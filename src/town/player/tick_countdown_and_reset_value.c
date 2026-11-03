#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"

/* extern */

typedef struct S_800980B4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800980B4_0;   /* arg0 in tick_countdown_and_reset_value */


/* Decrement the countdown, then call initialize_record_with_handler_table and set unk_10 to 0x400 at zero. */
void tick_countdown_and_reset_value(S_800980B4_0 *state, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 remaining_ticks;

    remaining_ticks = state->unk_0A - 1;
    state->unk_0A = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_record_with_handler_table(state, position, sprite);
        state->unk_10 = 0x400;
    }
}
