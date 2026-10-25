#include "common.h"
#include "m2c_compat.h"

s32 store_record_value_and_table_lookup(); /* Slot contract: loading images do not establish one callee contract. */ /* extern */

/* func_koya_tamago_pal_ld: load the hut egg palette. */
void scr_func_koya_tamago_pal_ld(void) {
    store_record_value_and_table_lookup(0, 0, 0, 0);
}
