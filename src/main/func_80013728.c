#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void cardBootSetSaveMenuRequest();                            /* extern */

/* Set the object's field at offset 0x20 to the supplied value. */
void cardBootInitializeSaveMenuRequest(void *object, s32 value) {
    cardBootSetSaveMenuRequest(object, value);
}
