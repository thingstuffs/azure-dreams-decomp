#include "common.h"

extern void func_800C3050(void *arg0, u32 arg1, void *arg2, void *arg3,
                           void *arg4, void *arg5);
extern u8 D_800D6AE4[];
extern u8 D_800D6AEC[];
extern u8 D_800D6B14[];
extern u8 D_800D6B18[];

void func_800CBC1C(void *arg0, s32 arg1, u16 *arg2) {
    func_800C3050(arg0, 0x27, D_800D6B14, D_800D6B18, D_800D6AE4,
                  D_800D6AEC);
    arg2[9] = 0;
    arg2[10] &= ~0x100;
}
