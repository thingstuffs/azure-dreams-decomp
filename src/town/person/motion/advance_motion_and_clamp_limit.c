#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

extern void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);
extern s16 query_lowered_transform_position(void *position);
#include "town/person/object_setup.h"
s32 func_800CDF00();     /* extern */
s32 func_800CDF94();


/* Advance motion, clamp at its limit, and handle the remaining steps. */
void advance_motion_and_clamp_limit(Rec_func_80094268_arg0 *entity, EntityRec *motion, void *context) {
    s16 steps_left;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        steps_left = entity->unk_90.as_s16 - 1;
        entity->unk_90.as_s16 = steps_left;
        if (steps_left <= 0) {
            motion->flags14 = 0;
            func_800CDF94(entity, motion, context);
            return;
        }
        if (select_object_setup_path(entity, motion, context) == 0) {
            func_800CDF00(entity, motion, context);
            return;
        }
    } else {
        add_hex_20000_s_signed_offset_hex_14(motion);
    }
}
