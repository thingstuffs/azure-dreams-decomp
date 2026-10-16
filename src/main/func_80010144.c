#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Initialize operation 0x12 for the owner with the supplied data. */
void cardBootShowDeleteConfirmation(M2C_UNK owner, M2C_UNK data) {
    cardBootCreateOrResetMessageDialog(owner, 0x12, 1, data);
}
