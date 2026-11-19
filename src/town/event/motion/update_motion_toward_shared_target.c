#include "common.h"
#include "town/scene/collision.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "town/player/position.h"
#include "town/scene/motion.h"
#include "town.h"
#include "town/event/motion.h"
#include "town/menu/indexed_effect_vectors_g00583.h"


/* Update motion toward the shared target and advance state when the countdown expires. */
void update_motion_toward_shared_target(TownObjectRecord *state, struct ColliderView *context, ObjectPosition *motion, struct SpriteFrameState *sprite) {
    s32 position;
    u16 ticks_left;

    position = motion->z.v;
    motion->velocity_z = (s32) ((s32) ((view_reference_entity.z.v + town_target_height_offset) - position) / 2);
    add_motion_deltas_to_position(motion);
    apply_bound_adjustments(context, motion);
    resolve_collider_overlaps(context, motion);
    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_target_motion(state, context, motion, sprite);
    }
}
