#include "common.h"
#include "shared/game_work.h"


/* Check for flags in mask 0xF0A3 while flag 0x10 is clear. */
s32 func_80094EA4(void) {
    if (!(gameWork.buttons & 0x10)) {
        if (gameWork.buttons & 0xF0A3) {
            return 1;
        }
    }
    return 0;
}
