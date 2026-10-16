#include "common.h"
#include "m2c_compat.h"

s32 townHandleEvaluatePositionAfterSubtractingStoredOffsetFirstComponent();                           /* extern */
s32 func_8008F41C();                           /* extern */
void townSetTheControlFlagInitializesClearedTrailingField();             /* extern */
void townSetTheFlagInitializesState();             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void townApplyUpperLowerBoundaryAdjustmentsFixedPoint(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = townHandleEvaluatePositionAfterSubtractingStoredOffsetFirstComponent(value) << 0x10;
    if (*value >= upper_bound) {
        townSetTheControlFlagInitializesClearedTrailingField(context, value, upper_bound);
    }
    lower_bound = (func_8008F41C(value) << 0x10) - 1;
    if (lower_bound >= *value) {
        townSetTheFlagInitializesState(context, value, lower_bound);
    }
}
