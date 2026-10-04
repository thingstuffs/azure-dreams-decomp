#include "common.h"

extern s32 func_800D1A80(s32 value_a, s32 value_b, void *ptr, s32 value_c);
extern void func_800A56C0(void);

void func_800D2464(s32 value_a, s32 value_b, void *ptr, s32 value_c) {
    if (func_800D1A80(value_a, value_b, ptr, value_c) != 0) {
        func_800A56C0();
        return;
    }

    *(s16 *)((u8 *)ptr + 0x12) = 0;
}
