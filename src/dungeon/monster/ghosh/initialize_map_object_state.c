#include "common.h"

extern void *ghosh_actor_node;
extern s32 D_80174928[];
extern s32 *D_80174CCC;
extern s16 D_80174CD0;

/* Initialize the current object state and reset the default table counter. */
void initialize_map_object_state(void) {
    void *state;

    state = ghosh_actor_node;
    if (state != 0) {
        state = (s8 *)state + 0x20;
        *(s8 *)((s8 *)state + 0xB2) = 1;
        *(s16 *)((s8 *)state + 0xAE) = 1;
        D_80174CCC = D_80174928;
        D_80174CD0 = 0;
    }
}
