#include "common.h"

extern s32 func_800D1A80(void);
extern void func_800A56C0(void);

void func_800D2464(s32 arg0, s32 arg1, void *arg2) {
    if (func_800D1A80() != 0) {
        func_800A56C0();
        return;
    }

    *(s16 *)((u8 *)arg2 + 0x12) = 0;
}
