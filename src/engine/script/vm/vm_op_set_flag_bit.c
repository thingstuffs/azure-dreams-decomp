#include "common.h"
#include "engine/script.h"

#include "common.h"

extern s32 set_resident_bitmap_bit(s32 value);

/* Consumes a signed little-endian 16-bit script operand and passes it to set_resident_bitmap_bit. */
s32 vm_op_12_set_flag_bit(ScriptReader *state) {
    u8 *data;
    s32 low;
    s32 high;

    data = state->cursor;
    low = data[0];
    high = data[1];
    state->cursor = data + 2;
    high <<= 8;
    low += high;
    return set_resident_bitmap_bit((s16)low);
}
