#include "common.h"
void position_decimal_digit_parts(s32);                         /* extern */

/* Calls position_decimal_digit_parts with base + 0x20. */
void forward_offset_to_record_loader(s32 base) {
    position_decimal_digit_parts(base + 0x20);
}
