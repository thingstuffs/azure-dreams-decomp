#include "modules/dungeon_resource06_slot0.h"

void func_80175834(Resource06CallbackState *state, void *motion, void *position, void *actor)
{
    if (func_800AC7EC(state, motion, position, actor) > 0) {
        state->callback = func_8017140C;
    }
}
