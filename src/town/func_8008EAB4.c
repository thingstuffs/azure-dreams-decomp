#include "common.h"

extern s32 func_8008C134(s16 arg0, s16 arg1);
extern s32 func_800C1D20(s32 arg0);
extern void func_8008C1C4(s32 arg0, s32 arg1, s32 arg2, void *arg3);

void func_8008C214(s16 arg0, void *arg1) {
    s32 i;

    for (i = 0; i < 0x80; i++) {
        func_8008C1C4(func_800C1D20(func_8008C134(i, arg0) & 0xFFFF), i, 0x80, arg1);
    }
}
