#include "common.h"
#include "shared/game_work.h"


/* Check for flags in mask 0xF0A3 while flag 0x10 is clear. */
s32 func_80094EA4(void) {
    if (!(((s32)gameWork.unk_008) & 0x10)) {
        if (((s32)gameWork.unk_008) & 0xF0A3) {
            return 1;
        }
    }
    return 0;
}
