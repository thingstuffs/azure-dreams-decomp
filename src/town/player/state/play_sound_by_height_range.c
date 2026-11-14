#include "common.h"
#include "slus.h"
#include "town/player/state.h"
#include "town/player/overlay_height_data.h"


/* Dispatch code 0x518 or 0x50A according to the global flag. */
void play_sound_by_height_range(void) {
    if (overlay_height_in_range != 0) {
        SD_Call(0x518);
        return;
    }
    SD_Call(0x50A);
}
