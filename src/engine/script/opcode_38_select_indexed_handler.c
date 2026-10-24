#include "common.h"

#include "common.h"
#include "engine/message.h"

typedef struct {
    u8 pad_00[0x10];
    void (*callback)(void *);
    u8 pad_14[0x8];
    u8 *cursor;
    u8 pad_20[0x12];
    u8 command;
} Func80039BE4State;

/* Opcode 0x26: Call handler u8 of the resident handler table, then resume the message window. */
void script_call_indexed_handler(Func80039BE4State *state) {
    state->command = *state->cursor++;
    state->callback = run_indexed_handler_and_set_next;
}
