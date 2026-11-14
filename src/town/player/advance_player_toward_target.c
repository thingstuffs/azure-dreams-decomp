#include "common.h"
#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "town/player.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/object.h"
#include "town/data.h"
#include "town/player/record.h"


extern s32 town_scene_record_handlers[];
extern s32 D_800D0640[3];

/* Updates motion toward the target and advances the state when the countdown expires. */
void advance_player_toward_target(void *state_arg, ObjectPosition *motion, void *context) {
    TownPlayerRecord *state = state_arg;
    u16 ticks_left;
    s32 target_index;
    s32 *target_bases;
    s32 *target_base;

    target_index = town_player_target_adjustment;
    target_bases = D_800D0640;
    target_base = target_bases + target_index;
    motion->velocity_y = (s32) ((u32) (state->unk_32 * 0x10000) + (u32) *target_base
        - (u32) motion->y.v) / (s16)state->timer;
    ticks_left = (u16) state->timer - 1;
    state->timer = ticks_left;
    if (((s16) ticks_left * 0x10000) <= 0) {
        motion->y.v = (s32) ((u32) (state->unk_32 * 0x10000) + (u32) *target_base);
        clear_object_velocity(motion);
        state->unk_10 = 0x400;
        state->timer = 0xA;
        dispatch_selected_entry_if_nonzero(town_scene_record_handlers, state_arg, context);
        state->unk_04 = forward_player_state_update;
    }
}
