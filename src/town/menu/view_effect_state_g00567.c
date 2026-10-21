/* inferred-strong G00567: view_effect_state_g00567; joins CL:town/func_800A4E6C; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A4E6C. */
#include "town/menu/view_effect_state_g00567.h"

/* Updates state from global values and triggers a refresh every 15 calls. */
void update_view_driven_state(State *state) {

    state->field_8 = (func_80064584(g_game_work.view.camera_rotation.parts.viewAngle) + 0x1000) / 2;
    state->field_0 = -func_80064584(g_game_work.view.camera_rotation.parts.viewAngle) / 24;
    state->field_2 = func_80065F90(state->field_0, 160);
    state->field_4 = ((u16)g_game_work.view.camera_position.parts.camera_position_x);
    state->field_6 = ((u16)g_game_work.view.camera_position.parts.camera_position_y);

    if (--state->field_C <= 0) {
        state->field_C = 15;
        allocate_randomized_effect_object((s32)state);
    }
}

/* Allocates an object and initializes its randomized state. */
void *allocate_randomized_effect_object(s32 state_value)
{
    s32 offset_sample;
    s16 initial_count;
    S_800A25CC_1 *state;
    void *object;

    object = allocate_flagged_object_node(0x136);
    if (object == 0) {
        return 0;
    }
    ((S_800A25CC_0 *)object)->unk_10 = D_800A2690;
    state = object + 0x20;
    initial_count = scale_random_to_unsigned_halfword_limit(0xB4) + 0x3C;
    state->unk_04 = initial_count;
    state->unk_06 = initial_count;
    state->unk_10 = (scale_random_to_unsigned_halfword_limit(0x28) & 0xFFFF) + 0x80;
    state->unk_14 = state_value;
    offset_sample = scale_random_to_unsigned_halfword_limit(0x40);
    state->unk_08 = offset_sample + scale_random_to_unsigned_halfword_limit(0x40) - 0x40;
    state->unk_0A = scale_random_to_unsigned_halfword_limit(0x40);
    state->unk_0C = scale_random_to_unsigned_halfword_limit(0x40);
    return object;
}
