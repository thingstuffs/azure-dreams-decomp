#include "common.h"

extern s32 func_800352FC(void *, s32, s32, s32);
extern s32 func_800C2A60(void *arg0);
extern void func_8008F134(void *arg0);
extern s32 D_800814A0;

void func_800C26C0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if ((func_800352FC(arg0, arg1, arg2, arg3) != 0) && (func_800C2A60(arg0) != 0)) {
        func_8008F134(arg0);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
