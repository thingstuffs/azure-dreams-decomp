#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Passes value, 11, and two zero arguments to cardBootCreateOrResetMessageDialog. */
void cardBootShowLoadFailureNotice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 0xb, zero, zero);
}
