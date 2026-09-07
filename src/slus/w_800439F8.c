#include "common.h"

extern u8 D_80080A8A;
extern u32 D_80081494;
extern u8 D_800814AC;
extern u8 D_800814A4;

void func_800439F8(void)
{
    u8 *page = (u8 *)0x80010000;

    if (D_80080A8A != 0) {
        u32 value0 = D_80081494;
        u8 value4 = D_800814AC;
        u8 value6 = D_800814A4;
        *(u8 *)0x80080A8A = 0;
        *(u32 *)(page + 0x3180) = value0;
        *(u8 *)(page + 0x3184) = value4;
        *(u8 *)(page + 0x3186) = value6;
    } else {
        u32 value0 = *(u32 *)(page + 0x3180);
        u8 value4 = *(u8 *)(page + 0x3184);
        u8 value6 = *(u8 *)(page + 0x3186);
        D_80081494 = value0;
        D_800814AC = value4;
        D_800814A4 = value6;
    }
}
