/* inferred-strong G00581: primitive_scale_effect_g00581; joins CL:town/func_800AA1AC,CL:town/func_800AA268; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AA1AC, CL:town/func_800AA268. */
#include "town/menu/primitive_scale_effect_g00581.h"

/* Update scale from elapsed ticks and advance when the countdown expires. */
void update_scale_effect_and_advance(S_800A7950_1 *state, void *context, S_800A7950_0 *scale) {
    s16 ticks_left;

    scale->unk_1C = (s16) (((state->unk_90 - state->unk_6C) * 8) + 0x1000);
    scale->unk_1E = (s16) (0x1000 - ((state->unk_90 - state->unk_6C) * 2));
    ticks_left = (u16) state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if (ticks_left < 0) {
        initialize_neutral_primitive(state, context, scale);
    }
}

/* Initialize object data and mode, and set the primitive color to neutral gray. */
void initialize_neutral_primitive(void *object, void *unused, void *primitive) {
    *(void **)((s8 *)object + 0x50) = D_800A79F0;
    *(s16 *)((s8 *)object + 0x6C) = 0x16;
    *(u8 *)((s8 *)primitive + 0x0E) = 0x80;
    *(u8 *)((s8 *)primitive + 0x0D) = 0x80;
    *(u8 *)((s8 *)primitive + 0x0C) = 0x80;
}
