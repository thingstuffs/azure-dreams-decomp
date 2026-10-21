#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 *town_player_action_callback[3];
extern s32 D_800947CC;

/* Sets the first pointer in D_800FE5D8 to D_800947CC. */
s32 set_return_item_callback(void) {
    *town_player_action_callback = &D_800947CC;
    return 0;
}
