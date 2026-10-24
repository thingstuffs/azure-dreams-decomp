#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "engine/object.h"

/* Opcode 0x0D: Clear the event flag given by the 16-bit operand. */
void script_clear_flag(ScriptReader *state) {
    u8 *cursor = state->cursor;
    s32 low = cursor[0];
    s32 high = cursor[1];

    state->cursor = cursor + 2;
    clear_resident_bitmap_bit((s16)(low + (high << 8)));
}
