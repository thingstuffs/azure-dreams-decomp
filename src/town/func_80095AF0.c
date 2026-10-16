#include "shared/position_query.h"
#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 field_A;
    u8 padC[8];
    s32 field_14;
} TownObject;

extern u8 D_800CFCEF;

extern void townInitializeSceneActionRecord(void *, TownObject *, void *);
extern void townStoreTheValidSharedAngleInOffsetHex10(void *);
extern void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(TownObject *);
extern void townAddHex20000SSignedOffsetHex14(TownObject *);
extern void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(TownObject *);
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(TownObject *, void *);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(TownObject *, s16, void *);
extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(TownObject *);

/* Updates a town object based on its computed threshold and the global flag. */
void townUpdateThresholdObject(void *context, TownObject *object, void *update_data)
{
    s16 threshold;
    u8 *threshold_data;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(object);
    townStoreTheValidSharedAngleInOffsetHex10(context);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(object);
    threshold_data = ((u8 *)&D_800FE488);
    threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, threshold_data);

    if (object->field_A >= threshold) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, threshold, threshold_data);
        townInitializeSceneActionRecord(context, object, update_data);
        return;
    }

    if (D_800CFCEF != 0) {
        object->field_14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(object);
        townInitializeSceneActionRecord(context, object, update_data);
    } else {
        townAddHex20000SSignedOffsetHex14(object);
    }
}
