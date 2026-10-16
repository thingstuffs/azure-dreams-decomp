#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Forwards the input and value with both middle arguments set to 2. */
void cardBootShowPleaseWaitNotice(M2C_UNK input, M2C_UNK value) {
    cardBootCreateOrResetMessageDialog(input, 2, 2, value);
}
