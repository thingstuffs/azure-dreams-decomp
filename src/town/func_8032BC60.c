#include "common.h"

/* Invokes set_script_flag_bit with code 0xDAF. */
void dispatch_event_daf(void) {
    set_script_flag_bit(0xDAF);
}
