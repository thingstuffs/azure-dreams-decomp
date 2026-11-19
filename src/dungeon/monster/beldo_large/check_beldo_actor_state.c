#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo_large.h"



/* Checks whether the actor's action ID equals the expected value. */
s32 check_beldo_actor_state(s32 expected_value) {
    ActorRecord *actor = NODE_BODY(beldo_actor_nodes);

    return actor->action_id == expected_value;
}
