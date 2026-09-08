#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80093D48();
extern M2C_UNK func_80095C80();

/* Advance interpolation toward the target and finish when the countdown expires. */
void func_80091EB4(Rec_func_80094268_arg0 *state, Rec_D_800E3D7C *motion, M2C_UNK context) {
    s32 target_pos;
    u16 ticks_left;

    func_80095C80(motion);
    ticks_left = state->unk_0A.as_u16 - 1;
    target_pos = state->unk_34.as_s16 << 0x10;
    state->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left <= 0) {
        motion->unk_0C.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_14.as_s32 = 0;
        motion->unk_08.at00_s32.v = (s32) (state->unk_34.as_s16 << 0x10);
        func_80093D48(state, motion, context);
        return;
    }
    motion->unk_14.as_s32 =
        (s32) ((s32) (target_pos - motion->unk_08.at00_s32.v) /
               (s16) ticks_left);
}
