#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80094984();
extern s16 func_800C2B88();
extern M2C_UNK D_80082660;
extern M2C_UNK D_80099874;

void func_8009A41C(void *arg0, M2C_UNK arg1) {
    M2C_UNK arg2;

    func_80094984(*(s32 **)(*(void **)((u8 *)arg0 + 0x44) + 0x14), arg0);
    arg2 = arg1;
    ASM_KEEP(arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    *((s8 *)(&D_80082660) + (*(s32 *)((u8 *)arg0 + 0x40) * 8)) = 0;
    *(void **)((u8 *)arg0 + 4) = &D_80099874;
    *(s16 *)((u8 *)arg0 + 0x10) = func_800C2B88(
        *(s16 *)((u8 *)arg0 + 0x36),
        *(s16 *)((u8 *)arg0 + 0x38),
        arg2);
}
