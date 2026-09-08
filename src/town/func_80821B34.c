#include "common.h"

typedef struct S_80024334_0 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
} S_80024334_0;   /* arg0 in func_80024334 */

typedef struct S_80024334_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    s32 unk_14;
    u8 pad_18[0xC];
    u16 unk_24;
} S_80024334_1;   /* obj in func_80024334 */

typedef struct S_80024334_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_80024334_2;   /* arg2 in func_80024334 */

typedef struct S_80024334_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024334_3;   /* arg1 in func_80024334 */



/* Apply object flags and tint, and copy the selected value triplet. */
void func_80024334(S_80024334_0 *state, S_80024334_3 *selected_values, S_80024334_2 *render_state) {
    S_80024334_1 *source;

    source = state->unk_00;

    if (source->unk_24 & 1) {
        render_state->unk_14 |= 0x80;
    } else {
        render_state->unk_14 &= 0xFF7F;
    }

    if (source->unk_14 != 0) {
        render_state->unk_0C = 0x808080;
    } else {
        render_state->unk_0C = 0xFFFFFF;
    }

    if (state->unk_08 != 0) {
        selected_values->unk_02 = source->unk_04;
        selected_values->unk_06 = source->unk_06;
        selected_values->unk_0A = source->unk_08;
    } else {
        selected_values->unk_02 = source->unk_0C;
        selected_values->unk_06 = source->unk_0E;
        selected_values->unk_0A = source->unk_10;
    }
}
