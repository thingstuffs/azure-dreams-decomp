#include "common.h"

extern void func_8004DA74(s32 arg0, void *arg1, s32 arg2);
extern u8 D_800282CC[];

void func_80027054(s32 arg0) {
    func_8004DA74(arg0 + 0x7C, &D_800282CC[0], 1);
}
