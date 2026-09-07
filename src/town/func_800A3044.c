#include "common.h"

extern s32 func_800A2304(void *arg0, s32 arg1, s32 arg2, u8 arg3);
extern s32 D_800A07E8;

void func_800A07A4(void *arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 field98 = *(s32 *)((u8 *)arg0 + 0x98);
    u8 field94 = *(u8 *)((u8 *)arg0 + 0x94);

    if (func_800A2304(arg0, field98, arg2, field94) != 0) {
        *(s32 *)((u8 *)arg0 + 0x50) = (s32) &D_800A07E8;
    }
}
