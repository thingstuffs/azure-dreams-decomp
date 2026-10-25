#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object_setup.h"
#include "town/person/state_updates.h"
void choose_random_movement_direction(); /* Slot contract: loading images do not establish one callee contract. */    /* extern */


/* Count down after an unhandled entity update and choose a direction when the timer expires. */
void run_unhandled_update_and_choose_direction(Rec_func_80094268_arg0 *entity, void *motion, void *context, s32 update_arg) {
    u16 ticks_left;

    if (select_object_setup_path(entity, motion, context) == 0) {
        ticks_left = entity->unk_6C.as_u16 - 1;
        entity->unk_6C.as_u16 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            choose_random_movement_direction(entity, motion, context);
        }
    }
}
