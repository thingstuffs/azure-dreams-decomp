#include "shared/position_query.h"
#include "common.h"

typedef void (*Callback)(void *, void *, void *, s32);

extern void add_hex_20000_s_signed_offset_hex_14(void *);
extern void add_motion_deltas_to_position(void *);
extern s16 get_smaller_query_result_capped_hex_80_writes_associated_output(void *, void *);
extern void set_the_state_flag_initialize_s_fixed_point_clear_paired_field(void *, void *, s16);
extern void call_the_same_context_both_processing_routines(void *, void *);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);
extern s32 read_map_cell_at_world_position(s16, s16);
extern s32 check_masked_value_in_current_range(u16);
extern void SD_Call(s32);

extern u8 actor_surface_callback_address[];
extern s16 terrain_height_limits[];

/* Update motion, handle contact callbacks, and play the terrain height sound. */
void update_motion_and_handle_terrain_contact_alt(void *entity, void *collision, void *motion, s32 callback_arg) {
    s16 contact_height;
    s32 contact_height_s32;

    add_hex_20000_s_signed_offset_hex_14(motion);
    if (*(s32 *)((u8 *)motion + 0x14) > 0x200000) {
        *(s32 *)((u8 *)motion + 0x14) = 0x200000;
    }
    add_motion_deltas_to_position(motion);
    contact_height = get_smaller_query_result_capped_hex_80_writes_associated_output(motion, ((u8 *)&position_query_scratch));
    call_the_same_context_both_processing_routines(collision, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(collision, motion);
    contact_height_s32 = contact_height;
    if (*(s16 *)((u8 *)motion + 0xA) >= contact_height_s32) {
        set_the_state_flag_initialize_s_fixed_point_clear_paired_field(collision, motion, contact_height_s32);
        ((Callback *)(*(void **)((u8 *)entity + 0x58)))[1](entity, collision, motion, callback_arg);
    } else if (*(u8 *)((u8 *)collision + 0x3B) != 0) {
        *(s32 *)((u8 *)motion + 0xC) = 0;
        *(s32 *)((u8 *)motion + 0x10) = 0;
        *(s32 *)((u8 *)motion + 0x14) = 0;
        ((Callback *)(*(void **)((u8 *)entity + 0x58)))[1](entity, collision, motion, callback_arg);
    }
    if ((*(u16 *)((u8 *)entity - 2) & 0x8000) == 0 &&
        *(void **)((u8 *)entity + 0x50) == actor_surface_callback_address) {
        s32 terrain_index;

        terrain_index = check_masked_value_in_current_range((u16)read_map_cell_at_world_position(
            *(s16 *)((u8 *)motion + 2), *(s16 *)((u8 *)motion + 6)));
        if (terrain_index != 0) {
            s16 height = *(s16 *)((u8 *)motion + 0xA);
            s16 terrain_height = terrain_height_limits[terrain_index];

            if (height > terrain_height) {
                SD_Call(0x517);
            }
        }
    }
}
