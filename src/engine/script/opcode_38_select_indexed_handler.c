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

/* Read a script command byte and select run_indexed_handler_and_set_next as the next callback. */
void handle_vm_opcode_38(Func80039BE4State *state) {
    state->command = *state->cursor++;
    state->callback = run_indexed_handler_and_set_next;
}
