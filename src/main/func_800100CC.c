#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Initialize the owner's request with type 0xf, mode 2, and its data. */
void cardBootShowCopyingProgress(M2C_UNK owner, M2C_UNK data) {
    cardBootCreateOrResetMessageDialog(owner, 0xf, 2, data);
}
