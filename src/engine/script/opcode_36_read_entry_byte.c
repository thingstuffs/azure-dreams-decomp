#include "common.h"

typedef void (*Callback)(void);

typedef struct {
    u8 pad_00[0x10];
    Callback callback;
    u8 pad_14[0x8];
    u8 *stream;
    u8 pad_20[0xF];
    u8 value_2F;
} Func80039B94State;

extern void wait_message_entry_ready(void);

/* Opcode 0x24: Wait until the u8 actor entry is ready. */
void script_wait_actor_ready(Func80039B94State *state) {
    u8 *stream = state->stream;
    u8 value = *stream;

    state->stream = stream + 1;
    state->callback = wait_message_entry_ready;
    state->value_2F = value;
}
