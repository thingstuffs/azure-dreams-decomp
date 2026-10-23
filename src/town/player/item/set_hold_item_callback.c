#include "common.h"
#include "m2c_compat.h"

extern void D_80093BAC();
extern s32 *town_player_action_callback;

/* Selects D_80093BAC as town_player_action_callback and returns zero. */
s32 set_hold_item_callback(void) {
    town_player_action_callback = &D_80093BAC;
    return 0;
}
