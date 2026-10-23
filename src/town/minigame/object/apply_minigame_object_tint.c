#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/paired_indicators.h"
#include "shared/dungeon_moving_views.h"


   /* arg1 in apply_minigame_object_tint */


/* Apply object flags and tint, and copy the selected value triplet. */
void apply_minigame_object_tint(IndicatorChild *state, MovingPosition *selected_values, SpriteFrameState *render_state) {
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
        selected_values->x = source->first_x;
        selected_values->y = source->first_y;
        selected_values->z = source->first_z;
    } else {
        selected_values->x = source->second_x;
        selected_values->y = source->second_y;
        selected_values->z = source->second_z;
    }
}
