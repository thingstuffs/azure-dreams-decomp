#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

extern void townAddHex20000SSignedOffsetHex14(EntityRec *record);
extern s16 townQueryLoweredTransformPosition(void *position);
s32 townSelectObjectSetupPath();         /* extern */
s32 func_800CDF00();     /* extern */
s32 func_800CDF94();


/* extern */

/* Advance motion, clamp at its limit, and handle the remaining steps. */
void townAdvanceMotionAndClampLimit(Rec_func_80094268_arg0 *entity, EntityRec *motion, s32 context) {
    s16 steps_left;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (townQueryLoweredTransformPosition(motion) < motion->z.w.i) {
        motion->z.w.i = townQueryLoweredTransformPosition(motion);
        steps_left = entity->unk_90.as_s16 - 1;
        entity->unk_90.as_s16 = steps_left;
        if (steps_left <= 0) {
            motion->flags14 = 0;
            func_800CDF94(entity, motion, context);
            return;
        }
        if (townSelectObjectSetupPath(entity, motion, context) == 0) {
            func_800CDF00(entity, motion, context);
            return;
        }
    } else {
        townAddHex20000SSignedOffsetHex14(motion);
    }
}
