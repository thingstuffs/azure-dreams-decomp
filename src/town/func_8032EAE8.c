#include "common.h"
#include "m2c_compat.h"

void process_lshop_entries(s32, s32);             /* extern */

/* Calls process_lshop_entries with the supplied value and a zero second argument. */
void process_lshop_value(s32 value) {
    process_lshop_entries(value, 0);
}
