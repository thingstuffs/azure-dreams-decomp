/* Relink of matched dungeon/func_80AF4148; every changed retail word is a paired relocation. */
#define func_801717F4 func_801710EC
#include "modules/dungeon_resource10_slot0.h"

void func_80174710(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonPropagateActorActionFlag(state, motion, position, actor)) {
        state->callback = func_801710EC;
    }
}
