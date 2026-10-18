#include "common.h"
#include "shared/types3a_types.h"


extern void animate_item_menu_cursor_transition(ItemMenuDelayState *);

/* Update the state and increment its counter, clearing status when the prior count reaches the limit. */
void tick_item_menu_selection_delay(ItemMenuDelayState *state) {
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
