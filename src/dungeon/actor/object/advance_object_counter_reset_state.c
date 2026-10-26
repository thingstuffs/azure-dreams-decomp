#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern s32 initialize_object_entries(void *,s8 *, s32 *);
extern void apply_setup_on_timeout_variant_3(Rec_func_80094268_arg0 *object);
extern s32 D_800D6938[];


/* Decrement the object's counter and switch state with a ten-tick counter when it expires. */
void advance_object_counter_and_reset_state(Rec_func_80094268_arg0 *object, s32 unused, void *context) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_object_entries(object, context, D_800D6938);
        object->unk_54 = &apply_setup_on_timeout_variant_3;
        object->unk_6C.as_u16 = 0xAU;
    }
}
