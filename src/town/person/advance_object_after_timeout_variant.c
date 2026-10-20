#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_object_entries();  /* extern */
s32 create_offset_effect_object();                     /* extern */
extern M2C_UNK D_800C84B8;
extern M2C_UNK D_800D62AC;


/* Decrement the object's countdown and advance its state when it expires. */
void advance_object_after_timeout_variant_1(Rec_func_80094268_arg0 *object, s32 update_context, s32 state_context) {
    u16 ticks_left;

    ticks_left = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        create_offset_effect_object(update_context);
        initialize_object_entries(object, state_context, &D_800D62AC);
        object->unk_54 = &D_800C84B8;
        object->unk_6C.as_u16 = 0x15U;
    }
}
