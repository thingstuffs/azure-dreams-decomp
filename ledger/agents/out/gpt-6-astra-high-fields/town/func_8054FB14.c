#include "common.h"

extern void *D_80016000;

typedef struct S_func_8054FB14_0 {
    u8 pad_00[0x38];
    void *unk_38;
} S_func_8054FB14_0;

typedef struct S_func_8054FB14_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_func_8054FB14_1;

/* Adds 100 to the stored value, divides by 100, and caps the result at ten. */
s32 func_8054FB14(void) {
    u32 value;

    value = (((S_func_8054FB14_1 *)((S_func_8054FB14_0 *)D_80016000)->unk_38)->unk_2D5C + 0x64U) / 100U;
    if ((s32)value >= 0xB) {
        value = 0xAU;
    }
    return value;
}
