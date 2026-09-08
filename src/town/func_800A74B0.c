#include "common.h"

typedef s32 M2C_UNK;


extern M2C_UNK func_800A4B94();
extern M2C_UNK D_800A4B94;


typedef struct S_800A4C10_0 {
    void * unk_00;
    void * unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x4];
    M2C_UNK * unk_28;
} S_800A4C10_0;   /* arg0 in func_800A4C10 */

typedef struct S_800A4C10_1 {
    s32 unk_00;
} S_800A4C10_1;   /* temp_v1 in func_800A4C10 */

typedef struct S_800A4C10_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800A4C10_2;   /* ((S_800A4C10_0 *)arg0)->unk_00 in func_800A4C10 */

/* Restart interpolation when the target changes, otherwise advance toward its position. */
void func_800A4C10(S_800A4C10_0 *state) {
    s32 steps_left;
    S_800A4C10_1 *target;

    target = state->unk_00;
    if (target != state->unk_04) {
        state->unk_20 = 9;
        state->unk_14 = 0;
        state->unk_18 = 0;
        state->unk_1C = 0;
        state->unk_04 = target;
        func_800A4B94(state);
        return;
    }
    state->unk_08 +=
        (target->unk_00 - state->unk_08) /
        state->unk_20;
    state->unk_0C +=
        (((S_800A4C10_2 *)(state->unk_00))->unk_04 - state->unk_0C) /
        state->unk_20;
    state->unk_10 +=
        (((S_800A4C10_2 *)(state->unk_00))->unk_08 - state->unk_10) /
        state->unk_20;
    steps_left = state->unk_20 - 1;
    state->unk_20 = steps_left;
    if (steps_left <= 0) {
        state->unk_28 = &D_800A4B94;
    }
}
