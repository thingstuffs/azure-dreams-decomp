#include "common.h"
#include "m2c_compat.h"

void set_referenced_object_active_flag();                            /* extern */
void set_script_flag_bit();                     /* extern */

/* Runs set_script_flag_bit with code 0x1452 and its set_referenced_object_active_flag follow-up. */
void process_event_1452_and_refresh(void) {
    set_script_flag_bit(0x1452);
    set_referenced_object_active_flag();
}
