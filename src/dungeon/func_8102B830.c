/* Relink of matched dungeon/func_80E10550; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800AB538(void *, void *, void *, void *);                            /* extern */

/* Calls func_800AB538 on the record, then clears unk_A6. */
void func_8014F030(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render) {
    func_800AB538(record, motion, scale, render);
    record->unk_A6 = 0;
}
