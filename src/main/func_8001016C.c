#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Dispatches command 0x13 with the supplied argument and two zero arguments. */
void cardBootShowDeleteFailureNotice(s32 command_arg) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(command_arg, 0x13, zero, zero);
}
