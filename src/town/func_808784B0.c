#include "common.h"

extern s32 D_80700000[];
extern s32 D_80701DC4[];

extern void func_80701FEC(s32 arg0);
extern void func_80702180(s32 index, s32 arg1);

s32 func_807024B0(void) {
    s32 temp_a0;
    s32 temp_s0;

    temp_a0 = D_80701DC4[0];
    temp_s0 = *(s32 *)((u8 *)D_80700000 + (temp_a0 << 5) + 0x1E40);
    func_80702180(temp_a0, 3);
    func_80701FEC(3);
    return temp_s0;
}
