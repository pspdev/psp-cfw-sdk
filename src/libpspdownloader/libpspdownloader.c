/*
 * PSP Homebrew - HTTP File Downloader
 *
 * Connects to the network using a saved PSP Wi-Fi profile, then downloads
 * a file over HTTP using sceHttp, saving it to ms0:/ (memory stick).
 *
 * Build with PSPSDK (see Makefile / README for instructions).
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <psphttp.h>
#include <pspssl.h>          /* needed if you plan to use https:// URLs */
#include <pspsdk.h>
#include <psputility.h>
#include <psputility_modules.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pspdownloader.h"

#define printf pspDebugScreenPrintf

#define READ_CHUNK (4096)
//PSP_HEAP_SIZE_KB(1024);

/* PSP homebrew must explicitly load these kernel-mode PRX modules before
   using the corresponding sceNet / sceHttp APIs, or calls like sceNetInit
   fail with 0x8002013A (module not found). */
int load_network_modules(void)
{
    int mods[] = {
        PSP_NET_MODULE_COMMON,
        PSP_NET_MODULE_INET,
        PSP_NET_MODULE_PARSEURI,   /* required by sceHttp */
        PSP_NET_MODULE_PARSEHTTP,  /* required by sceHttp */
        PSP_NET_MODULE_HTTP,
        /* PSP_NET_MODULE_SSL,     -- uncomment if using https:// */
    };
    int i;
    for (i = 0; i < (int)(sizeof(mods) / sizeof(mods[0])); i++) {
        int err = sceUtilityLoadNetModule(mods[i]);
        if (err < 0) {
            #ifdef DEBUG
            printf("Failed to load net module %d: 0x%08X\n", mods[i], err);
            #endif
            /* Unload whatever we already loaded so we don't leak kernel
               memory across repeated test runs. */
            int j;
            for (j = i - 1; j >= 0; j--) {
                sceUtilityUnloadNetModule(mods[j]);
            }
            return err;
        }
    }
    return 0;
}

void unload_network_modules(void)
{
    int mods[] = {
        PSP_NET_MODULE_HTTP,
        PSP_NET_MODULE_PARSEHTTP,
        PSP_NET_MODULE_PARSEURI,
        PSP_NET_MODULE_INET,
        PSP_NET_MODULE_COMMON,
    };
    int i;
    for (i = 0; i < (int)(sizeof(mods) / sizeof(mods[0])); i++) {
        sceUtilityUnloadNetModule(mods[i]);
    }
}

/* Bring up networking and connect using the PSP's saved access point (slot 1) */
int net_connect(void)
{
    int err;

    err = load_network_modules();
    if (err < 0) return err;

    /* Diagnostics: how much memory does the system actually have free
       right now? On real hardware, sceNetInit's pool comes out of a
       separate kernel partition that seplugins/recovery-menu hooks can
       eat into permanently once loaded. */
    #ifdef DEBUG
    SceSize freeMem = sceKernelTotalFreeMemSize();
    SceSize maxBlock = sceKernelMaxFreeMemSize();
    printf("Free mem (total): %u KB\n", (unsigned int)(freeMem / 1024));
    printf("Free mem (largest block): %u KB\n", (unsigned int)(maxBlock / 1024));
    #endif
    err = sceNetInit(128 * 1024, 42, 4 * 1024, 42, 4 * 1024);
    if (err < 0) {
        #ifdef DEBUG
        printf("sceNetInit failed: 0x%08X\n", err);
        #endif
        unload_network_modules();
        return err;
    }

    err = sceNetInetInit();
    if (err < 0) {
        #ifdef DEBUG
        printf("sceNetInetInit failed: 0x%08X\n", err);
        #endif
        sceNetTerm();
        unload_network_modules();
        return err;
    }

    err = sceNetApctlInit(0x8000, 48);
    if (err < 0) {
        #ifdef DEBUG
        printf("sceNetApctlInit failed: 0x%08X\n", err);
        #endif
        sceNetInetTerm();
        sceNetTerm();
        unload_network_modules();
        return err;
    }

    /* Connect using access point config slot 1 (must already be set up
       in the PSP's Network Settings). */
	int found = 0;
	int wifiProfile = -1;
    for (int i = 1; i < 10; i++) { // If no profiles are setup this will still act like there is a valid connection
        int r = sceUtilityCheckNetParam(i);
        #ifdef DEBUG
        printf("sceUtilityCheckNetParam(%d) = 0x%08X\n", i, r);
        #endif
        if (r == 0) {
			found = 1;
			wifiProfile = i;
			break;
		}
    }
    if (!found) {
        #ifdef DEBUG
        printf("No valid network configs found at all.\n");
		return -1;
        #endif
    }
    err = sceNetApctlConnect(wifiProfile);
    if (err < 0) {
        #ifdef DEBUG
        printf("sceNetApctlConnect failed: 0x%08X\n", err);
        #endif
        sceNetApctlTerm();
        sceNetInetTerm();
        sceNetTerm();
        unload_network_modules();
        return err;
    }

    #ifdef DEBUG
    printf("Connecting to access point");
    #endif
    int state = -1;
    while (1) {
        int r = sceNetApctlGetState(&state);
        if (r < 0) {
            #ifdef DEBUG
            printf("\nGetState failed: 0x%08X\n", r);
            #endif
            sceNetApctlDisconnect();
            sceNetApctlTerm();
            sceNetInetTerm();
            sceNetTerm();
            unload_network_modules();
            return r;
        }
        if (state == 4) break; /* PSP_NET_APCTL_STATE_GOT_IP */
        #ifdef DEBUG
        printf(".");
        #endif
        sceKernelDelayThread(500 * 1000);
    }
    #ifdef DEBUG
    printf("\nConnected.\n");
    #endif
    return 0;
}

void net_disconnect(void)
{
    sceNetApctlDisconnect();
    sceNetApctlTerm();
    sceNetInetTerm();
    sceNetTerm();
    unload_network_modules();
}

/* Download url into local file at outPath using sceHttp */
int download_file(char *url, char *outPath)
{
    int result;
    int templateId = -1, connectionId = -1, requestId = -1, netconnect = -1;
    //SceUChar *buf = NULL;
	u8 buf[READ_CHUNK];
    //SceIoStat st;

	netconnect = net_connect();
	if(netconnect < 0) {
        #ifdef DEBUG
		printf("net_connect failed: 0x%08X\n", netconnect); 
        #endif
		goto cleanup;
	}

    /* If you need HTTPS support, also init sceSsl + sceHttpsInit here. */
    result = sceHttpInit(40 * 1024); // pool size in bytes; adjust as needed
    if (result < 0) {
        #ifdef DEBUG
        printf("sceHttpInit failed: 0x%08X\n", result);
        #endif
        return result;
    }
    templateId = sceHttpCreateTemplate("PSP-Downloader/1.0", PSP_HTTP_VERSION_1_1, 1);
    if (templateId < 0) { 
        #ifdef DEBUG
		printf("CreateTemplate failed: 0x%08X\n", templateId); 
        #endif
		goto cleanup; 
	}

    connectionId = sceHttpCreateConnectionWithURL(templateId, url, 1);
    if (connectionId < 0) { 
        #ifdef DEBUG
		printf("CreateConnection failed: 0x%08X\n", connectionId); 
        #endif
		goto cleanup; 
	}

    requestId = sceHttpCreateRequestWithURL(connectionId, PSP_HTTP_METHOD_GET, url, 0);
    if (requestId < 0) { 
        #ifdef DEBUG
		printf("CreateRequest failed: 0x%08X\n", requestId); 
        #endif
		goto cleanup; 
	}

    result = sceHttpSendRequest(requestId, NULL, 0);
    if (result < 0) { 
        #ifdef DEBUG
		printf("SendRequest failed: 0x%08X\n", result); 
        #endif
		goto cleanup; 
	}

    int statusCode = 0;
    sceHttpGetStatusCode(requestId, &statusCode);
    #ifdef DEBUG
    printf("HTTP status: %d\n", statusCode);
    #endif
    if (statusCode != 200) {
        #ifdef DEBUG
        printf("Server did not return 200 OK, aborting.\n");
        #endif
        result = -1;
        goto cleanup;
    }

    unsigned long long contentLength = 0;
    sceHttpGetContentLength(requestId, &contentLength);
    #ifdef DEBUG
    printf("Content-Length: %llu bytes\n", contentLength);
    #endif

    SceUID fd = sceIoOpen(outPath, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    if (fd < 0) {
        #ifdef DEBUG
        printf("Failed to open output file: 0x%08X\n", fd);
        #endif
        result = fd;
        goto cleanup;
    }

    unsigned long long totalRead = 0;
    while (1) {
        int r = sceHttpReadData(requestId, buf, READ_CHUNK);
        if (r < 0) {
            #ifdef DEBUG
            printf("\nsceHttpReadData error: 0x%08X\n", r);
            #endif
            result = r;
            sceIoClose(fd);
            goto cleanup;
        }
        if (r == 0) break; /* done */

        sceIoWrite(fd, buf, r);
        totalRead += r;
        #ifdef DEBUG
        printf("\rDownloaded: %llu bytes", totalRead);
        #endif
    }
    printf("\nDownload complete: %s\n", outPath);

    sceIoClose(fd);
    result = 0;

cleanup:
    //if (buf) free(buf);
    if (requestId >= 0) sceHttpDeleteRequest(requestId);
    if (connectionId >= 0) sceHttpDeleteConnection(connectionId);
    if (templateId >= 0) sceHttpDeleteTemplate(templateId);
    sceHttpEnd();
    return result;
}
