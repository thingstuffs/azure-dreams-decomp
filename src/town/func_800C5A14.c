#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033D08();                      /* extern */
void unlink_scene_list_node();                      /* extern */
s32 classify_object_against_bounds(Rec_func_80094268_arg0 *, s32);                                /* extern */
void clear_object_slot_and_mark_removed();                      /* extern */
void update_object_motion_and_flags();    /* extern */
extern M2C_UNK D_800C3960;


/* Update the object motion or clear its state and clean it up when the position check fails. */
void update_object_position_or_cleanup(Rec_func_80094268_arg0 *object, s32 position, s32 motion) {
    s32 check_result;
    s8 *state_flag;

    check_result = classify_object_against_bounds(object, position);
    if (check_result != 0) {
        if ((check_result != 2) || (object->unk_50.as_s32 != &D_800C3960)) {
            unlink_scene_list_node(object);
            state_flag = object->unk_98;
            if (state_flag != NULL) {
                *state_flag = 0;
            }
            func_80033D08(object);
            clear_object_slot_and_mark_removed(object);
            return;
        }
        update_object_motion_and_flags(object, position, motion);
        return;
    }
    update_object_motion_and_flags(object, position, motion);
}
