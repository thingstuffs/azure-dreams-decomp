#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town.h"
#include "town/player/position.h"
#include "town/player/state.h"
#include "town/data.h"

extern void dispatch_selected_entry_if_nonzero(void *, void *,void *);
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

/* Updates countdown-driven motion and invokes callbacks at selected ticks. */
void update_actor_action_state(TownObjectRecord *state, ObjectPosition *motion, s32 callback_arg) {
    s16 ticks_left;
    s32 target_position;

    resolve_collision_axis_order(motion);
    if (state->unk_0A >= 15) {
        target_position = (s32)((u32)(state->unk_34 +
                   D_800D0454[21 - state->unk_0A]) << 16);
    } else {
        target_position = (s32)((u32)state->unk_34 << 16);
    }


    if (state->unk_0A == 19)
        dispatch_selected_entry_if_nonzero(&timed_scene_handler_entries, state, callback_arg);
    if (state->unk_0A == 15)
        dispatch_selected_entry_if_nonzero(&D_800D00F0, state, callback_arg);
    if (state->unk_0A == 12)
        dispatch_selected_entry_if_nonzero(&D_800D00F8, state, callback_arg);
    ticks_left = (u16)state->unk_0A - 1;
    state->unk_0A = ticks_left;
    if ((s32)((u32)(u16)ticks_left << 16) <= 0) {
        motion->velocity_x = 0;
        motion->velocity_y = 0;
        motion->velocity_z = 0;
        init_height_interpolation_action(state, motion, callback_arg);
        return;
    }
    motion->velocity_z = target_position - motion->z.v;
}
