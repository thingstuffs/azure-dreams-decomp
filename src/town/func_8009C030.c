#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeRecordWithHandlerTable();     /* extern */
s16 townQueryLoweredTransformPosition();


/* extern */

/* Move toward the target position and advance the motion state when the countdown ends. */
void townMovePlayerTowardTargetWithTimer(Rec_func_80094268_arg0 *motion, EntityRec *position, M2C_UNK context) {
    u16 steps_left;

    position->z.w.i = townQueryLoweredTransformPosition(position);
    steps_left = motion->unk_0A.as_u16 - 1;
    motion->unk_0A.as_u16 = steps_left;
    if ((s16) steps_left <= 0) {
        position->x.w.i = (u16) motion->unk_30;
        position->y.w.i = (u16) motion->unk_32;
        motion->unk_10.as_u16 = (u16) motion->unk_0E;
        townInitializeRecordWithHandlerTable(motion, position, context);
        return;
    }
    position->x.w.i = (u16) (((u16)position->x.w.i) + ((s32) ((s16) motion->unk_30
        - (s16) ((u16)position->x.w.i)) / (s16) steps_left));
    position->y.w.i = (u16) (((u16)position->y.w.i) + ((s32) ((s16) motion->unk_32
        - (s16) ((u16)position->y.w.i)) / (s16) motion->unk_0A.as_u16));
}
