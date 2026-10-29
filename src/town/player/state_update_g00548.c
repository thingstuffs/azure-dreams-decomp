/* Advance and update the player state (G00548). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009D728, PD:town/engine:800D0620. */
#include "town/player/state_update_g00548.h"
#include "town/player.h"

/* Update the entity state and handler from global flags and the signed counter. */
void update_player_global_state(Entity *entity, void *ptr, void *ptr2) {
    GameWork *state = &g_game_work;
    s32 adjustment;

    if (((u32)state->pressed_buttons) & 0x40) {
        entity->unkA = 4;
        call_the_handler_selects_nonzero_entry((s32 *) D_800D0190, (Rec_func_80094268_arg0 *) entity, ptr2);
        entity->unk4 = D_8009B0EC;
    } else if ((((u32)state->pressed_buttons) & 0x1000) && ((adjustment = town_player_target_adjustment) >= 0)) {
        town_player_target_adjustment = adjustment - 1;
        entity->unk10 = 0x800;
        entity->unkA = 4;
        call_the_handler_selects_nonzero_entry((s32 *) player_interaction_handler_entries, (Rec_func_80094268_arg0 *) entity, ptr2);
        entity->unk4 = D_8009B014;
    } else if ((((u32)state->pressed_buttons) & 0x4000) && ((adjustment = town_player_target_adjustment) <= 0)) {
        town_player_target_adjustment = adjustment + 1;
        entity->unk10 = 0;
        entity->unkA = 4;
        call_the_handler_selects_nonzero_entry((s32 *) player_interaction_handler_entries, (Rec_func_80094268_arg0 *) entity, ptr2);
        entity->unk4 = D_8009B014;
    }
}

/* Decrement the countdown, switch the state's table on expiry, and update the state. */
void advance_player_state_table(Struct8009D814 *state, s32 update_arg, s32 shared_arg) {
    s16 countdown;

    countdown = state->unkA - 1;
    state->unkA = countdown;
    if (countdown <= 0) {
        call_the_handler_selects_nonzero_entry((s32 *)town_scene_record_handlers, (Rec_func_80094268_arg0 *)state, (void *)shared_arg);
        state->unk4 = D_8009AFF4;
    }
    update_player_global_state((Entity *)state, (void *)update_arg, (void *)shared_arg);
}

/* Forward the object and values to update_player_global_state. */
void forward_player_state_update(void *object, s32 value_1, s32 value_2) {
    update_player_global_state((Entity *)object, (void *)value_1, (void *)value_2);
}
