#include "modules/town_door.h"

/* Check interaction conditions, apply the target value, and trigger a positional effect. */
void townTriggerDoorInteractionEffect(void *actor, void *target, void *position) {
    if (*(s16 *)((u8 *)actor + 0x68) == 0) {
        if (townCheckDoorStatusInverted(actor) != 0) {
            return;
        }
    } else {
        if (townCheckDoorStatusInverted(actor) == 0) {
            return;
        }
    }
    if (townCheckDoorInputAndAngle(actor, target) == 0) {
        return;
    }
    townChangeDoorMap(actor, *(s32 *)((u8 *)target + 0x48));
    *(void **)((u8 *)actor + 0x50) = &townDoorNoOp;
    func_8009A8EC(*(s16 *)((u8 *)actor + 0x72), *(s16 *)((u8 *)position + 2), *(s16 *)((u8 *)position + 6));
}
