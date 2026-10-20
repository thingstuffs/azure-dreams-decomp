#include "modules/town_ovl_5ff1d0.h"

s32 check_inputs_after_threshold_twenty(s32 check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80018604() >= 0x14) {
        check_passed = func_80017978(check_value, check_data) != 0;
    }
    return check_passed;
}
