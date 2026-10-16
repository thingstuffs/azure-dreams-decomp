#include "modules/dungeon_resource12_slot0.h"

void func_801725F0(Resource12CallbackState *state, void *entity, void *position, void *graphic)
{
    if (func_800AB378(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_80170E70;
        }
    }
}
