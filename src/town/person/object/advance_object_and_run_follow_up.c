#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"

void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);                      /* extern */
s32 func_800CE04C(s32, s32, s32);


/* Advance the object and motion state, then run the follow-up handler for a nonnegative step. */
void advance_object_and_run_follow_up(Rec_func_80094268_arg0 *object, EntityRec *motion, s32 context) {
    object->unk_72.as_u16 = (u16) (object->unk_72.as_u16 + 0x400);
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        func_800CE04C(object, motion, context);
    }
}
