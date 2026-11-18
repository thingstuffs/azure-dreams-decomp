#include "common.h"
#include "engine/script.h"
#include "engine/message.h"

typedef struct Func80039BBCState {
    u8 unk00[0x10];
    void (*handler)(Func80038690State *);
    u8 unk14[0x08];
    u8 *cursor;
    u8 unk20[0x12];
    s8 call_number; /* read back with lb: numbers 0x80-0xFF index before the table */
} Func80039BBCState;

/* Opcode 0x25: Poll call number u8 with v0..v3 every frame until it returns nonzero (result to v15). */
void script_poll_service(Func80039BBCState *state) {
    u8 *cursor = state->cursor;
    u8 value = *cursor;

    state->cursor = cursor + 1;
    state->handler = run_message_opcode_handler;
    state->call_number = value;
}
