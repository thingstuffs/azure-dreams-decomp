#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townProcessValidEntryLookup(s32);                            /* extern */
void townSetPairedEntryBrightness();                         /* extern */

/* Runs the three update steps for an entry. */
void townRunEntryUpdateSteps(s32 entry_id) {
    townProcessValidEntryLookup(entry_id);
    func_800B3C74(entry_id);
    townSetPairedEntryBrightness(entry_id);
}
