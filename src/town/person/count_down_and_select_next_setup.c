#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
s32 *get_smallest_signed_overlap_axis_amount_two_intersecting_boxes();              /* extern */
#include "town/person/object_setup.h"
struct Rec_func_80094268_arg0; void initialize_object_and_data_pointer(struct Rec_func_80094268_arg0 *, s32, void *);    /* extern */
void func_800CDE4C(void *, s32, void *);    /* extern */
#include "records/Rec_D_800CFCB4.h"
extern Rec_D_800CFCB4 town_actor_control;

/* Count down when the object is ready and choose its next setup when the timer expires. */
void count_down_and_select_next_setup(Rec_func_80094268_arg0 *object, void *request_data, void *request_param, s32 check_param) {
    s32 *state;
    u16 ticks_left;

    if ((select_object_setup_path(object, request_data, request_param) == 0) &&
        ((state = get_smallest_signed_overlap_axis_amount_two_intersecting_boxes(object, &town_actor_control), (state == 0)) || (*state == 2)) &&
        (ticks_left = object->unk_6C.as_u16 - 1,
         object->unk_6C.as_u16 = ticks_left, ((ticks_left << 0x10) <= 0))) {
        if (scale_random_to_unsigned_halfword_limit(2) & 0xFFFF) {
            initialize_object_and_data_pointer(object, request_data, request_param);
            return;
        }
        func_800CDE4C(object, request_data, request_param);
    }
}
