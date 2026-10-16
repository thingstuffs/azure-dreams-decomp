#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Initializes a request with selector 0 and mode 1. */
void cardBootShowFormatConfirmation(M2C_UNK request_id, M2C_UNK request_value) {
    cardBootCreateOrResetMessageDialog(request_id, 0, 1, request_value);
}
