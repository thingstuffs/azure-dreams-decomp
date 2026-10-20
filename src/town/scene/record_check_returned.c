#include "common.h"

extern u32 process_checked_entry(s32 object, s32 entryIndex);
extern void clear_script_flag_bit(s32 bit_index);
extern u8 D_8001F15A[];

/* Record whether the check returned zero and invoke the handler when it did. */
s32 record_check_returned(s32 check_input_1, s32 check_input_2) {
    s32 result;

    result = process_checked_entry(check_input_1, check_input_2);
    if (result != 0) {
        D_8001F15A[0] = 0;
    } else {
        D_8001F15A[0] = 1;
        clear_script_flag_bit(0xD7A);
    }
    return result;
}
