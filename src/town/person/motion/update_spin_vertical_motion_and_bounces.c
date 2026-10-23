#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

extern void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);
extern s16 query_lowered_transform_position(void *position);
s32 select_object_setup_path();         /* extern */
s32 func_800CDE9C();     /* extern */
s32 func_800CDFF8();

/* Update spin and vertical motion, then handle ground contact and remaining bounces. */
void update_spin_vertical_motion_and_bounces(Rec_func_80094268_arg0 *entity, EntityRec *motion, s32 context) {
    s16 remaining_bounces;

    entity->unk_72.as_u16 = (u16) (entity->unk_72.as_u16 + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        remaining_bounces = entity->unk_90.as_s16 - 1;
        entity->unk_90.as_s16 = remaining_bounces;
        if (remaining_bounces <= 0) {
            motion->flags14 = 0;
            entity->unk_72.as_u16 = (u16) entity->unk_6E;
            func_800CDE9C(entity, motion, context);
            return;
        }
        if (select_object_setup_path(entity, motion, context) == 0) {
            func_800CDFF8(entity, motion, context);
            return;
        }
    } else {
        add_hex_20000_s_signed_offset_hex_14(motion);
    }
}
