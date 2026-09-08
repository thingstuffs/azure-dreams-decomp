#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80094984();
extern s16 func_800C2B88();
extern M2C_UNK D_80082660;
extern M2C_UNK D_80099874;

/* Clears the object slot flag, sets its handler, and updates its position-dependent value. */
void func_8009A41C(void *object, M2C_UNK value_arg) {
    M2C_UNK saved_value_arg;

    func_80094984(*(s32 **)(*(void **)((u8 *)object + 0x44) + 0x14), object);
    saved_value_arg = value_arg;
    ASM_KEEP(saved_value_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    *((s8 *)(&D_80082660) + (*(s32 *)((u8 *)object + 0x40) * 8)) = 0;
    *(void **)((u8 *)object + 4) = &D_80099874;
    *(s16 *)((u8 *)object + 0x10) = func_800C2B88(
        *(s16 *)((u8 *)object + 0x36),
        *(s16 *)((u8 *)object + 0x38),
        saved_value_arg);
}
