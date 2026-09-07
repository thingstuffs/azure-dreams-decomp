#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800B8D5C(void);
extern s32 D_800814A0; /* overlays/dungeon/first_pass_matched/func_800AB5D4.c */

void func_800B8CF0(void *arg0, s32 arg1, void *arg2) {
    s32 temp;

    temp = FIELD(arg0, u16, 2) - 1;
    FIELD(arg0, u16, 2) = (u16) temp;
    if (((temp << 16) >> 16) <= 0) {
        FIELD(arg0, u16, -2) = (u16) (FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0 |= 0x8000;
        func_800B8D5C();
        return;
    }
    if (temp & 1) {
        s8 val = (s8) ((((temp << 16) >> 16) << 3) | 0x20);
        FIELD(arg2, s8, 0xC) = val;
        FIELD(arg2, s8, 0xE) = val;
        FIELD(arg2, s8, 0xD) = val;
        func_800B8D5C();
        return;
    }
    FIELD(arg2, s32, 0xC) = 0x00101010;
}
