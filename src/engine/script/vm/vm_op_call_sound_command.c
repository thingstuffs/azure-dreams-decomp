#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "slus.h"

/* Opcode 0x1E: Send the 16-bit operand to SD_Call. */
void script_sound_command(ScriptReader *state)
{
    u8 *cursor = state->cursor;
    u8 low = cursor[0];
    u8 high = cursor[1];

    state->cursor = cursor + 2;
    SD_Call(low | (high << 8));
}
