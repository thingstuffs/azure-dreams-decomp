#include "common.h"
#include "town/scene/collision.h"
#include "shared/object_node.h"
#include "town/player/position.h"
#include "town/scene/motion.h"

extern s32 rsin(s32 value_a);
extern s32 rcos(s32 value_b);
extern s32 scene_object_payload_alias;
extern void *D_8009BC44;

/* Initialize heading-based motion, apply it to the object, and update the owner state. */
void initialize_heading_motion(void *owner, void *object, void *motion) {
    s32 *global_state = &scene_object_payload_alias;
    s32 source_z;

    *(s8 *)((u8 *)object + 0x15) = 1;
    *(s32 *)((u8 *)motion + 0xC) = rsin(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    *(s32 *)((u8 *)motion + 0x10) = rcos(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    *(s32 *)((u8 *)motion + 0x14) = 0xFFF20000;
    source_z = *(s32 *)((u8 *)(((ObjectNodeHeader *)((u8 *)global_state - 0x20))->position) + 0x14);
    if (source_z < 0) {
        *(s32 *)((u8 *)motion + 0x14) = source_z + 0xFFF20000;
    }
    add_motion_deltas_to_position(motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(object, motion);
    *(void **)((u8 *)owner + 0x50) = &D_8009BC44;
}
