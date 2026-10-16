#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x1c];
    u8 *read_ptr;
} Func80039258State;

extern void clearResidentBitmapBit(s32 value);

/* Consumes a signed little-endian 16-bit script operand and passes it to clearResidentBitmapBit. */
void vmOp13ClearFlagBit(Func80039258State *state) {
    u8 *cursor = state->read_ptr;
    s32 low = cursor[0];
    s32 high = cursor[1];

    state->read_ptr = cursor + 2;
    clearResidentBitmapBit((s16)(low + (high << 8)));
}
