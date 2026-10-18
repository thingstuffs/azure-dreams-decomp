#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_record_with_handler_table(void *, s32, s32);                            /* extern */

/* Forward the object and values to initialize_record_with_handler_table. */
void forward_player_motion_update(void *object, s32 value_1, s32 value_2) {
    initialize_record_with_handler_table(object, value_1, value_2);
}
