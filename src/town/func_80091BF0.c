#include "common.h"
#include "m2c_compat.h"

s32 townCheckThePositionSecondCoordinateAdjustedStoredOffset();                           /* extern */
s32 func_8008F4BC();                           /* extern */
void townSetTheFlagStoreStateClearStateSSecondaryField();             /* extern */
void townSetTheFlagInitializeAssociatedState();             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void func_8008F350(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = townCheckThePositionSecondCoordinateAdjustedStoredOffset(value) << 0x10;
    if (value[1] >= upper_bound) {
        townSetTheFlagStoreStateClearStateSSecondaryField(context, value, upper_bound);
    }
    lower_bound = (func_8008F4BC(value) << 0x10) - 1;
    if (lower_bound >= value[1]) {
        townSetTheFlagInitializeAssociatedState(context, value, lower_bound);
    }
}
