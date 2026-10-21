#include "common.h"

#include "common.h"
#include "slus/data.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *stream;
    u8 pad_20[0x60];
    u8 *buffer;
} Func80039AF0State;

/* Reads a stream byte into the buffer and stores its table lookup result. */
void read_message_byte(Func80039AF0State *state) {
    state->buffer[1] = *state->stream++;
    state->buffer[0x3C] = message_mode_default_bytes[state->buffer[1]];
}
