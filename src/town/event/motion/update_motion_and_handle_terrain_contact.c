#include "shared/position_query.h"
#include "common.h"
#include "shared/entity.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/object_links.h"

typedef void (*Callback)(void *, void *, void *, s32);


   /* the 0x2 bytes before arg0 in update_motion_and_handle_terrain_contact, addressed as arg0[-1] */

typedef struct S_8009B6B4_2 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8009B6B4_2;   /* arg0 in update_motion_and_handle_terrain_contact */


extern void add_hex_20000_s_signed_offset_hex_14(void *);
extern void add_motion_deltas_to_position(void *);
extern s16 get_smaller_query_result_capped_hex_80_writes_associated_output(void *, void *);
extern void set_the_state_flag_initialize_s_fixed_point_clear_paired_field(void *, void *, s16);
extern s32 call_the_same_context_both_processing_routines(void *, void *);
extern void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);
extern s32 read_map_cell_at_world_position(s16, s16);
extern s32 check_masked_value_in_current_range(u16);
extern void SD_Call(u32);

extern u8 D_8009B454[];
extern s16 terrain_height_limits[];

/* Update object motion, handle contact, and play the tile height sound. */
void update_motion_and_handle_terrain_contact(void *object, Rec_D_800CFCB4 *collision, ObjectPosition *motion, s32 callback_arg) {
    s16 contact_height;
    s32 contact_height_ext;

    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->velocity_z > 0x200000) {
        motion->velocity_z = 0x200000;
    }
    add_motion_deltas_to_position(motion);
    contact_height = get_smaller_query_result_capped_hex_80_writes_associated_output(motion, ((u8 *)&position_query_scratch));
    call_the_same_context_both_processing_routines(collision, motion);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(collision, motion);
    contact_height_ext = contact_height;
    if (motion->z.w.i >= contact_height_ext) {
        set_the_state_flag_initialize_s_fixed_point_clear_paired_field(collision, motion, contact_height_ext);
        ((Callback *)(*(void **)((u8 *)object + 0x58)))[1](object, collision, motion, callback_arg);
    } else if (collision->unk_3B != 0) {
        motion->velocity_z = 0;
        ((Callback *)(*(void **)((u8 *)object + 0x58)))[1](object, collision, motion, callback_arg);
    }
    if ((((ObjectRetirementFlags *)object)[-1].unk_00 & 0x8000) == 0 &&
        D_8009B454 == ((S_8009B6B4_2 *)object)->unk_50) {
        s32 tile_type;

        tile_type = check_masked_value_in_current_range((u16)read_map_cell_at_world_position(
            motion->x.w.i, motion->y.w.i));
        if (tile_type != 0) {
            s16 *thresholds = terrain_height_limits;
            s16 height = motion->z.w.i;
            s16 threshold = thresholds[tile_type];

            if (height > threshold) {
                SD_Call(0x517);
            }
        }
    }
}
