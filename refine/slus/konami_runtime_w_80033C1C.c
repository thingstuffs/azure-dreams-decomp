#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80033C1C_0 {
    s32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_80033C1C_0;   /* arg0 in func_80033C1C */


/* Initialize the state with the supplied value, zeroed fields, and unit scale. */
void func_80033C1C(S_80033C1C_0 *state, s32 initialValue) {
    state->unk_00 = 1;
    state->unk_04 = initialValue;
    state->unk_08 = 0;
    state->unk_0A = 0;
    state->unk_0C = 0;
    state->unk_10 = 0;
    state->unk_14 = 0;
    state->unk_18 = 0;
    state->unk_20 = 0x1000;
    state->unk_24 = 0x1000;
    state->unk_28 = 0x1000;
    state->unk_30 = 0;
    state->unk_34 = 0;
    state->unk_38 = 0;
    state->unk_40 = 0;
    state->unk_44 = 0;
    state->unk_48 = 0;
    state->unk_4C = 0;
    state->unk_50 = 0;
    state->unk_54 = 0;
    state->unk_58 = 0;
    state->unk_5C = 0;
    state->unk_60 = 0;
}
