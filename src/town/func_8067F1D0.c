#include "modules/town_ovl_5ff1d0.h"

s32 townCheckInputsAfterThresholdFive(s32 check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80018604() >= 5) {
        check_passed = func_80017978(check_value, check_data) != 0;
    }
    return check_passed;
}
