#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void townAddHex20000SSignedOffsetHex14();                 /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townInitializeRecordWithHandlerTable();        /* extern */


/* Update the actor's fall and handle contact with the ground. */
void townUpdateFallingActorAndHandleGround(s32 context, EntityRec *actor, s32 action_arg) {
    s16 ground_height;

    ground_height = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(actor, &D_800FE488);
    if (actor->z.w.i >= ground_height) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(actor, ground_height, &D_800FE488);
        townInitializeRecordWithHandlerTable(context, actor, action_arg);
        return;
    }
    townAddHex20000SSignedOffsetHex14(actor);
}
