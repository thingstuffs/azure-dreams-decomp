#include "common.h"
#include "m2c_compat.h"

s32 func_80026E70();                    /* extern */
s32 func_8002714C();      /* extern */
M2C_UNK func_8004B1A4();                         /* extern */

typedef struct S_800273E4_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800273E4_0;   /* arg0 in func_800273E4 */

/* Recalculates the state's derived value and replaces its associated handle. */
void *func_800273E4(S_800273E4_0 *state, M2C_UNK replacementInput, M2C_UNK calculationInput) {
    s32 adjustedValue;

    func_8004B1A4(state->unk_08);
    adjustedValue = func_80026E70(state->unk_00, calculationInput) + 5;
    state->unk_04 = adjustedValue;
    state->unk_08 = func_8002714C(state->unk_00, replacementInput, adjustedValue, calculationInput);
    return state;
}
