#include "common.h"
#include "m2c_compat.h"
#include "town/player/item.h"
#include "town/player/state.h"

extern s32 *town_player_action_callback;

/* Selects select_next_item_state as town_player_action_callback and returns zero. */
s32 set_hold_item_callback(void) {
    town_player_action_callback = &select_next_item_state;
    return 0;
}
