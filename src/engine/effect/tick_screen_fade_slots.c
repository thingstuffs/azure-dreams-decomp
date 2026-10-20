#include "common.h"
#include "shared/transition_slots.h"

extern int abs(int);
extern s16 render_screen_fade_decreasing_intensity(TransitionSlot *a0);
extern s16 render_screen_fade_increasing_intensity(TransitionSlot *a0);
/* Processes type 5 and 6 entries in reverse order, clearing their type when handled. */
void tick_screen_fade_slots(void)
{
    s32 entry_index;

    for (entry_index = 7; entry_index >= 0; entry_index--) {
        switch (abs(D_80083120[entry_index].type)) {
        case 5:
            if (render_screen_fade_decreasing_intensity(&D_80083120[entry_index]) != 0) {
                D_80083120[entry_index].type = 0;
            }
            break;
        case 6:
            if (render_screen_fade_increasing_intensity(&D_80083120[entry_index]) != 0) {
                D_80083120[entry_index].type = 0;
            }
            break;
        }
    }
}
