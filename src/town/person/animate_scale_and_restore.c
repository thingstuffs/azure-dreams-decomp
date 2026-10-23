#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


extern s32 rsin(s32);


typedef struct S_800C4E30_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800C4E30_1;   /* arg2 in animate_scale_and_restore */


extern void apply_object_setup_and_update(Rec_func_80094268_arg0 *, void *, S_800C4E30_1 *);
/* Advance the scale animation countdown and restore normal scale when it ends. */
void animate_scale_and_restore(Rec_func_80094268_arg0 *state, void *context, S_800C4E30_1 *scale) {
    s16 frames_left;
    s32 shrink_value;
    s32 grow_value;
    s32 shrink_amount;

    frames_left = (u16) state->unk_6C.as_s16 - 1;
    state->unk_6C.as_s16 = frames_left;
    if (frames_left <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        apply_object_setup_and_update(state, context, scale);
        return;
    }
    shrink_value = rsin(frames_left * 0x199);
    shrink_amount = (shrink_value / 4);
    scale->unk_1C = (s16) (0x1000 - shrink_amount);
    grow_value = rsin(state->unk_6C.as_s16 * 0x199);
    scale->unk_1E = (s16) ((grow_value / 4) + 0x1000);
}
