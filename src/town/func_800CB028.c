#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void add_hex_20000_s_signed_offset_hex_14();                      /* extern */
void initialize_object_entries();  /* extern */
extern M2C_UNK D_800C86EC;
extern M2C_UNK D_800D6290;


/* Advance the motion state and update the object when its step is nonnegative. */
void check_action_six_eligibility(Rec_func_80094268_arg0 *object, EntityRec *motion, s32 context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        initialize_object_entries(object, context, &D_800D6290);
        object->unk_54 = &D_800C86EC;
    }
}
