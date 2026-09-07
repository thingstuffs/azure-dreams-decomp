#include "common.h"

extern s32 D_800E296C[3];

s32 func_800CE4E8(u8 arg0, u8 arg1, s16 arg2, void *arg3, s32 arg4);
s32 func_800CE6E0(void);

s32 func_800CE69C(void *arg0) {
    void *v0;

    if (D_800E296C[0] & 0xC0000000) {
        return 1;
    }
    v0 = *(void **)((s8 *)arg0 - 0x14);
    func_800CE4E8(((u8 *)v0)[0x24], ((u8 *)v0)[0x25], *(s16 *)((s8 *)arg0 + 0x88), arg0, 0);
    return func_800CE6E0() != 0;
}
