#include "common.h"
#include "dungeon/effect/motion.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libgte.h"
#include "shared/dungeon_effect_state.h"

/* Draw two concentric effect layers with phase-scaled height and radii. */
s32 draw_concentric_effect_layers(B22_81893474_EffectState *effect, s32 position, s32 render_param) {
    s32 inner_radius;
    s32 outer_radius;
    s32 height;
    s32 outer_brightness;

    outer_brightness = effect->timer.low_byte * 0x10;
    if (outer_brightness & 0xFF) {
        outer_brightness = 0xFF;
    }
    height = ((rsin(effect->timer.s << 6) >> 4) * 0x140) >> 8;
    inner_radius = (rsin(effect->timer.s << 6) * 2) >> 8;
    outer_radius = ((rsin(effect->timer.s << 6) >> 4) * 0x18) >> 8;
    draw_shaded_textured_cylinder(effect, position, render_param, (s16)(effect->field_14.u << 5), (s16)height,
                  (s16)inner_radius, 3, 0x40);
    draw_shaded_textured_cylinder(effect, position, render_param, (s16)((-( effect->field_14.u << 0x16)) >> 0x10),
                  (s16)height, (s16)outer_radius, 1, outer_brightness & 0xFF);
    return 0;
}
