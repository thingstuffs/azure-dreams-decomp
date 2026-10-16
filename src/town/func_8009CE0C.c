#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townInitializeRecordWithHandlerTable(void *, s32, s32);                            /* extern */

/* Forward the object and values to townInitializeRecordWithHandlerTable. */
void townForwardPlayerMotionUpdate(void *object, s32 value_1, s32 value_2) {
    townInitializeRecordWithHandlerTable(object, value_1, value_2);
}
