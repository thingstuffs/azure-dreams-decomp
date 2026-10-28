#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"
#include "shared/entity.h"



/* Return whether the current record's unk_D2 field is zero. */
s32 is_active_encounter_ready(void) {
    void *body = ghosh_actor_node + 1;
    ActorRecord *actor = body;

    return actor->unk_B0.bytes[2] == 0;
}
