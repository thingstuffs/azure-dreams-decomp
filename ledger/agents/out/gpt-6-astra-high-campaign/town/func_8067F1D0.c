#include "common.h"
#include "m2c_compat.h"

s32 func_80017978();                    /* extern */
s32 func_80018604();                                /* extern */

/* Check the supplied inputs only when the prerequisite value is at least 5. */
s32 func_8067F1D0(s32 check_value, M2C_UNK check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80018604() >= 5) {
        check_passed = func_80017978(check_value, check_data) != 0;
    }
    return check_passed;
}
