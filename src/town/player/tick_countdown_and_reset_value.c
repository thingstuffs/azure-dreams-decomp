#include "town/player/initialize_record_with_handler_table_api.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"
#include "town/player/record.h"

/* extern */



/* Decrement the countdown, then call initialize_record_with_handler_table and set unk_10 to 0x400 at zero. */
void tick_countdown_and_reset_value(TownPlayerRecord *state, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 remaining_ticks;

    remaining_ticks = state->timer.as_u16 - 1;
    state->timer.as_u16 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        initialize_record_with_handler_table(state, position, sprite);
        state->unk_10.as_s16 = 0x400;
    }
}
