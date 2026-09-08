#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"





extern s32 func_80094220(void *, void *, s32);
extern void func_80094984(void *, void *, s32);
extern void func_80095C80(void *);
extern s32 D_800D00E8;
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

/* Updates countdown-driven motion and invokes callbacks at selected ticks. */
void func_80091D6C(Rec_func_80094268_arg0 *state, Rec_D_800E3D7C *motion, s32 callback_arg) {
    s16 ticks_left;
    s32 target_position;

    func_80095C80(motion);
    if (state->unk_0A.as_s16 >= 15) {
        target_position = (s32)((u32)(state->unk_34.as_s16 +
                   D_800D0454[21 - state->unk_0A.as_s16]) << 16);
        goto selector_join;
    } else {
        target_position = (s32)((u32)state->unk_34.as_s16 << 16);
    }

selector_join:
    if (state->unk_0A.as_s16 == 19)
        func_80094984(&D_800D00E8, state, callback_arg);
    if (state->unk_0A.as_s16 == 15)
        func_80094984(&D_800D00F0, state, callback_arg);
    if (state->unk_0A.as_s16 == 12)
        func_80094984(&D_800D00F8, state, callback_arg);
    ticks_left = (u16)state->unk_0A.as_s16 - 1;
    state->unk_0A.as_s16 = ticks_left;
    if ((s32)((u32)(u16)ticks_left << 16) <= 0) {
        motion->unk_0C.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_14.as_s32 = 0;
        func_80094220(state, motion, callback_arg);
        return;
    }
    motion->unk_14.as_s32 = target_position - motion->unk_08.at00_s32.v;
}
