#include "common.h"

#include "common.h"

extern void bzero(void *dst, s32 len);
extern void func_8004D0C8(void *arg0);

extern s32 D_80080B58;
extern s32 D_80080B5C;
extern s32 D_80080B60;
extern s32 D_80080B64;
extern u8 D_80083780[12];

/* Initialize state fields from globals and clear associated state. */
void func_8004D614(void)
{
    u8 *state = (u8 *)&D_80083178;

    bzero(state + 0x9C, 8);
    *(s32 *)(state + 0x94) = D_80080B60;
    *(s32 *)(state + 0x98) = D_80080B64;
    *(s32 *)(state + 0xAC) = D_80080B58;
    *(s32 *)(state + 0xB0) = D_80080B5C;
    bzero(state + 0xA4, 8);
    *(s32 *)(state + 0x13C) = 0;
    *(s32 *)(state + 0x180) = 0;
    *(s32 *)(state + 0xB4) = 0;
    *(s32 *)(state + 0xF8) = 0;
    func_8004D0C8(D_80083780);
}
