#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "town/player/action_initializers.h"



extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(EntityRec *position);

/* Advance interpolation toward the target and finish when the countdown expires. */
void interpolate_actor_height_until_timeout(Rec_func_80094268_arg0 *state, EntityRec *motion, void *context) {
    s32 target_pos;
    u16 ticks_left;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(motion);
    ticks_left = state->unk_0A.as_u16 - 1;
    target_pos = state->unk_34.as_s16 << 0x10;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left <= 0) {
        motion->unk_0C = 0;
        motion->unk_10 = 0;
        motion->flags14 = 0;
        motion->z.v = (s32) (state->unk_34.as_s16 << 0x10);
        initialize_scene_action_record(state, motion, context);
        return;
    }
    motion->flags14 =
        (s32) ((s32) (target_pos - motion->z.v) /
               (s16) ticks_left);
}
