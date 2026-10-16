#include "modules/dungeon_resource07_slot0.h"

void func_801727E8(Resource07CallbackState *state, void *entity, void *position, void *graphic)
{
    if (func_800AB378(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_80170E54;
        }
    }
}
