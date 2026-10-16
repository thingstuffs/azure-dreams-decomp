#include "modules/dungeon_resource08_slot0.h"

void func_801727CC(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (func_800AB378(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_80170E7C;
        }
    }
}
