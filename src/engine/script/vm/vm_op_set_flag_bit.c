#include "common.h"
#include "engine/script.h"

#include "common.h"

extern s32 set_resident_bitmap_bit(s32 value);

/* Opcode 0x0C: Set the event flag given by the 16-bit operand. */
s32 script_set_flag(ScriptReader *state) {
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
