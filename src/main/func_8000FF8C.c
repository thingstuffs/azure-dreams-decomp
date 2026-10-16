#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Dispatches request 14 with parameter 2 for the parent and its status pointer. */
void cardBootShowLoadingProgress(M2C_UNK parent, M2C_UNK status) {
    cardBootCreateOrResetMessageDialog(parent, 0xe, 2, status);
}
