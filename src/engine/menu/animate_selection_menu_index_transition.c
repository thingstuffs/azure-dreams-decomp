#include "common.h"
#include "engine/effect.h"
#include "engine/menu.h"
#include "slus.h"

typedef struct S_8004F95C {
    void (*func)(void);
    u8 pad4[0x28 - 0x4];
    s32 limit;
    s32 counter;
} S_8004F95C;

/*
 * Reorders and interpolates the menu entries, then installs the idle callback when the previous
 * counter value reaches the limit.
 */
void animate_selection_menu_index_transition(S_8004F95C *state) {
    reorder_and_interpolate_selection_menu_entries(state);
    if (state->counter++ >= state->limit) {
        state->func = noop_selection_menu_animation_idle;
    }
}
