#include <pspuser.h>
#include <pspsysmem.h>
#include <stdint.h>

extern void *memset(void * buffer_, int value, unsigned int size);

static SceUID mainVpl = -1;

/* I think we don't strictly need this but may as well leave it */
void memdestroy()
{
    if ( mainVpl < 0 ) return; /* No VPL to destroy */
    
    sceKernelDeleteVpl(mainVpl);
}

SceUID memcreate(SceSize vplSize)
{
    if ( mainVpl ) memdestroy(); /* If there's already a VPL created, delete that one (should we change this?) */

    mainVpl = sceKernelCreateVpl("Main VPL", PSP_MEMORY_PARTITION_USER, 0, vplSize, NULL);
    return mainVpl;
}

void *malloc(size_t size)
{
    if ( size == 0 ) return NULL;

    /* mainVpl not created by the user, we'll need to create our own instead */
    if ( mainVpl < 0 )
    {
        memcreate(16 * 1024); /* 16 KB for now */
    }

    uintptr_t *ptr = NULL;

    /* We actually need to allocate an extra ptr to store the ptr */
    if ( sceKernelTryAllocateVpl(mainVpl, size + sizeof(uintptr_t), (void **)&ptr) < 0 ) return NULL; /* No mem! */

    *ptr = (uintptr_t)ptr; /* Save pointer in the first 4 bytes */

    return ++ptr; /* Return 2nd 4 bytes */
}

void *memalign(unsigned int align, size_t size)
{
    if ( mainVpl < 0 || size == 0 || (align & (align - 1)) ) return NULL;

    const uintptr_t *ptr = NULL;

    /* We need to allocate size + alignment + extra ptr because that's what it needs in the worst case scenario */
    if ( sceKernelTryAllocateVpl(mainVpl, size + align + sizeof(uintptr_t), (void **)&ptr) < 0 ) return NULL;

    /* Get next aligned byte */
    uintptr_t *aligned = (uintptr_t*)(((uintptr_t)ptr + align + sizeof(uintptr_t) - 1) & ~(align - 1));
    aligned[-1] = (uintptr_t)ptr; /* Save pointer in the first 4 aligned bytes */

    return aligned; /* Return 2nd aligned 4 bytes */
}

void free(void* ptr)
{
    if ( mainVpl < 0 || !ptr ) return; /* No VPL / invalid ptr */

    void *original = (void *)((uintptr_t *)ptr)[-1]; /* Get saved pointer from previous 4 bytes */
    sceKernelFreeVpl(mainVpl, original);
}

void *calloc(size_t n, size_t size)
{
    if ( size == 0 || n > SIZE_MAX / size ) return NULL; /* Invalid size / Overflow check */

	size_t total = n * size;

	void *p = malloc(total);
	if ( !p ) return NULL;
	
	return memset(p, 0, total);
}