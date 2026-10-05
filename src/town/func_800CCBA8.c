#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"


extern void func_800C4174(void *object, void *update_context, s32 setup_context);

/* Ease the position toward its target, snapping to it when the timer expires. */
void func_800CA308(Rec_func_80094268_arg0 *state, EntityRec *position, s32 update_arg) {
    s32 x_delta;
    s32 y_delta;
    s32 z_delta;
    u16 timer;

    timer = state->unk_6C.as_u16 - 1;
    state->unk_6C.as_u16 = timer;
    if ((timer << 16) <= 0) {
        func_800C4174(state, position, update_arg);
        position->x.w.i = state->unk_84.as_u16;
        position->y.w.i = state->unk_86.as_u16;
        position->z.w.i = 0;
        return;
    }

    x_delta = (s16)state->unk_84.as_u16 -
            (s16)((u16)position->x.w.i);
    if (x_delta < 0) {
        x_delta += 7;
    }
    position->x.w.i =
        (u16)(((u16)position->x.w.i) + (x_delta >> 3));

    y_delta = (s16)state->unk_86.as_u16 - position->y.w.i;
    if (y_delta < 0) {
        y_delta += 7;
    }
    position->y.w.i =
        (s16)((u16)position->y.w.i + (y_delta >> 3));

    z_delta = -position->z.w.i;
    if (z_delta < 0) {
        z_delta += 7;
    }
    position->z.w.i =
        (s16)((u16)position->z.w.i + (z_delta >> 3));
}
