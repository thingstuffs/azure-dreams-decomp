#include "common.h"
void func_80018FDC(s32, s32);             /* extern */

/* Calls func_80018FDC with the supplied value and a zero second argument. */
void call_value_handler_mode_0(s32 value) {
    func_80018FDC(value, 0);
}
