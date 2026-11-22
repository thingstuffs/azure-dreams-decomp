#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/paired_indicators.h"
#include "shared/entity.h"
#include "town/minigame/object.h"

/* Apply object flags and tint, and copy the selected value triplet. */
void apply_minigame_object_tint(IndicatorChild *state, ObjectPosition *position, SpriteFrameState *render_state) {
    PairedIndicators *source;

    source = state->source;

    if (source->flags & 1) {
        render_state->flags |= 0x80;
    } else {
        render_state->flags &= 0xFF7F;
    }

    if (source->blink_color != 0) {
        render_state->color.word = 0x808080;
    } else {
        render_state->color.word = 0xFFFFFF;
    }

    if (state->use_first != 0) {
        position->x.w.i = source->first_x;
        position->y.w.i = source->first_y;
        position->z.w.i = source->first_z;
    } else {
        position->x.w.i = source->second_x;
        position->y.w.i = source->second_y;
        position->z.w.i = source->second_z;
    }
}
