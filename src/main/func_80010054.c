#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Forwards the input value with 0xD and two zero arguments to cardBootCreateOrResetMessageDialog. */
void cardBootShowFormatSuccessNotice(s32 input_value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(input_value, 0xd, zero, zero);
}
