
struct SpriteFrameState;
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 update_actor_hop_and_shrink(void *, void *,struct SpriteFrameState *, void *);                            /* extern */

/* Calls update_actor_hop_and_shrink on the record, then clears unk_A6. */
void reset_record_motion_field(ActorRecord *record, ObjectPosition *motion, SpriteFrameState *scale, ActorRecord *render) {
    update_actor_hop_and_shrink(record, motion, scale, render);
    record->unk_A4.halves.high.s = 0;
}
