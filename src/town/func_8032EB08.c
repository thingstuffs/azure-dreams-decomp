#include "common.h"
#include "m2c_compat.h"

void process_lshop_entries();                /* extern */

/* Forwards the base value plus four to process_lshop_entries with mode 1. */
void process_lshop_value_plus_four(s32 base_value) {
    process_lshop_entries(base_value + 4, 1);
}
