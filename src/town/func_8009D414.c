/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townAddHex20000SSignedOffsetHex14();                 
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      
void townInitializeRecordWithHandlerTable();        

void func_8009AB74(s32 context, EntityRec *actor, s32 action_arg) {
    s16 ground_height;

    ground_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, &D_800FE488);
    if (actor->z.w.i >= ground_height) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, ground_height, &D_800FE488);
        townInitializeRecordWithHandlerTable(context, actor, action_arg);
        return;
    }
    townAddHex20000SSignedOffsetHex14(actor);
}
