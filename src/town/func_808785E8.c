#include "common.h"
#include "m2c_compat.h"

void shop_set_indexed_flag();                     /* extern */

/* Calls shop_set_indexed_flag with 0x20C and returns the value at 0x80701FBC. */
s32 shop_prepare_special_value(void) {
    shop_set_indexed_flag(0x20C);
    return *(s32 *)0x80701FBC;
}
