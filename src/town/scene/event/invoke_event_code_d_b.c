#include "script_symbols.h"
#include "common.h"

/* Calls set_script_flag_bit with ID 0xD52. */
void invoke_event_code_d_52(void) {
    set_script_flag_bit(Ftt_pad33);
}
