#include "common.h"
#include "m2c_compat.h"

s32 func_800173CC();                    /* extern */
s32 func_80017FEC();                                /* extern */

/* Check the supplied inputs only when the prerequisite value is at least 2. */
s32 func_80016250(s32 check_value, M2C_UNK check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80017FEC() >= 2) {
        check_passed = func_800173CC(check_value, check_data) != 0;
    }
    return check_passed;
}
