#include "script_symbols.h"
#include "common.h"

/* Calls set_script_flag_bit with argument 0x12C2. */
void invoke_event_code_12_c_2(void) {
    set_script_flag_bit(F_engei_build);
}
