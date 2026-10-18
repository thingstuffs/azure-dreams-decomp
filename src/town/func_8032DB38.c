#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001BDBC[];
extern u8 D_8001C358[];

/* Forward two values to apply_entry_position with the fixed data buffers. */
s32 forward_values_to_fixed_data_handler(s32 first_value, s32 unused, s32 second_value)
{
    return apply_entry_position(D_8001BDBC, D_8001C358, first_value, second_value);
}
