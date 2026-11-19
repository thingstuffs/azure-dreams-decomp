#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "dungeon/monster/beldo_large.h"

/* Returns whether the Beldo script node mode equals the supplied value. */
s32 is_beldo_large_mode(s32 value) {
    ActorRecord *actor = NODE_BODY(beldo_script_node);
 return actor->action_id == value; }
