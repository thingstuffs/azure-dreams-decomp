#include "modules/dungeon_resource08_slot0.h"

void func_80174BBC(Resource08CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AB464(state, motion, position, actor) > 0) {
        state->callback = func_80170E7C;
    }
}
