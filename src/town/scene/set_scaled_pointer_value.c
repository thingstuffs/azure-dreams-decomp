#include "common.h"
#include "shared/record_ptrs.h"


/* Stores (value + 1) * 16 through the global object's pointer at offset 0x1C. */
void set_scaled_pointer_value(s32 value)
{
    s32 *value_ptr = *(s32 **)((u8 *)(&D_80016000));
    value_ptr = *(s32 **)((u8 *)value_ptr + 0x1C);
    *value_ptr = (value + 1) * 0x10;
}
