#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Initialize a type-5, mode-1 context with the supplied owner and data. */
void cardBootShowOverwriteConfirmation(M2C_UNK owner, M2C_UNK data) {
    cardBootCreateOrResetMessageDialog(owner, 5, 1, data);
}
