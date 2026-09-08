#include "common.h"

#ifdef NON_MATCHING
#define ASM_KEEP4(p, x, y, z) ((void)0)
#else
#define ASM_KEEP4(p, x, y, z) \
    __asm__ __volatile__("" : "+r"(p), "+r"(x), "+r"(y), "+r"(z))
#endif

extern u8 D_80083160[];
extern u8 D_80162004[];
extern void *func_800B7420();

/* Initialize the shared buffer pointer and paired parameters, then process the buffer. */
void func_800B72B8(void)
{
    u8 *base = D_80083160;
    u8 *p = base + 0x1DC;
    int size;
    int limit;
    int seven;

    seven = 7;
    limit = 0x7F;
    size = 0x2000;
    ASM_KEEP4(p, seven, limit, size);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    *(s16 *)(p + 0x14) = seven;
    seven = 7;
    *(s16 *)(p + 0x16) = seven;
    *(s16 *)(p + 0x18) = limit;
    *(s16 *)(p + 0x1C) = size;
    *(s16 *)(p + 0x1A) = limit;
    *(s16 *)(p + 0x1E) = size;
    *(u8 **)(base + 0x1DC) = D_80162004;
    func_800B7420(base, size, limit);
}
