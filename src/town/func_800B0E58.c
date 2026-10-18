#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Func800B0E58State;

extern void animate_item_menu_cursor_transition(Func800B0E58State *);

/* Update the state and increment its counter, clearing status when the prior count reaches the limit. */
void tick_item_menu_selection_delay(Func800B0E58State *state) {
    s32 counter;
    s32 previous_counter;

    animate_item_menu_cursor_transition(state);
    counter = state->unk8;
    previous_counter = counter;
    counter = counter + 1;
    state->unk8 = counter;
    if (previous_counter >= state->unk4) {
        state->unk0 = 0;
    }
}
