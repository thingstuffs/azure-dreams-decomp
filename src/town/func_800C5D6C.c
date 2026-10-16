#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 townSelectObjectSetupPath(void *, s32, s32, s32);                            /* extern */

/* Forward the object and three values to townSelectObjectSetupPath. */
void townForwardObjectUpdateValues(void *object, s32 value_1, s32 value_2, s32 value_3) {
    townSelectObjectSetupPath(object, value_1, value_2, value_3);
}
