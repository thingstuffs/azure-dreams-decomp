#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x10];
    void (*callback)(void *);
    u8 pad_14[0x8];
    u8 *cursor;
    u8 pad_20[0x12];
    u8 command;
} Func80039BE4State;

extern void func_80038708(void *);

/* Read a script command byte and select func_80038708 as the next callback. */
void func_80039BE4(Func80039BE4State *state) {
    state->command = *state->cursor++;
    state->callback = func_80038708;
}
