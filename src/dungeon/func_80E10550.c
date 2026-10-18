#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 update_actor_hop_and_shrink(void *, void *, void *, void *);                            /* extern */

/* Calls update_actor_hop_and_shrink on the record, then clears unk_A6. */
void reset_record_motion_field(Rec_func_800AB538_arg0 *record, void *motion, void *scale, void *render) {
    update_actor_hop_and_shrink(record, motion, scale, render);
    record->unk_A6 = 0;
}
