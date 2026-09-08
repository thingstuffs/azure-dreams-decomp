#include "common.h"

typedef void (*Callback)(void);

typedef struct {
    unsigned char pad[0x1c];
    u16 value;
} State;

extern void func_8003C4C0(void);

/* Increases the state value by 0x200, clamps it to 0x1000, and switches callbacks at the limit. */
void func_8003C488(Callback *callback, void *unused, State *state) {
    state->value += 0x200;
    if (state->value < 0x1000) {
        return;
    }
    state->value = 0x1000;
    *callback = func_8003C4C0;
}
