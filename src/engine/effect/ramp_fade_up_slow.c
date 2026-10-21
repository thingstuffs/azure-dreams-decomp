#include "common.h"
#include "engine/script/vm.h"

typedef void (*Callback)(void);

typedef struct {
    unsigned char pad[0x1c];
    u16 value;
} State;

/* Increases the state value by 0x200, clamps it to 0x1000, and switches callbacks at the limit. */
void ramp_fade_up_slow(Callback *callback, void *unused, State *state) {
    state->value += 0x200;
    if (state->value < 0x1000) {
        return;
    }
    state->value = 0x1000;
    *callback = noop_after_fade_ramp_completion;
}
