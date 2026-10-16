#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Forward the target and value to cardBootCreateOrResetMessageDialog with fixed parameters 6 and 2. */
void cardBootShowSavingProgress(M2C_UNK target, M2C_UNK value) {
    cardBootCreateOrResetMessageDialog(target, 6, 2, value);
}
