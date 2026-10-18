#include "common.h"
#include "m2c_compat.h"

void invoke_callback_for_four_global_values();                            /* extern */

/* Clears the value at 0x804094E8 and calls invoke_callback_for_four_global_values. */
void func_80019998(void) {
    *(s32 *)0x804094E8 = 0;
    invoke_callback_for_four_global_values();
}
