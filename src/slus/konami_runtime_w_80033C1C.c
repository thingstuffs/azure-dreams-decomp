#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"



/* Initialize the state with the supplied value, zeroed fields, and unit scale. */
void func_80033C1C(Rec_D_80081FDC *state, s32 initialValue) {
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
