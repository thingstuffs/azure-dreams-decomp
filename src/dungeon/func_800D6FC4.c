#include "common.h"

typedef struct S_800DC724_0 {
    u8 pad_00[0x3C];
    void * unk_3C;
    u8 pad_40[0x10];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
} S_800DC724_0;   /* arg0 in func_800DC724 */

typedef struct S_800DC724_1 {
    u16 unk_00;
    u16 unk_02;
} S_800DC724_1;   /* temp_v0 in func_800DC724 */

typedef struct S_800DC724_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800DC724_2;   /* holder in func_800DC724 */

typedef struct S_800DC724_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800DC724_3;   /* temp_a0 in func_800DC724 */



extern s32 SD_Call();
extern s32 func_800DC650();
extern u8 D_800E2924[];

/* Move toward the indexed position, then apply the pending index once settled. */
void func_800DC724(S_800DC724_0 *state, s32 coord)
{
    s32 next_index;
    s32 delta_x;
    s32 delta_y;
    s32 current_index;
    s32 biased_dx;
    s32 biased_dy;
    s32 target_y;
    s32 index;
    s32 target_x;
    u8 *positions;
    S_800DC724_2 *holder;
    S_800DC724_3 *position;
    S_800DC724_1 *target;

    positions = D_800E2924;
    index = state->unk_50;
    holder = state->unk_3C;
    target = (index * 4) + positions;
    target_x = target->unk_00;
    target_y = target->unk_02;
    position = holder->unk_04;
    state->unk_58 = 0;
    delta_x = (s16)target_x - position->unk_08;
    if (delta_x != 0) {
        state->unk_58 = 1;
        coord = position->unk_08;
        biased_dx = delta_x + 3;
        if (delta_x <= 0) {
            biased_dx = delta_x - 3;
        }
        position->unk_08 = coord + (biased_dx >> 2);
    }
    delta_y = (s16)target_y - position->unk_0A;
    if (delta_y != 0) {
        state->unk_58 = 1;
        coord = position->unk_0A;
        biased_dy = delta_y + 3;
        if (delta_y <= 0) {
            biased_dy = delta_y - 3;
        }
        position->unk_0A = coord + (biased_dy >> 2);
    }
    func_800DC650(state, coord, target_y);
    if (state->unk_58 != 0) {
        return;
    }
    current_index = state->unk_50;
    next_index = state->unk_54;
    if (current_index == next_index) {
        return;
    }
    if ((next_index ^ current_index) & 2) {
        SD_Call(0x507);
    }
    state->unk_50 = state->unk_54;
}
