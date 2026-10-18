#include "common.h"
#include "m2c_compat.h"

void set_script_flag_bit();                     /* extern */

/* Process IDs 0x1462, 0x1474, and 0xD89 in sequence. */
void dispatch_three_progress_events(void) {
    set_script_flag_bit(0x1462);
    set_script_flag_bit(0x1474);
    set_script_flag_bit(0xD89);
}
