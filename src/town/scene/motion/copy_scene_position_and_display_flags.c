#include "common.h"
#include "town/paired_indicators.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct {
    u8 pad0[12];
    u32 color;
    u8 pad10[4];
    u16 flags;
} Output;

/* Copies the selected source position and updates the output flag and color. */
void copy_scene_position_and_display_flags(IndicatorChild *control, Position *position, Output *output) {
    PairedIndicators *source = control->source;

    if (source->flags & 1) {
        output->flags |= 0x80;
    } else {
        output->flags &= ~0x80;
    }

    if (source->blink_color != 0) {
        output->color = 0xFFFFFF;
    } else {
        output->color = 0x808080;
    }

    if (control->use_first != 0) {
        position->x = source->first_x;
        position->y = source->first_y;
        position->z = source->first_z;
    } else {
        position->x = source->second_x;
        position->y = source->second_y;
        position->z = source->second_z;
    }
}
