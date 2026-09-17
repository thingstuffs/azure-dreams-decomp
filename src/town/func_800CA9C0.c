#include "common.h"
#include "m2c_compat.h"

extern void *set_item_w0(s8, s8, s8, s8);

/* Handles the mam_bita_give script call. */
void mam_bita_give(void) {
    set_item_w0(1, 2, 0, 0);
}
