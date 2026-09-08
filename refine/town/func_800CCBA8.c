#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_800C4174(void *arg0, void *arg1, s32 arg2);

/* Ease the position toward its target, snapping to it when the timer expires. */
void func_800CA308(Rec_func_80094268_arg0 *state, Rec_D_800E3D7C *position, s32 update_arg) {
    s32 x_delta;
    s32 y_delta;
    s32 z_delta;
    u16 timer;

    timer = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = timer;
    if ((timer << 16) <= 0) {
        func_800C4174(state, position, update_arg);
        position->unk_00.at02_u16.v = state->unk_84.as_u16;
        position->unk_04.at02_s16.v = state->unk_86.as_u16;
        position->unk_08.at02_s16.v = 0;
        return;
    }

    x_delta = (s16)state->unk_84.as_u16 -
            (s16)position->unk_00.at02_u16.v;
    if (x_delta < 0) {
        x_delta += 7;
    }
    position->unk_00.at02_u16.v =
        (u16)(position->unk_00.at02_u16.v + (x_delta >> 3));

    y_delta = (s16)state->unk_86.as_u16 - position->unk_04.at02_s16.v;
    if (y_delta < 0) {
        y_delta += 7;
    }
    position->unk_04.at02_s16.v =
        (s16)((u16)position->unk_04.at02_s16.v + (y_delta >> 3));

    z_delta = -position->unk_08.at02_s16.v;
    if (z_delta < 0) {
        z_delta += 7;
    }
    position->unk_08.at02_s16.v =
        (s16)((u16)position->unk_08.at02_s16.v + (z_delta >> 3));
}
