#include "common.h"
#include "town/scene.h"
#include "town/player.h"

extern void func_80016A78(void);

/* Run the conditional handler for values of at least five, then process the inputs. */
void process_entry_after_level_5_step(s32 input_a, s32 input_b) {
    if (get_town_state_count() >= 5) {
        func_80016A78();
    }
    process_checked_entry(input_a, input_b);
}
