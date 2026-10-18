#include "common.h"
#include "shared/game_work.h"


typedef struct State {
    s32 unk0;
    s32 unk4;
    s32 flags;
} State;

void update_actor_ground_and_input(s32 *, s32, s32);
void initialize_scene_action_record();

/* Calls initialize_scene_action_record if update_actor_ground_and_input leaves the value unchanged and flag 0x20 is clear. */
void update_input_and_fallback_action(s32 *value, s32 input_a, s32 input_b) {
    GameWork *state;
    s32 old_value;

    state = &g_game_work;
    old_value = *value;
    update_actor_ground_and_input(value, input_a, input_b);
    if ((old_value == *value) && !(state->buttons & 0x20)) {
        initialize_scene_action_record(value, input_a, input_b);
    }
}
