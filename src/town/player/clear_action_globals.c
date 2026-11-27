#include "common.h"
#include "town/player.h"

extern u8 script_camera_target_slot;
extern s32 D_80110EC0;

/* Clears both D_80110EC0 and D_80082A39 to zero. */
void clear_action_globals(void) {
    D_80110EC0 = 0;
    script_camera_target_slot = 0;
}
