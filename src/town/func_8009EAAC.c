#include "common.h"

extern s32 func_800644B8(s32 value_a);
extern s32 func_80064584(s32 value_b);
extern void add_motion_deltas_to_position(void *motion);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *collider, void *position);
extern s32 D_800834B8;
extern void *D_8009BC44;

/* Initialize heading-based motion, apply it to the object, and update the owner state. */
void initialize_heading_motion(void *owner, void *object, void *motion) {
    s32 *global_state = &D_800834B8;
    s32 source_z;

    *(s8 *)((u8 *)object + 0x15) = 1;
    *(s32 *)((u8 *)motion + 0xC) = func_800644B8(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    *(s32 *)((u8 *)motion + 0x10) = func_80064584(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    *(s32 *)((u8 *)motion + 0x14) = 0xFFF20000;
    source_z = *(s32 *)((u8 *)(*(void **)((u8 *)global_state - 0x18)) + 0x14);
    if (source_z < 0) {
        *(s32 *)((u8 *)motion + 0x14) = source_z + 0xFFF20000;
    }
    add_motion_deltas_to_position(motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(object, motion);
    *(void **)((u8 *)owner + 0x50) = &D_8009BC44;
}
