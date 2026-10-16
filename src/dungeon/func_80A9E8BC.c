#include "modules/dungeon_resource08_slot0.h"

void func_801740BC(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateActorFadeIn(state, motion, position, actor)) {
        state->callback = dungeonUpdateActorBehaviorAndEffect;
    }
}
