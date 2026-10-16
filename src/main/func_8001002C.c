#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Forwards the value to cardBootCreateOrResetMessageDialog with code 12 and two zero arguments. */
void cardBootShowFormatFailureNotice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 0xc, zero, zero);
}
