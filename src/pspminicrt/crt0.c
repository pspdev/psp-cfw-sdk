#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdisplay.h>

static char boot_path[256];
extern int main(int argc, char *argv[]);

void _exit(int status){
    sceKernelExitGame();
}

static int start_thread(SceSize args, void *argp)
{
    SceUID mod;
    char *path = (char *)argp;
    char* last_trail = NULL;
    int i = 0;

    strcpy(boot_path, path);
    last_trail = strrchr(boot_path, '/');
    if (last_trail) last_trail[0] = 0;

    sceIoChdir(boot_path);
    
    main(1, &path);
    
    _exit(0);
    return 0;
}

int module_start(SceSize args, void *argp)
{

    SceUID thid = sceKernelCreateThread("minicrt_start_thread", start_thread, 0x10, 0x4000, 0, NULL);

    if (thid < 0)
        return thid;

    sceKernelStartThread(thid, args, argp);
    
    return 0;
}

