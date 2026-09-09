#include "common.h"
#include "m2c_compat.h"

M2C_UNK set_item_w0(); /* extern */

/* Handles the mam_bita_give script call. */
void mam_bita_give(void) {
    set_item_w0(1, 2, 0, 0);
}
