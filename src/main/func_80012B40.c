#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void cardBootSetSlotMenuRequest();                            /* extern */

/* Set the object's field at offset 0x20 to the supplied value. */
void cardBootInitializeSlotMenuRequest(void *object, s32 value) {
    cardBootSetSlotMenuRequest(object, value);
}
