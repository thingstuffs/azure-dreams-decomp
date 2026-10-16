#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void townApplySelectedEntryValues(void *, s32);
/* Pass data and its accompanying value to townApplySelectedEntryValues. */
void townForwardDataAndValueB(void *data, s32 value) {
    townApplySelectedEntryValues(data, value);
}
