#include "common.h"
#include "m2c_compat.h"

void set_linked_flag();                     /* extern */

/* Calls shop_set_indexed_flag with 0x20C and returns the value at 0x80701FBC. */
s32 flag_then_read_word(void) {
    set_linked_flag(0x20C);
    return *(s32 *)0x80701FBC;
}
