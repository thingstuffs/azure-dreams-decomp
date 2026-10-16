#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Start operation 4 in mode 2 with the owner and status flag. */
void cardBootShowFormattingProgress(M2C_UNK owner, M2C_UNK status_flag) {
    cardBootCreateOrResetMessageDialog(owner, 4, 2, status_flag);
}
