#include "common.h"
#include "town/menu.h"
#include "town/shop.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Calls func_800B47BC with the value increased by 0x20. */
void forward_offset_to_effect_builder(s32 value) {
    func_800B47BC(value + 0x20);
}
