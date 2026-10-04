#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80093D48();
extern void func_80095C80();

/* Advance interpolation toward the target and finish when the countdown expires. */
void func_80091EB4(Rec_func_80094268_arg0 *state, EntityRec *motion, s32 context) {
    s32 target_pos;
    u16 ticks_left;

    func_80095C80(motion);
    ticks_left = state->unk_0A.as_u16 - 1;
    target_pos = state->unk_34.as_s16 << 0x10;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left <= 0) {
        motion->unk_0C = 0;
        motion->unk_10 = 0;
        motion->flags14 = 0;
        motion->z.v = (s32) (state->unk_34.as_s16 << 0x10);
        func_80093D48(state, motion, context);
        return;
    }
    motion->flags14 =
        (s32) ((s32) (target_pos - motion->z.v) /
               (s16) ticks_left);
}
