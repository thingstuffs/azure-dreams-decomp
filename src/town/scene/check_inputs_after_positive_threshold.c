#include "common.h"
#include "town/scene/record_actions.h"

s32 func_80017FEC(void);                                /* extern */

/* Check the supplied inputs only when the prerequisite value is positive. */
s32 check_inputs_after_positive_threshold(Rec_func_800165F4_arg0 *check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (func_80017FEC() > 0) {
        check_passed = func_800173CC(check_value, check_data) != 0;
    }
    return check_passed;
}
