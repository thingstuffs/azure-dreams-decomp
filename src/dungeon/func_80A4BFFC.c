#include "modules/dungeon_resource06_slot0.h"

void func_801757FC(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonResolveActorFloorTrapOnce(state, motion, position, actor) > 0) {
        state->callback = func_8017140C;
    }
}
