#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Forwards value to cardBootCreateOrResetMessageDialog with code 0x10 and two zero arguments. */
void cardBootShowCopyFailureNotice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 0x10, zero, zero);
}
