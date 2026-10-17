/* Relink of matched dungeon/func_80A9F3F4; every changed retail word is a paired relocation. */
#define dungeonUpdateActorBehaviorAndEffect D_8014CE7C
#include "modules/dungeon_resource08_slot0.h"

void func_80150BF4(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor) > 0) {
        state->callback = dungeonUpdateActorBehaviorAndEffect;
    }
}
