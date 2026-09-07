#include "common.h"

extern u8 D_8006CCD8[9];
extern u8 D_8006CCE8[9];
extern void func_8009B25C(void *, s32, s32, s32);

void func_800A04F0(void *arg0, s32 arg1, s32 arg2, u32 arg3) {
    s32 shifted;
    u8 *base1;
    s32 offset;

    shifted = arg3 >> 8;
    base1 = D_8006CCD8;
    offset = shifted & 0xE;
    func_8009B25C(
        arg0,
        (*(u16 *)(base1 + offset) + arg1) & 0xFFFF,
        (*(u16 *)(&D_8006CCE8[offset]) + arg2) & 0xFFFF,
        *(s16 *)((u8 *)arg0 + 0x88));
}
