#include "common.h"
#include "town/paired_indicators.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80024334_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_80024334_2;   /* arg2 in apply_minigame_object_tint */

   /* arg1 in apply_minigame_object_tint */


/* Apply object flags and tint, and copy the selected value triplet. */
void apply_minigame_object_tint(IndicatorChild *state, MovingPosition *selected_values, S_80024334_2 *render_state) {
    PairedIndicators *source;

    source = state->source;

    if (source->flags & 1) {
        render_state->unk_14 |= 0x80;
    } else {
        render_state->unk_14 &= 0xFF7F;
    }

    if (source->blink_color != 0) {
        render_state->unk_0C = 0x808080;
    } else {
        render_state->unk_0C = 0xFFFFFF;
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
