
struct SpriteFrameState;
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AB538_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/cyclone.h"
#include "dungeon/actor.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Calls update_actor_hop_and_shrink on the record, then clears unk_A6. */
void update_cyclone_hop_shrink(ActorRecord *record, ObjectPosition *motion, SpriteFrameState *scale, ActorRecord *render) {
    update_actor_hop_and_shrink(record, motion, scale, render);
    record->unk_A4.halves.high.s = 0;
}
