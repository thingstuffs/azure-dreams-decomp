#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* Process IDs 0x97F, 0x145B, and 0x11FA in sequence. */
void townProcessEventSequence(void) {
    townSetScriptFlagBit(0x97F);
    townSetScriptFlagBit(0x145B);
    townSetScriptFlagBit(0x11FA);
}
