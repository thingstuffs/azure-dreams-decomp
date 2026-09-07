#include "common.h"

#include "common.h"

extern void bzero(void *dst, s32 len);
extern void func_8004D0C8(void *arg0);

extern s32 D_80080B58;
extern s32 D_80080B5C;
extern s32 D_80080B60;
extern s32 D_80080B64;
extern u8 D_80083780[12];

void func_8004D614(void)
{
    u8 *base = (u8 *)&D_80083178;

    bzero(base + 0x9C, 8);
    *(s32 *)(base + 0x94) = D_80080B60;
    *(s32 *)(base + 0x98) = D_80080B64;
    *(s32 *)(base + 0xAC) = D_80080B58;
    *(s32 *)(base + 0xB0) = D_80080B5C;
    bzero(base + 0xA4, 8);
    *(s32 *)(base + 0x13C) = 0;
    *(s32 *)(base + 0x180) = 0;
    *(s32 *)(base + 0xB4) = 0;
    *(s32 *)(base + 0xF8) = 0;
    func_8004D0C8(D_80083780);
}
