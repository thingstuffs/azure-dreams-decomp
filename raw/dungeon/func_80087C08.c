#include "common.h"

void func_8008D368(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *((s8 *)arg0 + 0x9A) = 0x2E;
    *((s8 *)arg0 + 0x9B) = 0;
    *(s32 *)((s8 *)arg0 + 0x8C) = 0;
    *(s32 *)((s8 *)arg0 + 0xCC) = arg3;
    *(s16 *)((s8 *)arg0 + 0x10E) = (s16) arg4;
}
