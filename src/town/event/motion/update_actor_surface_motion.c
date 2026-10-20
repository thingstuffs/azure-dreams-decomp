#include "shared/position_query.h"
#include "common.h"

extern s16 get_smaller_query_result_capped_hex_80_writes_associated_output(void *, void *);
extern void set_the_state_flag_initialize_s_fixed_point_clear_paired_field(void *, void *, s16);
extern void call_the_same_context_both_processing_routines(void *, void *);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);
extern void dispatch_active_town_object_script(void *, void *, void *, void *);
extern void set_actor_drop_state(void *, void *, void *, void *);

extern u8 D_8009B454[];
extern u8 D_8009B594[];
extern u8 D_8009BDC0[];

/* Update movement and height, transition the actor state, and copy its value to the context. */
void update_actor_surface_motion(void *actor, void *subject, void *motion, void *context) {
    s16 surface_height;
    void *actor_callback;
    s32 *actor_value;

    surface_height = get_smaller_query_result_capped_hex_80_writes_associated_output(motion, ((u8 *)&D_800FE488));
    call_the_same_context_both_processing_routines(subject, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(subject, motion);
    if (*(u8 *)((u8 *)subject + 0x3B) == 0) {
        if (surface_height - *(s16 *)((u8 *)motion + 0xA) >= 4) {
            set_actor_drop_state(actor, subject, motion, context);
        } else {
            set_the_state_flag_initialize_s_fixed_point_clear_paired_field(subject, motion, surface_height);
            *(s32 *)((u8 *)motion + 0xC) = 0;
            *(s32 *)((u8 *)motion + 0x10) = 0;
            *(s32 *)((u8 *)motion + 0x14) = 0;
            *(void **)((u8 *)actor + 0x50) = D_8009B594;
        }
    }
    dispatch_active_town_object_script(actor, subject, motion, context);
    actor_callback = *(void **)((u8 *)actor + 0x50);
    if (actor_callback != D_8009B454 && actor_callback != D_8009B594 && actor_callback != D_8009BDC0) {
        actor_value = *(s32 **)((u8 *)actor + 0x7C);
        if (actor_value != 0)
            *(s32 *)((u8 *)context + 8) = *actor_value;
    }
}
