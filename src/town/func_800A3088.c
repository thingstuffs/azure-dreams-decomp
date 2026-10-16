#include "modules/town_door.h"

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void townEmitDoorPositionEffect(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position) {
    if (entity->unk68 == 0) {
        if (townCheckDoorStatusInverted(entity) != 0) {
            return;
        }
    } else if (townCheckDoorStatusInverted(entity) == 0) {
        return;
    }
    if (townCheckDoorInputAndAngle(entity, action) != 0) {
        entity->unk50 = townOpenDoorToTarget;
        action = position->unk2;
        townInitializePlayerEntityCallbacks(entity->unk72, action, position->unk6);
    }
}
