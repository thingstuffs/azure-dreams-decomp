#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townAddHex20000SSignedOffsetHex14();                 /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile();                      /* extern */
void townBindHandlerAndInitializeEntity();        /* extern */


/* Updates the record and selects a handler based on its computed threshold. */
void townUpdateActorAndSelectGroundHandler(s32 context, EntityRec *record, s32 action_data) {
    s16 threshold;

    townHandleResolvesMovementCollisionsAlongOneAxisUsingBoundaryProbesTile(record);
    threshold = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(record, &D_800FE488);
    if (record->z.w.i >= threshold) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(record, threshold, &D_800FE488);
        townBindHandlerAndInitializeEntity(context, record, action_data);
        return;
    }
    townAddHex20000SSignedOffsetHex14(record, threshold);
}
