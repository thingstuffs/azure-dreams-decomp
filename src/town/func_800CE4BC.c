#include "common.h"

extern void func_800C3050(void *arg0, u32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern u8 D_800D6AE4[];
extern u8 D_800D6AEC[];
extern u8 D_800D6B14[];
extern u8 D_800D6B18[];

// Configure the context for ID 0x27, then clear state word 9 and flag 0x100.
void func_800CBC1C(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x27, D_800D6B14, D_800D6B18, D_800D6AE4,
                  D_800D6AEC);
    stateWords[9] = 0;
    stateWords[10] &= ~0x100;
}
