#include "common.h"
#include "m2c_compat.h"

typedef struct S_800DC82C_0 {
    u8 pad_00[0x38];
    s32 * unk_38;
    u8 pad_3C[0x18];
    s32 unk_54;
    u8 pad_58[0x4];
    union { s32 s; volatile s32 u; } unk_5C;   /* accessed as both */
} S_800DC82C_0;   /* arg0 in func_800DC82C */


/* cfail-repair: tf7-phase1-cache-v3 */
/* Updates the low flag bits and activity field from the referenced state. */
void func_800DC82C(S_800DC82C_0 *record) {
    s32 state_or_flags;
    s32 flag_value;

    record->unk_5C.s = 0;
    state_or_flags = *record->unk_38;
    flag_value = 1;
    if (state_or_flags == 0) {
        state_or_flags = record->unk_54;
        state_or_flags |= 3;
        goto label_880;
    }
    if (state_or_flags == flag_value) {
        state_or_flags = record->unk_54;
        flag_value = -3;
        state_or_flags |= 1;
        goto label_87C;
    }
    state_or_flags = record->unk_54;
    record->unk_5C.u = flag_value;
    flag_value = -2;
    state_or_flags &= flag_value;
    flag_value = -3;
label_87C:
    state_or_flags &= flag_value;
label_880:
    record->unk_54 = state_or_flags;
}
