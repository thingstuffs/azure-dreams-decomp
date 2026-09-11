#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u32 *slots;
} RuntimeState;

/* Copies an event-script slot value using source and destination indices read from the script. */
void func_8003A248(RuntimeState *state) {
    u32 source = *state->read_ptr++;
    u32 destination = *state->read_ptr++;

    state->slots[destination + 0x12] = state->slots[source + 0x12];
}
