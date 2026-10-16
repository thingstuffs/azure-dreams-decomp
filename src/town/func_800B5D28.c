#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townUpdateAndFinalizeRecord();                         /* extern */

/* Passes the base plus 0x20 to townUpdateAndFinalizeRecord. */
void townForwardOffsetToRecordUpdater(s32 base) {
    townUpdateAndFinalizeRecord(base + 0x20);
}
