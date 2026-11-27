#include "common.h"
#include "town/scene/collision.h"
#include "shared/object_node.h"
#include "town/player/position.h"
#include "town/scene/motion.h"
#include "sdk/libgte.h"
#include "town/event/motion.h"
#include "dungeon/actor_callbacks_api.h"

extern s32 scene_object_payload_alias;


/* Initialize heading-based motion, apply it to the object, and update the owner state. */
void initialize_heading_motion(TownObjectRecord *owner, ColliderView *object, ObjectPosition *motion) {
    s32 *global_state = &scene_object_payload_alias;
    s32 source_z;
    s32 *x_velocity = &motion->velocity_x;

    object->enabled = 1;
    *x_velocity = rsin(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    motion->velocity_y = rcos(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    motion->velocity_z = 0xFFF20000;
    source_z = NODE_HEADER(global_state)->position->velocity_z;
    if (source_z < 0) {
        motion->velocity_z = source_z + 0xFFF20000;
    }
    add_motion_deltas_to_position(motion);
    resolve_collider_overlaps(object, motion);
    owner->state_callback.as_pm = update_falling_motion;
}
