#include "common.h"
#include "m2c_compat.h"

void townInvokeHandlerWithCode799();                     /* extern */

/* Calls townInvokeHandlerWithCode799 with 0xFA3 and returns zero. */
s32 func_806011BC(void) {
    townInvokeHandlerWithCode799(0xFA3);
    return 0;
}
