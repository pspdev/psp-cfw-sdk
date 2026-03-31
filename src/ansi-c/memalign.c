#include <pspsdk.h>
#include <pspkernel.h>
#include <pspsysmem_kernel.h>

void* memalign(unsigned int align, unsigned int size){
    int uid = sceKernelAllocPartitionMemory(PSP_MEMORY_PARTITION_USER, "", PSP_SMEM_High, size+sizeof(int), NULL);
    int* ptr = sceKernelGetBlockHeadAddr(uid);
    if (ptr){
        ptr = (void*)((u32)ptr + sizeof(int));
        ptr = (void*)(((u32)ptr & (~(align-1))) + align); // align
        ptr[-1] = uid;
        return ptr;
    }
    return NULL;
}
