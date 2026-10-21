#include "common.h"

short SD_Call(int flags);
extern s32 overlay_height_in_range;

/* Queue sound command 0x519 at interval multiples when enabled. */
void play_periodic_sound(s32 count, s32 interval) {
    if (((count % interval) == 0) && (overlay_height_in_range != 0)) {
        SD_Call(0x519);
    }
}
