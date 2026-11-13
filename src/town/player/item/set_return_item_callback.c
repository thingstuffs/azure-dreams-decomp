#include "common.h"
#include "town/player/state_callback_g00544.h"
#include "town/player/item.h"



/* Stores D_800947CC through town_player_action_callback and returns zero. */
s32 set_return_item_callback(void) {
    *town_player_action_callback = initialize_returned_item_action;
    return 0;
}
