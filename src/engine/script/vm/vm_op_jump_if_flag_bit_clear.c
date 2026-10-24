#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "engine/object.h"
#include "engine/script/vm.h"

/* Opcode 0x2B: If the 16-bit event flag is clear, jump to the 32-bit address. */
void script_jump_if_flag_clear(ScriptReader *state) {
    u8 *operand_ptr = state->cursor;
    s32 operand = operand_ptr[0] + (operand_ptr[1] << 8);

    state->cursor = operand_ptr + 2;
    if (test_resident_bitmap_bit((s16)operand) == 0) {
        u8 *target_ptr = state->cursor;

        state->cursor = (u8 *)(target_ptr[0] + (target_ptr[1] << 8) +
                                 (target_ptr[2] << 16) + (target_ptr[3] << 24));
    } else {
        state->cursor += 4;
    }
}
