#include "common.h"
#include "town/system.h"
#include "slus.h"
#include "town/player/overlay_height_data.h"


/* Choose the sound command from the global mode flag. */
void play_overlay_height_sound(void) {
    if (overlay_height_in_range != 0) {
        SD_Call(0x517);
        return;
    }
    SD_Call(0x508);
}
