#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

void invoke_handler_with_code_799();                     /* extern */

/* Calls invoke_handler_with_code_799 with 0xFA3 and returns zero. */
s32 run_event_fa3(void) {
    invoke_handler_with_code_799(F_shospital_first_hush);
    return 0;
}
