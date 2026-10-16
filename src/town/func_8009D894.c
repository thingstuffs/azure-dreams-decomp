#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townUpdatePlayerGlobalState(void *, s32, s32);                            /* extern */

/* Forward the object and values to townUpdatePlayerGlobalState. */
void townForwardPlayerStateUpdate(void *object, s32 value_1, s32 value_2) {
    townUpdatePlayerGlobalState(object, value_1, value_2);
}
