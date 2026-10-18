#include "common.h"

extern void set_script_flag_bit(s32);
extern void clear_script_flag_bit(s32);

/* Dispatches consecutive indices to one of two handlers according to successive mask bits. */
void write_script_flag_range(s32 base, s32 bits, s32 count)
{
    s32 offset;

    for (offset = 0; offset < count; offset++) {
        if (bits & 1) {
            set_script_flag_bit(base + offset);
        } else {
            clear_script_flag_bit(base + offset);
        }
        bits >>= 1;
    }
}
