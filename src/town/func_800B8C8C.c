#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townFillDisplaySlots(void *, s32);                            /* extern */

/* Forward the object and value to townFillDisplaySlots. */
void townForwardDisplayEntryUpdate(void *object, s32 value) {
    townFillDisplaySlots(object, value);
}
