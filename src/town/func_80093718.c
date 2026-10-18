/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"

void initialize_scene_action_record();      

typedef struct S_80090DF0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80090DF0_0;   

void dispatch_actor_interaction_actions(s32 *, S_80090DF0_0 *, s32);

void dispatch_actor_interaction_with_fallback(s32 *value, S_80090DF0_0 *state, s32 context) {
    s32 old_value;

    old_value = *value;
    dispatch_actor_interaction_actions(value, state, context);
    if ((old_value == *value) && (state->unk_0C == 0) && (state->unk_10 == 0)) {
        initialize_scene_action_record(value, state, context);
    }
}
