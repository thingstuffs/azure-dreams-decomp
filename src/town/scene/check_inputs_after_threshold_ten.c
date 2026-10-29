#include "modules/town_ovl_5ff1d0.h"
#include "town/scene.h"

/*
 * Returns whether func_80017978 accepts the supplied inputs, skipping that call until
 * func_80018604 reaches 10.
 */
s32 check_inputs_after_threshold_ten(s32 check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80018604() >= 0xA) {
        check_passed = func_80017978(check_value, check_data) != 0;
    }
    return check_passed;
}
