#include "shared/position_query.h"
#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void townAddHex20000SSignedOffsetHex14();                 /* extern */
s16 townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated();               /* extern */
void townComputeAndClampsVectorBasedAdjustmentUpdatesTown();      /* extern */
void townInitializeRecordWithHandlerTable();        /* extern */


/* Advance the object's position and handle crossing the sampled limit. */
void townAdvancePlayerPosition(s32 context, EntityRec *object, s32 update_data) {
    s16 limit;

    object->z.v = (s32) (object->z.v + object->flags14);
    limit = townSelectTheSmallerPositionQueryResultCappedN64WritesAssociated(object, &D_800FE488);
    if (limit < object->z.w.i) {
        townComputeAndClampsVectorBasedAdjustmentUpdatesTown(object, limit, &D_800FE488);
        townInitializeRecordWithHandlerTable(context, object, update_data);
        return;
    }
    townAddHex20000SSignedOffsetHex14(object);
}
