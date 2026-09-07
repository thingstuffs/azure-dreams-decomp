#include "common.h"

extern s32 D_800AFD5C;

void func_800B0134(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x18) = arg1;
    arg1 = arg1 + 0x20;
    *(s32 *)((u8 *)arg0 + 0x10) = 1;
    *(s32 *)((u8 *)arg0 + 0x0) = arg1;
    *(s32 **)((u8 *)arg0 - 0x10) = &D_800AFD5C;
}
