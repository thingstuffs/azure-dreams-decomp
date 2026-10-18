#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
s32 *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes();              /* extern */
s32 select_object_setup_path(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
void initialize_object_and_data_pointer();    /* extern */
M2C_UNK func_800CDE4C();    /* extern */
extern M2C_UNK D_800CFCB4;

/* Count down when the object is ready and choose its next setup when the timer expires. */
void count_down_and_select_next_setup(Rec_func_80094268_arg0 *object, M2C_UNK request_data, M2C_UNK request_param, s32 check_param) {
    s32 *state;
    u16 ticks_left;

    if ((select_object_setup_path(object, request_data, request_param, check_param) == 0) &&
        ((state = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, &D_800CFCB4), (state == NULL)) || (*state == 2)) &&
        (ticks_left = object->unk_6C.as_u16 - 1,
         object->unk_6C.as_u16 = ticks_left, ((ticks_left << 0x10) <= 0))) {
        if (scale_random_to_unsigned_halfword_limit(2) & 0xFFFF) {
            initialize_object_and_data_pointer(object, request_data, request_param);
            return;
        }
        func_800CDE4C(object, request_data, request_param);
    }
}
