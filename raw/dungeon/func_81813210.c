#include "common.h"

extern u8 D_80027F34[];

void func_80028210(void *arg0, s32 arg1, s32 arg2) {
    *(s32 *)((u8 *)arg0 + 0x44) = arg1;
    arg1 += 0x20;
    *(s32 *)((u8 *)arg0 + 0x04) = 4;
    *(s32 *)((u8 *)arg0 + 0x48) = arg1;
    *(s32 *)((u8 *)arg0 + 0x18) = arg2;
    *(s32 *)arg0 = 0;
    *(u8 **)((u8 *)arg0 - 0x10) = D_80027F34;
}
