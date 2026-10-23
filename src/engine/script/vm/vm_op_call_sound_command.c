#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "slus.h"

/* Reads a little-endian 16-bit script operand and passes it to SD_Call. */
void vm_op_30_call_sound_command(ScriptReader *state)
{
    u8 *cursor = state->cursor;
    u8 low = cursor[0];
    u8 high = cursor[1];

    state->cursor = cursor + 2;
    SD_Call(low | (high << 8));
}
