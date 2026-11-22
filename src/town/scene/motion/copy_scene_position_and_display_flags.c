#include "common.h"
#include "town/paired_indicators.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Copies the selected source position and updates the output flag and color. */
void copy_scene_position_and_display_flags(IndicatorChild *control, ObjectPosition *position, SpriteFrameState *output) {
    PairedIndicators *source = control->source;

    if (source->flags & 1) {
        output->flags |= 0x80;
    } else {
        output->flags &= ~0x80;
    }

    if (source->blink_color != 0) {
        output->color.word = 0xFFFFFF;
    } else {
        output->color.word = 0x808080;
    }

    if (control->use_first != 0) {
        position->x.w.i = source->first_x;
        position->y.w.i = source->first_y;
        position->z.w.i = source->first_z;
    } else {
        position->x.w.i = source->second_x;
        position->y.w.i = source->second_y;
        position->z.w.i = source->second_z;
    }
}
