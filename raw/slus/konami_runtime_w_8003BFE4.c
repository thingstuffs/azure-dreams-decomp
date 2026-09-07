#include "common.h"

#include "common.h"

extern u8 D_80082D08[0x100];
extern u8 D_80083160[0x100];
extern void func_8003BE1C(u16 *, s32, s32);

void func_8003BFE4(void)
{
    u16 *dst = (u16 *)D_80082D08;
    u8 *base = D_80083160;
    u16 *src = (u16 *)(base + 0x20);
    s32 i = 0;
    u16 *src2 = (u16 *)(base + 0x24);
    u16 *dst2 = dst + 2;

    do {
        u16 value = *src;
        src += 4;
        i++;
        *dst = value;
        value = src2[-1];
        dst += 4;
        dst2[-1] = value;
        value = *src2;
        src2 += 4;
        *dst2 = value;
        dst2 += 4;
    } while (i < 6);

    func_8003BE1C((u16 *)D_80082D08, 6, 4);
}
