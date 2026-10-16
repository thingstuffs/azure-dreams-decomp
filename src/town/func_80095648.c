#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"

M2C_UNK func_8009451C();        /* extern */
M2C_UNK func_80094714();        /* extern */
M2C_UNK func_80094910();                            /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                         /* extern */
void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();                      /* extern */
void townAddHex20000SSignedOffsetHex14();                      /* extern */
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                      /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
void townSpawnPersonRadialEffects();                      /* extern */
extern u8 D_800CFCEF;


/* Updates a town object based on its threshold and the global update flag. */
void townUpdateThresholdObjectWithInteraction(s32 object_id, EntityRec *object, s32 update_context) {
    s16 update_threshold;
    GameWork *town_state;

    town_state = &gameWork;
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(object);
    townStoreTheValidSharedAngleInOffsetHex10(object_id);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(object);
    if (((s32)town_state->unk_010) & 0x40) {
        func_80094714(object_id, object, update_context);
    }
    update_threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, &D_800FE488);
    if (object->z.w.i >= update_threshold) {
        func_80094910();
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, update_threshold, &D_800FE488);
        townSpawnPersonRadialEffects(object);
        func_8009451C(object_id, object, update_context);
    } else if (D_800CFCEF != 0) {
        func_80094910();
        object->flags14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(object);
        func_8009451C(object_id, object, update_context);
    } else {
        townAddHex20000SSignedOffsetHex14(object);
    }
}
