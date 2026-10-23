#include "common.h"

extern void *ghosh_actor_node;
extern s32 D_80174928[];
extern s32 *ghosh_script_cursor;
extern s16 ghosh_script_repeat_count;

/* Initialize the current object state and reset the default table counter. */
void initialize_map_object_state(void) {
    void *state;

    state = ghosh_actor_node;
    if (state != 0) {
        state = (s8 *)state + 0x20;
        *(s8 *)((s8 *)state + 0xB2) = 1;
        *(s16 *)((s8 *)state + 0xAE) = 1;
        ghosh_script_cursor = D_80174928;
        ghosh_script_repeat_count = 0;
    }
}
