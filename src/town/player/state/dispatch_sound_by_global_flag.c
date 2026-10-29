#include "common.h"
#include "slus.h"
#include "town/player/state.h"

extern s32 overlay_height_in_range;

/* Dispatch code 0x518 or 0x50A according to the global flag. */
void dispatch_sound_by_global_flag(void) {
    if (overlay_height_in_range != 0) {
        SD_Call(0x518);
        return;
    }
    SD_Call(0x50A);
}
