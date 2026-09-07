#include "common.h"

extern s32 func_800A4ACC();
extern s32 func_800AB1C0();
extern s32 func_800AD594();
extern s32 func_800AD9B4();

extern u16 D_80083462;
extern s32 D_801714D4[];

void func_8017276C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_800AB1C0() != 0) {
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            *(s32 **)((u8 *)arg0 + 0x8C) = D_801714D4;
            goto block_3;
        }
    } else {
block_3:
        if (D_80083462 & 0x80) {
            *(s16 *)((u8 *)arg0 + 0x92) = -0x20;
        }
    }
    ASM_USE(arg2);
}
