#include "common.h"
#include "m2c_compat.h"

s32 townGetScriptFlagMask();                     /* extern */

/* Calls townGetScriptFlagMask with ID 0x12C2 and returns 1. */
s32 townQueryEvent12C2AndReturnOne(void) {
    townGetScriptFlagMask(0x12C2);
    return 1;
}
