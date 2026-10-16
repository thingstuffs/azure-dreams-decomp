#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_800C9B44_arg0.h"

void townAddHex20000SSignedOffsetHex14();                      /* extern */
s16 townQueryLoweredTransformPosition();                          /* extern */
M2C_UNK func_800C9C94();     /* extern */
void townChooseReactionActionAndHeading();


/* extern */

/* Advance motion and handle reaching the position limit. */
void townAdvanceReactionMotionToLimit(Rec_func_800C9B44_arg0 *state, EntityRec *motion, s32 context) {
    u16 remaining_count;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (townQueryLoweredTransformPosition(motion) < motion->z.w.i) {
        motion->z.w.i = townQueryLoweredTransformPosition(motion);
        remaining_count = state->unk_90 - 1;
        state->unk_90 = remaining_count;
        if ((remaining_count << 0x10) <= 0) {
            motion->flags14 = 0;
            townChooseReactionActionAndHeading(state, motion, context);
            return;
        }
        func_800C9C94(state, motion, context);
        return;
    }
    townAddHex20000SSignedOffsetHex14(motion);
}
