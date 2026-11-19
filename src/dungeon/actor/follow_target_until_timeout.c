#include "town/event/object.h"
#include "town/scene/motion.h"
#include "common.h"
#include "shared/entity.h"
#include "town/player/position.h"
#include "dungeon/actor.h"


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 resident_globals_page[];


/* Updates motion toward the target and handles countdown expiration. */
void follow_target_until_timeout(TownObjectRecord *entity, struct ColliderView *context, ObjectPosition *motion, struct SpriteFrameState *completion_data) {
    s32 *target_pos;
    u16 remaining_ticks;

    target_pos = resident_globals_page + 0xDE0;
    motion->velocity_x = (s32) ((s32) (target_pos[0] - motion->x.v) / 2);
    motion->velocity_y = (s32) ((s32) (target_pos[1] - motion->y.v) / 2);
    add_motion_deltas_to_position(motion);
    apply_bound_adjustments(context, motion);
    resolve_collider_overlaps(context, motion);
    remaining_ticks = entity->timer - 1;
    entity->timer = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_object_and_maybe_play_sound(entity, context, motion, completion_data);
    }
}
