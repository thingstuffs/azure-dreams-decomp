/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townAddHex20000SSignedOffsetHex14();                 
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      
void townBindDefaultDataAndClearRecord();        

void func_80097F9C(s32 context, EntityRec *record, s32 action_data) {
    s16 threshold;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(record);
    threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(record, &D_800FE488);
    if (record->z.w.i >= threshold) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(record, threshold, &D_800FE488);
        townBindDefaultDataAndClearRecord(context, record, action_data);
        return;
    }
    townAddHex20000SSignedOffsetHex14(record, threshold);
}
