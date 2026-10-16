#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/town_handler.h"

M2C_UNK dungeonInitializeActionObjectTypeSix();     /* extern */
M2C_UNK func_80094910();                            /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                      /* extern */
void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();                      /* extern */
void townAddHex20000SSignedOffsetHex14();                      /* extern */
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                      /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
void townSpawnPersonRadialEffects();                      /* extern */
extern u8 D_800CFCEF;
extern M2C_UNK D_800D00B8;

/* Advance the state counter and update the entity, handling threshold and flag transitions. */
void townUpdateThresholdAndInteraction(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context) {
    s16 threshold;
    u16 counter;

    counter = state->unk_0A.as_u16 + 1;
    state->unk_0A.as_u16 = counter;
    if ((s16) counter == 6) {
        townCallTheHandlerSelectsNonzeroEntry((s32 *) &D_800D00B8, state, (void *) context);
    }
    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(entity);
    townStoreTheValidSharedAngleInOffsetHex10(state);
    townHandleAdjustVectorTowardSelectedAngleLimitMagnitude(entity);
    threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(entity, &D_800FE488);
    if (entity->z.w.i >= threshold) {
        func_80094910();
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(entity, threshold, &D_800FE488);
        townSpawnPersonRadialEffects(entity);
        dungeonInitializeActionObjectTypeSix(state, entity, context);
        return;
    }
    if (D_800CFCEF != 0) {
        func_80094910();
        entity->flags14 = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(entity);
        dungeonInitializeActionObjectTypeSix(state, entity, context);
        return;
    }
    townAddHex20000SSignedOffsetHex14(entity);
}
