#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"




/* Check whether the stored byte meets the threshold. */
s32 check_boss_effect_threshold(s32 threshold) {
    void *body = ghosh_scripted_actor + 1;
    ActorRecord *actor = body;

    return (s32)actor->action_id >= threshold;
}
