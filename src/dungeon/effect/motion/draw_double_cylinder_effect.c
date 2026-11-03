#include "dungeon/effect/motion.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libgte.h"
#include "shared/dungeon_effect_state.h"

   /* arg0 in func_80024EF8 */

/* cfail-repair: tf7-phase1-cache-v3 */

/* Draws two effect layers with opposing angles and phase-dependent sizes. */
s32 draw_counter_rotating_cylinders(B22_81893474_EffectState *effect, MovingPosition *center, s32 unused_value) {
    s32 primary_size;
    s32 secondary_size;
    u8 fade;

    fade = ~(effect->timer.low_byte * 0x10);
    primary_size = (s32) (rsin((0x10 - effect->timer.s) << 6) * 2) >> 8;
    secondary_size = (s32) ((rsin((0x10 - effect->timer.s) << 6) >> 4) * 0x18) >> 8;
    draw_shaded_textured_cylinder(effect, center, unused_value, (s16) (effect->field_14.u << 5), 0x140, (s32) (s16) primary_size, 3, 0x40);
    draw_shaded_textured_cylinder(effect, center, unused_value, (s16) ((s32) (0 - (effect->field_14.u << 0x16)) >> 0x10), 0x140,
        (s32) (s16) secondary_size, 1, fade & 0xFF);
    return 0;
}
