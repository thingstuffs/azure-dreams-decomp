#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} Func80039258State;

extern void func_80033AE8(s32 value);

/* Reads a signed little-endian 16-bit value, advances the cursor, and passes it to func_80033AE8. */
void func_80039258(Func80039258State *state) {
    u8 *cursor = state->read_ptr;
    u8 low = cursor[0];
    u8 high = cursor[1];

    state->read_ptr = cursor + 2;
    func_80033AE8((s16)(low + (high << 8)));
}
