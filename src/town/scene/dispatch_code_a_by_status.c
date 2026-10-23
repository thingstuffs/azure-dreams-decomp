#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

/*
 * Reads and returns func_80019928 status, passing F_sbs22_pad36 to func_8001A418 for zero or
 * func_8001A490 otherwise.
 */
s32 dispatch_code_7_a_0_by_status(void) {
    s32 status;

    status = func_80019928();
    if (status == 0) {
        func_8001A418(F_sbs22_pad36);
    } else {
        func_8001A490(F_sbs22_pad36);
    }
    return status;
}
