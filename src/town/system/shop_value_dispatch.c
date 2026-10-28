/* Dispatch shop values with the required entry processing mode. */

#include "common.h"
#include "m2c_compat.h"
#include "town/shop/state/set_lshop_special_flag_g00699.h"


             /* extern */

/* Calls process_lshop_entries with the supplied value and a zero second argument. */
                /* extern */

/* Calls process_lshop_entries with value, 0. */
void process_lshop_value(void *value) {
    process_lshop_entries(value, 0);
}


/* Forwards the base value plus four to process_lshop_entries with mode 1. */
void process_lshop_value_plus_four(u8 *base_value) {
    process_lshop_entries(base_value + 4, 1);
}
