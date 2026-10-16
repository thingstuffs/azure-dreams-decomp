#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_8009431C();        /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                         /* extern */
void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();                      /* extern */
void townAddHex20000SSignedOffsetHex14();                      /* extern */
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
void townUpdateTheComputedUpperBoundGlobalStatePermits();                      /* extern */
extern u8 D_800CFCEE;


/* Update the actor record and dispatch follow-up processing when its state is nonnegative. */
void townUpdateActorAndDispatchState(s32 actor, EntityRec *record, M2C_UNK context) {
    townUpdateTheComputedUpperBoundGlobalStatePermits(record);
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(record);
    townStoreTheValidSharedAngleInOffsetHex10(actor);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(record);
    if (D_800CFCEE != 0) {
        record->flags14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(record);
    } else {
        townAddHex20000SSignedOffsetHex14(record);
    }
    if (record->flags14 >= 0) {
        func_8009431C(actor, record, context);
    }
}
