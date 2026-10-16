/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeRecordWithHandlerTable();     
s16 townQueryLoweredTransformPosition();

void func_800999AC(Rec_func_80094268_arg0 *state, EntityRec *object, s32 context) {
    u16 ticks_left;

    object->z.w.i = townQueryLoweredTransformPosition(object);
    ticks_left = state->unk_0A.as_u16 - 1;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        townInitializeRecordWithHandlerTable(state, object, context);
        return;
    }
    object->x.v = (s32) (object->x.v + 0xFFFE0000);
}
