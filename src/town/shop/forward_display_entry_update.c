#include "common.h"
#include "m2c_compat.h"
#include "town/shop.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Forward the object and value to fill_display_slots. */
void forward_display_entry_update(void *object, s32 value) {
    fill_display_slots(object, value);
}
