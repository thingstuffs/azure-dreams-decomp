#include "common.h"
#include "town/player/item.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 *town_player_action_callback[3];
extern s32 D_800947CC;

/* Stores D_800947CC through town_player_action_callback and returns zero. */
s32 set_return_item_callback(void) {
    *town_player_action_callback = &D_800947CC;
    return 0;
}
