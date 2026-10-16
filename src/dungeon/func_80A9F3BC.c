#include "modules/dungeon_resource08_slot0.h"

void func_80174BBC(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonResolveActorFloorTrapOnce(state, motion, position, actor) > 0) {
        state->callback = dungeonUpdateActorBehaviorAndEffect;
    }
}
