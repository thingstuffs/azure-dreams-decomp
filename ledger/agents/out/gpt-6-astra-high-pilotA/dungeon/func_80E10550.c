#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800AB538(arg0);                            /* extern */

/* Calls func_800AB538 on the record, then clears unk_A6. */
void func_80173D50(Rec_func_800AB538_arg0 *record) {
    func_800AB538(record);
    record->unk_A6 = 0;
}
