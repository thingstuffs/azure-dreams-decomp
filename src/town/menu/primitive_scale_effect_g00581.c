/* Initializes neutral-colored primitives and updates timed scale effects. */
/* inferred-strong G00581: primitive_scale_effect_g00581; joins CL:town/func_800AA1AC,CL:town/func_800AA268; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AA1AC, CL:town/func_800AA268. */
#include "town/menu/primitive_scale_effect_g00581.h"
#include "town/menu.h"
#include "town/menu/effect_callbacks_api.h"
#include "shared/sprite_frame_state.h"

/* Update scale from elapsed ticks and advance when the countdown expires. */
void update_scale_effect_and_advance(TownObjectRecord *state, void *context, SpriteFrameState *scale) {
    s16 ticks_left;

    scale->scale_x = (s16) (((state->unk_90 - ((s16)state->timer)) * 8) + 0x1000);
    scale->scale_y = (s16) (0x1000 - ((state->unk_90 - ((s16)state->timer)) * 2));
    ticks_left = (u16) state->timer - 1;
    state->timer = ticks_left;
    if (ticks_left < 0) {
        initialize_neutral_primitive(state, context, scale);
    }
}

/* Initialize object data and mode, and set the primitive color to neutral gray. */
void initialize_neutral_primitive(TownObjectRecord *object, void *unused, SpriteFrameState *primitive) {
    object->unk_50.as_pv = update_opposing_scale_effect;
    object->timer = 0x16;
    primitive->color.c.b = 0x80;
    primitive->color.c.g = 0x80;
    primitive->color.c.r = 0x80;
}
