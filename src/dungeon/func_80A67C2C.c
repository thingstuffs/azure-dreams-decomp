/* Relink of matched dungeon/func_80A49C2C; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 dungeonUpdateActorHopAndShrink(void *, void *, void *, void *);                            /* extern */


/* Calls dungeonUpdateActorHopAndShrink on the record, then clears unk_B6. */
void func_8015542C(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render) {
    dungeonUpdateActorHopAndShrink(record, motion, scale, render);
    record->unk_B6 = 0;
}
