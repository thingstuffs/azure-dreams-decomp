#include "common.h"
#include "m2c_compat.h"

void invoke_handler_with_code_799();                     /* extern */

/* Calls invoke_handler_with_code_799 with 0xFA3 and returns zero. */
s32 func_806011BC(void) {
    invoke_handler_with_code_799(0xFA3);
    return 0;
}
