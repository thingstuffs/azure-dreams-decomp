#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townHandleInsertInitializeTwoValuesStatusFlags(Rec_D_800CFCB4 *, s32, s32);                            /* extern */


/* Configure the record and set its mode to 4. */
void townConfigureTheSetModeN4(Rec_D_800CFCB4 *record, s32 setup_value, s32 setup_param) {
    townHandleInsertInitializeTwoValuesStatusFlags(record, setup_value, setup_param);
    record->unk_14 = 4;
}
