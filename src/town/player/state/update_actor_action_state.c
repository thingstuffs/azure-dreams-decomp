#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"


extern s32 init_height_interpolation_action(void *, void *, s32);
extern void call_the_handler_selects_nonzero_entry(void *, void *,void *);
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(void *);
extern s32 timed_scene_handler_entries;
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

/* Updates countdown-driven motion and invokes callbacks at selected ticks. */
void update_actor_action_state(Rec_func_80094268_arg0 *state, EntityRec *motion, s32 callback_arg) {
    s16 ticks_left;
    s32 target_position;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(motion);
    if (state->unk_0A.as_s16 >= 15) {
        target_position = (s32)((u32)(state->unk_34.as_s16 +
                   D_800D0454[21 - state->unk_0A.as_s16]) << 16);
    } else {
        target_position = (s32)((u32)state->unk_34.as_s16 << 16);
    }


    if (state->unk_0A.as_s16 == 19)
        call_the_handler_selects_nonzero_entry(&timed_scene_handler_entries, state, callback_arg);
    if (state->unk_0A.as_s16 == 15)
        call_the_handler_selects_nonzero_entry(&D_800D00F0, state, callback_arg);
    if (state->unk_0A.as_s16 == 12)
        call_the_handler_selects_nonzero_entry(&D_800D00F8, state, callback_arg);
    ticks_left = (u16)state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = ticks_left;
    if ((s32)((u32)(u16)ticks_left << 16) <= 0) {
        motion->unk_0C = 0;
        motion->unk_10 = 0;
        motion->flags14 = 0;
        init_height_interpolation_action(state, motion, callback_arg);
        return;
    }
    motion->flags14 = target_position - motion->z.v;
}
