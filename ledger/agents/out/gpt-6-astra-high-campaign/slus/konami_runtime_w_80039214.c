#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x1C];
    u8 *data;
} Func39214State;

extern s32 func_80033AA8(s32 value);

/* Consumes a signed little-endian 16-bit script operand and passes it to func_80033AA8. */
s32 func_80039214(Func39214State *state) {
    u8 *data;
    s32 low;
    s32 high;

    data = state->data;
    low = data[0];
    high = data[1];
    state->data = data + 2;
    high <<= 8;
    low += high;
    return func_80033AA8((s16)low);
}
