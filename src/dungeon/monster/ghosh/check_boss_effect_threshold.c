#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "m2c_compat.h"

typedef struct S_801725F0_0 {
    u8 pad_00[0xBA];
    u8 unk_BA;
} S_801725F0_0;   /* D_80174CE0 in check_boss_effect_threshold */



/* Check whether the stored byte meets the threshold. */
s32 check_boss_effect_threshold(s32 threshold) {
    void *body = ghosh_scripted_actor + 1;
    ActorRecord *actor = body;

    return (s32)actor->action_id.u >= threshold;
}
