#include "common.h"
#include "m2c_compat.h"

s16 set_or_clear_actor_status_slot();            /* extern */

/* Process the target with parameters 7 and 0x10 and report success. */
s32 process_target_with_action_seven(M2C_UNK target) {
    set_or_clear_actor_status_slot(target, 7, 0x10);
    return 1;
}
