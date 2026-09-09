#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *cursor;
} Func80039B28State;

extern s16 SD_Call(s32 a0);

/* Reads a little-endian 16-bit script operand and passes it to SD_Call. */
void func_80039B28(Func80039B28State *state)
{
    u8 *cursor = state->cursor;
    u8 low = cursor[0];
    u8 high = cursor[1];

    state->cursor = cursor + 2;
    SD_Call(low | (high << 8));
}
