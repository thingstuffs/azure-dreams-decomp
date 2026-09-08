#include "common.h"

#include "common.h"

typedef struct D80082A38 {
    u8 pad0[0x48];
    s32 field48;
    s32 field4C;
    u8 pad50[0x5C];
    s16 fieldAC;
    s16 fieldAE;
} D80082A38;

extern D80082A38 D_80082A38;

/* Copies the signed 16-bit fields at AC and AE into the 32-bit fields at 48 and 4C. */
void func_8003AAF8(void) {
    D80082A38 *state;
    s32 value_ac;
    s32 value_ae;

    state = &D_80082A38;
    value_ac = state->fieldAC;
    value_ae = state->fieldAE;
    state->field48 = value_ac;
    state->field4C = value_ae;
}
