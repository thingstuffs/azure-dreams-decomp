#include "shared/position_query.h"
#include "common.h"

typedef struct TownObject {
    u8 pad0[0xA];
    s16 limit;
    u8 padC[8];
    s32 state;
} TownObject;

extern void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(TownObject *arg);
extern void townStoreTheValidSharedAngleInOffsetHex10(void *arg);
extern void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(TownObject *arg);
extern void func_80094910(void);
extern s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(TownObject *arg, s32 *table);
extern void townComputeAndClampsVectorBasedAdjustmentUpdatesTown(TownObject *arg, s16 value, s32 *table);
extern void townSpawnPersonRadialEffects(TownObject *arg);
extern void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(TownObject *arg);
extern void townInitializeSceneActionRecord(void *context, TownObject *object, s32 update_arg);
extern void townAddHex20000SSignedOffsetHex14(TownObject *arg);

extern u8 D_800CFCEF;

/* Updates a town object based on its table value, limit, and a global flag. */
void townUpdateThresholdBoundObject(void *context, TownObject *object, s32 update_arg)
{
    s16 table_value;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(object);
    townStoreTheValidSharedAngleInOffsetHex10(context);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(object);
    table_value = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, ((s32 *)&D_800FE488));

    if (object->limit >= table_value) {
        func_80094910();
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, table_value, ((s32 *)&D_800FE488));
        townSpawnPersonRadialEffects(object);
        townInitializeSceneActionRecord(context, object, update_arg);
    } else if (D_800CFCEF != 0) {
        func_80094910();
        object->state = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(object);
        townInitializeSceneActionRecord(context, object, update_arg);
    } else {
        townAddHex20000SSignedOffsetHex14(object);
    }
}
