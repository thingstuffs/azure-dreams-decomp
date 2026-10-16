#include "modules/dungeon_resource06_slot0.h"

void func_80173D98(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonUpdateSpinningActorFall(state, motion, position, actor)) {
        state->callback = func_8017140C;
    }
}
