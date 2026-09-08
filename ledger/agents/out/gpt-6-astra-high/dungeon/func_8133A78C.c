#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D60;

typedef struct S_8017178C_0 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
} S_8017178C_0;   /* state in func_8017178C */

/* Stores the value at offset 0x12 and clears the field at offset 0x18. */
void func_8017178C(s16 value) {
    S_8017178C_0 *state;

    state = D_80175D60 + 0x20;
    state->unk_12 = value;
    state->unk_18 = 0;
}
