#include "common.h"

typedef s32 M2C_UNK;

extern void func_80094984(void *arg0, void *arg1);
extern s16 func_800C2B88(s16 arg0, s16 arg1, M2C_UNK arg2);
extern u8 D_80082660[];
extern M2C_UNK D_800D0128;
extern M2C_UNK D_80099874;

void func_800991C0(void *arg0, M2C_UNK arg1) {
    M2C_UNK arg2;

    func_80094984(&D_800D0128, arg0);
    arg2 = arg1;
    ASM_KEEP(arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    D_80082660[*(s32 *)((s8 *)arg0 + 0x40) * 8] = 0;
    *(M2C_UNK **)((s8 *)arg0 + 4) = &D_80099874;
    *(s16 *)((s8 *)arg0 + 0x10) = func_800C2B88(*(s16 *)((s8 *)arg0 + 0x36), *(s16 *)((s8 *)arg0 + 0x38), arg2);
}
