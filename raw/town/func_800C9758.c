#include "common.h"

extern void func_800C3050(void *arg0, u32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern u8 D_800D5AC8[];
extern u8 D_800D5AD0[];
extern u8 D_800D5AF8[];
extern u8 D_800D5AFC[];

void func_800C6EB8(void *arg0, s32 arg1, u16 *arg2) {
    func_800C3050(arg0, 0x17, D_800D5AF8, D_800D5AFC, D_800D5AC8,
                  D_800D5AD0);
    arg2[9] = 0x280;
    arg2[10] &= ~0x100;
}
