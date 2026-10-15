#include "modules/town_door.h"

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void func_800A07E8(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position) {
    if (entity->unk68 == 0) {
        if (func_800A0668(entity) != 0) {
            return;
        }
    } else if (func_800A0668(entity) == 0) {
        return;
    }
    if (func_800A0F10(entity, action) != 0) {
        entity->unk50 = func_800A0884;
        action = position->unk2;
        func_8009A674(entity->unk72, action, position->unk6);
    }
}
