#include "common.h"

s32 func_800173CC();                    /* extern */
s32 func_80017FEC();                                /* extern */

/* Check the supplied inputs only when the prerequisite value is positive. */
s32 check_inputs_after_positive_threshold(s32 check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80017FEC() > 0) {
        check_passed = func_800173CC(check_value, check_data) != 0;
    }
    return check_passed;
}
