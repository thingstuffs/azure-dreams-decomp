#ifndef TOWN_MENU_FADING_TRIANGLE_EFFECT_H
#define TOWN_MENU_FADING_TRIANGLE_EFFECT_H

#include "common.h"
#include "town/menu/view_state.h"

/* Body allocated by create_flickering_triangle for the fading triangle callback. */
typedef struct FadingTriangleEffectBody {
    /* 0x00 */ u8 pad_00[4];
    /* 0x04 */ u16 ticks_left;
    /* 0x06 */ s16 fade_period;
    /* 0x08 */ u16 center_offset;
    /* 0x0A */ u16 phase_x_offset;
    /* 0x0C */ u16 phase_y_offset;
    /* 0x0E */ u8 pad_0E[2];
    /* 0x10 */ s32 triangle_width;
    /* 0x14 */ State *parameters;
} FadingTriangleEffectBody;

#endif
