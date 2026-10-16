#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Calls cardBootCreateOrResetMessageDialog with selector 9 and two zero arguments. */
void cardBootShowInsufficientSpaceOverwriteAdvice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 9, zero, zero);
}
