#include "common.h"

typedef struct {
    u8 pad0[8];
    u16 count;
    u16 index;
    s16 *data;
} ScriptState;

s32 func_8009F988(void) {
    ScriptState *state;
    u16 index;
    s16 *result;

    state = (ScriptState *)0x80013710;
    index = state->index;
    result = &state->data[index];

    if (state->count == 0) {
        s8 *entry = (s8 *)--result;

        state->index = index - 1;
        if (*entry >= 0) {
            s32 value;

            value = *(volatile u8 *)entry;
            state->count = value - 1;
        } else {
            state->count = 0;
        }
    } else {
        state->count = state->count - 1;
    }
    return (s32)result;
}

/* MECHANISM: Frameless leaf under the true-space func_8009F988 name, with both
   apparent 0x8009F9DC/0x8009F9E0 calls recovered as local count-update joins.
   The shared pointer return then sinks move $v0,$v1 into the jr $ra delay slot. */
