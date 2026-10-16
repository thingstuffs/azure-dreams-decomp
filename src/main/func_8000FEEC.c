#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Starts mode 8 for the owner with no additional parameters. */
void cardBootShowOverwriteFailureNotice(s32 owner) {
    cardBootCreateOrResetMessageDialog(owner, 8, 0, 0);
}
