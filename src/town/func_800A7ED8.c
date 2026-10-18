#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"

void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis();           /* extern */
void process_scene_record_update();     /* extern */
void add_motion_deltas_to_position();                      /* extern */
void apply_the_enabled_movement_offsets_adding_z_offset_only_positive();                      /* extern */
void store_position_and_compute_delta();                      /* extern */
void update_the_s_field_10_using_callee_8008_fe_90();                   /* extern */
s32 update_object_and_clear_status_fields();                      /* extern */
void turn_entity_toward_target();     /* extern */
extern s32 D_800903FC[];
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800FE490;


typedef struct S_800A5638_0_pre {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_800A5638_0_pre;   /* the 0x10 bytes before arg0 in update_effect_record_and_dispatch, addressed as arg0[-1] */


/* Updates the record, invokes its handler, clamps values, and dispatches follow-up processing. */
void update_effect_record_and_dispatch(void *handler, EntityRec *record, s32 context) {
    apply_the_enabled_movement_offsets_adding_z_offset_only_positive(record);
    update_the_s_field_10_using_callee_8008_fe_90(&D_800FE490);
    add_motion_deltas_to_position(record);
    update_object_and_clear_status_fields(record);
    store_position_and_compute_delta(record);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(&D_800CFCB4, record);
    ((Rec_func_8009431C_arg0 *)handler)->unk_00.as_x78b360(handler, record, context);
    if (!(((S_800A5638_0_pre *)handler)[-1].unk_0E & 0x8000)) {
        if (record->y.v <= 0x06500000) {
            record->y.v = 0x06500000;
            record->unk_10 = 0x180000;
            if (record->z.v > 0) {
                record->z.v = 0;
            }
        }
        if (((S_800A5638_0_pre *)handler)[-1].unk_00 == &D_800903FC) {
            process_scene_record_update(handler, record, context);
            return;
        }
        turn_entity_toward_target(handler, record, context);
    }
}
