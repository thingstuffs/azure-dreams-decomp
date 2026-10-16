#include "common.h"
#include "shared/transition_slots.h"

extern int abs(int);
extern s16 renderScreenFadeDecreasingIntensity(TransitionSlot *a0);
extern s16 renderScreenFadeIncreasingIntensity(TransitionSlot *a0);
/* Processes type 5 and 6 entries in reverse order, clearing their type when handled. */
void tickScreenFadeSlots(void)
{
    s32 entry_index;

    for (entry_index = 7; entry_index >= 0; entry_index--) {
        switch (abs(D_80083120[entry_index].type)) {
        case 5:
            if (renderScreenFadeDecreasingIntensity(&D_80083120[entry_index]) != 0) {
                D_80083120[entry_index].type = 0;
            }
            break;
        case 6:
            if (renderScreenFadeIncreasingIntensity(&D_80083120[entry_index]) != 0) {
                D_80083120[entry_index].type = 0;
            }
            break;
        }
    }
}
