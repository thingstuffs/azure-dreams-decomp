#include "modules/dungeon_resource16_slot0.h"

void func_80173674(Resource16CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AB464(state, motion, position, actor) > 0) {
        state->callback = func_80171014;
    }
}
