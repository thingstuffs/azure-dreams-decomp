#include "modules/dungeon_resource03_slot0.h"

void func_80173AF8(Resource03CallbackState *state, void *entity, void *position, void *graphic)
{
    if (func_800AC010(state, entity, position, graphic)) {
        if ((s16)func_800AD9B4(position, graphic) > 0) {
            state->callback = func_80170E54;
        }
    }
}
