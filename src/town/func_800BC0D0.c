#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef unsigned long uptr;
#endif

extern u8 D_800D2EA4[];

void func_800B9830(void)
{
    s32 i;
    volatile u8 *src;
    register u8 *page ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

    i = 0;
    src = D_800D2EA4;
    page = (u8 *)0x80010000;
    do {
        i++;
        page[0x33A4] = src[6];
        {
            u8 value = src[7];
            src += 8;
            page[0x33A5] = value;
        }
        page += 2;
    } while (i < 0x22);

    i = 0;
    page = (u8 *)0x80010000;
    do {
        u8 *item = (u8 *)((uptr)i + (uptr)page);
        i++;
        item[0x3608] = 0;
        item[0x360A] = 0;
    } while (i < 2);
}
