#include "modules/dungeon_resource17_slot0.h"

void func_80174318(Resource17CallbackState *state, void *entity, void *position, void *graphic)
{
    if (func_800AC010(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_801713A8;
        }
    }
}
