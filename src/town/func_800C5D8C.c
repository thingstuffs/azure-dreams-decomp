#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

s32 select_object_setup_path(void *object, s32 request_data, s32 request_param, s32 check_param);
void choose_random_movement_direction();    /* extern */


/* Count down after an unhandled entity update and choose a direction when the timer expires. */
void run_unhandled_update_and_choose_direction(Rec_func_80094268_arg0 *entity, s32 motion, s32 context, s32 update_arg) {
    u16 ticks_left;

    if (select_object_setup_path(entity, motion, context, update_arg) == 0) {
        ticks_left = entity->unk_6C.as_u16 - 1;
        entity->unk_6C.as_u16 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            choose_random_movement_direction(entity, motion, context);
        }
    }
}
