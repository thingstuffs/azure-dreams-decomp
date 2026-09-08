#include "common.h"

typedef s32 M2C_UNK;

extern void func_80094984(void *arg0, void *arg1);
extern s16 func_800C2B88(s16 arg0, s16 arg1, M2C_UNK arg2);
extern u8 D_80082660[];
extern M2C_UNK D_800D0128;
extern M2C_UNK D_80099874;

/* Clears the object's slot flag and initializes its state pointer and lookup result. */
void func_800991C0(void *object, M2C_UNK lookup_arg) {
    M2C_UNK saved_lookup_arg;

    func_80094984(&D_800D0128, object);
    saved_lookup_arg = lookup_arg;
    ASM_KEEP(saved_lookup_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    D_80082660[*(s32 *)((s8 *)object + 0x40) * 8] = 0;
    *(M2C_UNK **)((s8 *)object + 4) = &D_80099874;
    *(s16 *)((s8 *)object + 0x10) = func_800C2B88(*(s16 *)((s8 *)object + 0x36), *(s16 *)((s8 *)object + 0x38), saved_lookup_arg);
}
