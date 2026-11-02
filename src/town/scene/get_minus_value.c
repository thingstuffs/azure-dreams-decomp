#include "common.h"
#include "town/scene.h"
#include "town/shop.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Returns 20 minus the value from func_800190DC. */
s32 get_20_minus_value(void) {
    return 0x14 - count_town_items();
}
