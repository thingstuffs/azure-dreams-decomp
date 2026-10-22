/* Approach player angle target.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01125 - CL:town/func_8009D150.
 */
#include "town/player/approach_player_angle_target_g01125.h"

/* Move toward an angle-offset target and advance state when the timer expires. */
void approach_player_angle_target(S_8009A724_0 *state, S_8009A724_1 *position) {
    s16 target_x;
    s16 target_z;
    s16 frames_left;

    target_x = state->unk_36 - (func_800644B8(state->unk_10 - 0x80) / 48);
    target_z = state->unk_38 - (func_80064584(state->unk_10 - 0x80) / 48);
    frames_left = state->unk_0A - 1;
    state->unk_0A = (u16) frames_left;
    position->unk_02 = approach_scalar_target(frames_left, position->unk_02, target_x);
    position->unk_06 = approach_scalar_target((s16) state->unk_0A, position->unk_06, target_z);
    if ((s16) state->unk_0A <= 0) {
        state->unk_0A = 0x10U;
        state->unk_04 = &D_8009A81C;
    }
}

/* Updates two values using a countdown and switches state when it expires. */
void update_player_countdown_values(S_8009A81C_0 *state, S_8009A81C_1 *values) {
    u16 ticks_left;

    ticks_left = state->unk_0A - 1;
    state->unk_0A = ticks_left;
    values->unk_02 = approach_scalar_target((s16) ticks_left, values->unk_02, state->unk_36);
    values->unk_06 = approach_scalar_target((s16) state->unk_0A, values->unk_06, state->unk_38);
    if ((s16) state->unk_0A <= 0) {
        state->unk_0A = 0x20U;
        state->unk_04 = &player_no_op;
    }
}

/* Performs no operation. */
void player_no_op(void) {
}

/* Move the current value toward the target by the given divisor. */
s16 approach_scalar_target(s32 divisor, s16 current, s16 target)
{
    if (divisor != 0) {
        u32 current_shifted = (u32)current << 16;
        return (s16)(current + (((s32)target - ((s32)current_shifted >> 16)) / divisor));
    }
    return current;
}
