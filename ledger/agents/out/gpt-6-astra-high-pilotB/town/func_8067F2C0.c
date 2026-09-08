#include "common.h"
#include "m2c_compat.h"

s32 func_80017978();                    /* extern */
s32 func_80018604();                                /* extern */

/* Returns whether the check succeeds when the threshold of ten is met. */
s32 func_8067F2C0(s32 check_value, M2C_UNK check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80018604() >= 0xA) {
        check_passed = func_80017978(check_value, check_data) != 0;
    }
    return check_passed;
}
