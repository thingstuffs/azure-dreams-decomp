/* Dispatch shop values with the required entry processing mode. */

#include "common.h"
#include "m2c_compat.h"


void process_lshop_entries(s32, s32);             /* extern */

/* Calls process_lshop_entries with the supplied value and a zero second argument. */
void process_lshop_entries();                /* extern */

/* Calls process_lshop_entries with value, 0. */
void process_lshop_value(s32 value) {
    process_lshop_entries(value, 0);
}


/* Forwards the base value plus four to process_lshop_entries with mode 1. */
void process_lshop_value_plus_four(s32 base_value) {
    process_lshop_entries(base_value + 4, 1);
}
