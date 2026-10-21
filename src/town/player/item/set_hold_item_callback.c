#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80093BAC;
extern s32 *town_player_action_callback;

/* Sets D_800FE5D8 to point to D_80093BAC and returns zero. */
s32 set_hold_item_callback(void) {
    town_player_action_callback = &D_80093BAC;
    return 0;
}
