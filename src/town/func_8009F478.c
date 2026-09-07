#include "common.h"

extern void func_8009CB64(void *arg0, void *arg1, void *arg2, void *arg3);
extern s32 D_800F8B6C[];

void func_8009CBD8(void *arg0, void *arg1, void *arg2) {
    func_8009CB64(arg0, arg1, arg2, &D_800F8B6C[0]);
    *(s16 *)((u8 *)arg2 + 0x10) = 0;
    *(u16 *)((u8 *)arg2 + 0x14) = *(u16 *)((u8 *)arg2 + 0x14) | 0x1C;
}
