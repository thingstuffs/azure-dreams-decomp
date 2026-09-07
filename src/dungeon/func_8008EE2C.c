#include "common.h"

extern void *D_800E3D7C[];

void func_8009458C(s16 arg0, s8 arg1) {
    u8 *ptr;
    s32 off = arg0 * 4;
    void *p = *(void **)(off + 0xAC + (u8 *)D_800E3D7C[0]);
    *(s8 *)((u8 *)p + 0x12) = arg1;

    ptr = (u8 *)0x80010000 + (arg0 * 2);
    *(s16 *)(ptr + 0x2098) = arg1 & 0xFF;
}
