#include "common.h"
#include "town/player.h"

extern s8 D_80082A39;
extern s32 D_80110EC0;

/* Clears both D_80110EC0 and D_80082A39 to zero. */
void clear_action_globals(void) {
    D_80110EC0 = 0;
    D_80082A39 = 0;
}
