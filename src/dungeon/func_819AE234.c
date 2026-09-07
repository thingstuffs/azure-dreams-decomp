#include "common.h"

extern u8 D_80027452[16];
extern u8 D_800814A0[16];

void func_80025A34(void *arg0, s32 arg1, void *arg2) {
    u8 red;
    u8 green;
    u8 blue;

    *(u16 *)D_80027452 = *(u16 *)D_80027452 + 1;
    red = *((u8 *)arg2 + 0xC);
    green = *((u8 *)arg2 + 0xD);
    *((u8 *)arg2 + 0xC) = red - (red >> 1);
    blue = *((u8 *)arg2 + 0xE);
    *((u8 *)arg2 + 0xD) = green - (green >> 1);
    *((u8 *)arg2 + 0xE) = blue - (blue >> 1);
    if (*((u8 *)arg2 + 0xC) < 8) {
        *((u16 *)arg0 - 1) |= 0x8000;
        *(u32 *)D_800814A0 |= 0x8000;
    }
}
