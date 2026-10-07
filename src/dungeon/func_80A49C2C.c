#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800AB538(void *, void *, void *, void *);                            /* extern */


/* Calls func_800AB538 on the record, then clears unk_B6. */
void func_8017342C(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render) {
    func_800AB538(record, motion, scale, render);
    record->unk_B6 = 0;
}
