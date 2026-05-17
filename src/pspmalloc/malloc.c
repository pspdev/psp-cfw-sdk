#include <pspsdk.h>
#include <pspkernel.h>
#include <pspsysmem_kernel.h>

void* malloc(size_t size){
    int uid = sceKernelAllocPartitionMemory(PSP_MEMORY_PARTITION_USER, "", PSP_SMEM_High, size+sizeof(int), NULL);
    int* ptr = sceKernelGetBlockHeadAddr(uid);
    if (ptr){
        ptr[0] = uid;
        return &(ptr[1]);
    }
    return NULL;
}

void free(void* ptr){
    if (ptr){
        SceUID uid = ((SceUID*)ptr)[-1];
        sceKernelFreePartitionMemory(uid);
    }
}
