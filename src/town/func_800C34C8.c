#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern void townDispatchPairedTableValues(void);
/* Forward the context, value, and options to townDispatchPairedTableValues. */
void townForwardContextValueOptions(s32 context, s32 value, s32 options) {
    townDispatchPairedTableValues();
}
