#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* The target recomputes the address separately for the load (into v0) and the
 * store (into at) rather than caching one base register across both accesses.
 * A single C reference to D_804094EC lets gcc's RTL CSE merge those into one
 * cached-register access, which does not match. Declaring a second alias bound
 * to the SAME real address (via the narrow absolute-symbol form) for the store
 * gives gcc two textually distinct expressions, so it emits the two separate
 * lui/lw + lui/sw pairs the target uses. Both names resolve to the identical
 * linked address 0x804094EC; nothing is locally defined/faked. */
extern s32 card_selected_channel[];

void invoke_callback_for_four_global_values(void);
void func_80408654(s32);
void wait_selected(s32);

/* Run setup for both indices and replace the stored value with 16 minus itself. */
void toggle_card_selection_state(void) {
    s32 next_value;

    invoke_callback_for_four_global_values();
    func_80408654(0);
    func_80408654(1);
    next_value = 0x10 - card_selected_channel[0];
    D_804094EC_2[0] = next_value;
    wait_selected(next_value);
}
