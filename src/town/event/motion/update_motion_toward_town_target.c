#include "common.h"
#include "town/scene/collision.h"
#include "shared/entity_objects.h"
#include "town/player/position.h"
#include "town/scene/motion.h"
#include "town.h"
#include "town/event/motion.h"
#include "town/event/object.h"

/* Update target-relative motion and advance when the countdown expires. */
void update_motion_toward_town_target(TownObjectRecord *state, struct ColliderView *context, ObjectPosition *motion, struct SpriteFrameState *sprite) {
    u16 ticks_left;

    motion->velocity_x = (view_reference_entity.x.v - motion->x.v) / 2;
    motion->velocity_y = (view_reference_entity.y.v - motion->y.v) / 2;
    add_motion_deltas_to_position(motion);
    apply_bound_adjustments(context, motion);
    resolve_collider_overlaps(context, motion);
    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_object_and_maybe_play_sound(state, context, motion, sprite);
    }
}
