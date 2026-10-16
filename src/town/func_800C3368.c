#include "common.h"
#include "m2c_compat.h"

s32 townStoreRecordValueAndTableLookup(); /* extern */

/* func_koya_tamago_pal_ld: load the hut egg palette. */
void scr_func_koya_tamago_pal_ld(void) {
    townStoreRecordValueAndTableLookup(0, 0, 0, 0);
}
