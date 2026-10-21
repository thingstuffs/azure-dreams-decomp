#include "common.h"

extern s32 overlay_height_in_range;
extern void SD_Call(s32);

/* Choose the sound command from the global mode flag. */
void select_sound_command_from_mode(void) {
    if (overlay_height_in_range != 0) {
        SD_Call(0x517);
        return;
    }
    SD_Call(0x508);
}
