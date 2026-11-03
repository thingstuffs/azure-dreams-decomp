#include "common.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "town/menu.h"
#include "shared/sprite_frame_state.h"

/* extern */


/* extern */

/* Update opposing scale offsets until the countdown ends, then restore unit scale. */
void update_opposing_scale_effect(TownObjectRecord *state, s32 unused_1, SpriteFrameState *scale, s32 unused_3) {
    u16 ticks_left;
    s32 scale_wave;
    s32 scale_offset;
    s32 rounded_wave;

    ticks_left = state->timer.as_u16 - 1;
    state->timer.as_u16 = ticks_left;
    if ((s16) ticks_left <= 0) {
        scale->scale_y = 0x1000;
        scale->scale_x = 0x1000;
        initialize_randomized_scale_timer(state);
        return;
    }
    scale_wave = rsin((s16) ticks_left * 0xBA);
    scale_offset = scale_wave >> 2;
    if (scale_wave < 0) {
        scale_offset = (s32) (scale_wave + 3) >> 2;
    }
    scale->scale_x = (s16) (0x1000 - scale_offset);
    rounded_wave = rsin((s16) state->timer.as_u16 * 0xBA);
    scale->scale_y = (s16) ((rounded_wave / 4) + 0x1000);
}
