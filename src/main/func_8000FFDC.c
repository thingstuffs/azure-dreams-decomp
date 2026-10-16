#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Calls cardBootCreateOrResetMessageDialog with the supplied value, 10, and two zero arguments. */
void cardBootShowInsufficientSpaceCardAdvice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 0xa, zero, zero);
}
