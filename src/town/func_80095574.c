#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad0[0x14];
    s32 field14;
} TownObject;

extern u8 D_800CFCEE[];

extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(TownObject *);
extern void townStoreTheValidSharedAngleInOffsetHex10(void *);
extern void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(TownObject *);
extern void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(TownObject *);
extern void townAddHex20000SSignedOffsetHex14(TownObject *);
extern void func_80094714(void *, TownObject *, void *);
extern void func_80094620(void *, TownObject *, void *);

/* Updates the town object and dispatches its action based on input and state. */
void townUpdateTownObjectFromInput(void *context, TownObject *object, void *action_data)
{
    GameWork *input = &gameWork;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(object);
    townStoreTheValidSharedAngleInOffsetHex10(context);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(object);

    if (D_800CFCEE[0] != 0) {
        object->field14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(object);
    } else {
        townAddHex20000SSignedOffsetHex14(object);
    }

    if (((u32)input->unk_010) & 0x40) {
        func_80094714(context, object, action_data);
        return;
    }

    if (object->field14 >= 0) {
        func_80094620(context, object, action_data);
    }
}
