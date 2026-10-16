#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Passes the value and fixed arguments (7, 0, 0) to cardBootCreateOrResetMessageDialog. */
void cardBootShowNoSavedGameNotice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 7, zero, zero);
}
