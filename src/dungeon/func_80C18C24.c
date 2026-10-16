#include "modules/dungeon_resource17_slot0.h"

void func_80174424(Resource17CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AB464(state, motion, position, actor) > 0) {
        state->callback = func_801713A8;
    }
}
