#include "common.h"
void position_decimal_digit_parts(s32);                         /* extern */

/* Calls func_800B2E3C with the input offset by 0x20. */
void forward_offset_to_record_loader(s32 base) {
    position_decimal_digit_parts(base + 0x20);
}
