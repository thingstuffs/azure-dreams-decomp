/* Dispatch shop values with the required entry processing mode. */

#include "common.h"
#include "m2c_compat.h"
#include "town/shop/state/set_lshop_special_flag_g00699.h"
#include "town/system.h"



/* Calls apply_shop_transaction with the supplied value and a zero second argument. */

/* Calls apply_shop_transaction with value, 0. */
void buy_flagged_entries(void *value) {
    apply_shop_transaction(value, 0);
}


/* Forwards the base value plus four to apply_shop_transaction with mode 1. */
void sell_flagged_entries(u8 *base_value) {
    apply_shop_transaction(base_value + 4, 1);
}
