#include "common.h"

extern void func_800C3050(void *arg0, u32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern u8 D_800D5AC8[];
extern u8 D_800D5AD0[];
extern u8 D_800D5AF8[];
extern u8 D_800D5AFC[];

// Load resource set 0x17, set state word 9 to 0x280, and clear flag 0x100 in word 10.
void func_800C6EB8(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x17, D_800D5AF8, D_800D5AFC, D_800D5AC8,
                  D_800D5AD0);
    stateWords[9] = 0x280;
    stateWords[10] &= ~0x100;
}
