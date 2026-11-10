#include "common.h"
#include "town/system.h"
#include "slus.h"

extern s32 overlay_height_in_range;

/* Choose the sound command from the global mode flag. */
void select_sound_command_from_mode(void) {
    if (overlay_height_in_range != 0) {
        SD_Call(0x517);
        return;
    }
    SD_Call(0x508);
}
