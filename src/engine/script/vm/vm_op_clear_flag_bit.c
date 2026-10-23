#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "engine/object.h"

/* Consumes a signed little-endian 16-bit script operand and passes it to clear_resident_bitmap_bit. */
void vm_op_13_clear_flag_bit(ScriptReader *state) {
    u8 *cursor = state->cursor;
    s32 low = cursor[0];
    s32 high = cursor[1];

    state->cursor = cursor + 2;
    clear_resident_bitmap_bit((s16)(low + (high << 8)));
}
