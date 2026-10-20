#include "script_symbols.h"
#include "common.h"
void func_80018570(s32);                     /* extern */
s32 func_80018668();                         /* extern */

/* Query 0x146C, process it, and return the saved query result. */
s32 check_inputs_after_threshold_five(void) {
    s32 query_result;

    query_result = func_80018668(F_mama_ret_first);
    func_80018570(F_mama_ret_first);
    return query_result;
}
