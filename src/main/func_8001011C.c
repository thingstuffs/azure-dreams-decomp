#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Passes value to cardBootCreateOrResetMessageDialog with 0x11 and two zero arguments. */
void cardBootShowOverwriteProtectedNotice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 0x11, zero, zero);
}
