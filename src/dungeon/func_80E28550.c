/* Relink of matched dungeon/func_80E10550; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 dungeonUpdateActorHopAndShrink(void *, void *, void *, void *);                            /* extern */

/* Calls dungeonUpdateActorHopAndShrink on the record, then clears unk_A6. */
void func_8015BD50(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render) {
    dungeonUpdateActorHopAndShrink(record, motion, scale, render);
    record->unk_A6 = 0;
}
