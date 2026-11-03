#include "town/player/position_handlers.h"
#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "town/player/action_initializers.h"
#include "town/player.h"
#include "town/player/position.h"

/* Advance interpolation toward the target and finish when the countdown expires. */
void interpolate_actor_height_until_timeout(TownObjectRecord *state, ObjectPosition *motion, void *context) {
    s32 target_pos;
    u16 ticks_left;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(motion);
    ticks_left = state->unk_0A.as_u16 - 1;
    target_pos = state->unk_34.as_s16 << 0x10;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left <= 0) {
        motion->velocity_x = 0;
        motion->velocity_y = 0;
        motion->velocity_z = 0;
        motion->z.v = (s32) (state->unk_34.as_s16 << 0x10);
        initialize_scene_action_record(state, motion, context);
        return;
    }
    motion->velocity_z =
        (s32) ((s32) (target_pos - motion->z.v) /
               (s16) ticks_left);
}
