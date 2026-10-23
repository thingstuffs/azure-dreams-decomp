#include "common.h"
#include "engine/script.h"

#include "common.h"
#include "slus/data.h"

/* Reads a stream byte into the buffer and stores its table lookup result. */
void read_message_byte(ScriptReader *state) {
    state->data[1] = *state->cursor++;
    state->data[0x3C] = message_mode_default_bytes[state->data[1]];
}
