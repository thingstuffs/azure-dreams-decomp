#include "common.h"

/* Calls set_script_flag_bit with ID 0xD81. */
void invoke_event_code_d_81(void) {
    set_script_flag_bit(0xD81);
}
