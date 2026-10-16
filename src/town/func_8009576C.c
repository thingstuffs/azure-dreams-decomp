/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 func_8009451C();        
s32 func_80094714();        
s32 func_80094910();                            
void townStoreTheValidSharedAngleInOffsetHex10();                         
void townHandleAdjustVectorTowardSelectedAngleLimitMagnitude();                      
void townAddHex20000SSignedOffsetHex14();                      
void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2();                      
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      
void townSpawnPersonRadialEffects();                      
extern u8 D_800CFCEF;

void func_80092ECC(s32 object_id, EntityRec *object, s32 update_context) {
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
