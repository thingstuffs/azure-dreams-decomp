#include "common.h"
#include "shared/transition_slots.h"
#include "engine/effect.h"
#include "sdk/libc.h"

/* Processes type 5 and 6 entries in reverse order, clearing their type when handled. */
void tick_screen_fade_slots(void)
{
    s32 entry_index;

    for (entry_index = 7; entry_index >= 0; entry_index--) {
        switch (abs(runtime_transition_slots[entry_index].type)) {
        case 5:
            if (render_screen_fade_decreasing_intensity(&runtime_transition_slots[entry_index]) != 0) {
                runtime_transition_slots[entry_index].type = 0;
            }
            break;
        case 6:
            if (render_screen_fade_increasing_intensity(&runtime_transition_slots[entry_index]) != 0) {
                runtime_transition_slots[entry_index].type = 0;
            }
            break;
        }
    }
}
