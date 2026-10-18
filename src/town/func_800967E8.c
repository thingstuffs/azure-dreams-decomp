#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
void call_the_handler_selects_nonzero_entry();  /* extern */
void store_the_valid_shared_angle_in_offset_hex_10(Rec_func_80094268_arg0 *);                            /* extern */
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58();                     /* extern */
extern s32 D_80091528;
extern M2C_UNK D_800D0098;


/* Initialize the object state, motion, behavior data, and counter. */
void initialize_randomized_object_action(Rec_func_80094268_arg0 *object, s32 motion, s32 table_arg) {
    object->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(motion);
    call_the_handler_selects_nonzero_entry(&D_800D0098, object, table_arg);
    object->unk_00.as_pm = &D_80091528;
    object->unk_0A.as_s16 = (s16) (scale_random_to_unsigned_halfword_limit(2) + 0xC);
}
