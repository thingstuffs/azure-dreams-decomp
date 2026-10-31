#include "common.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"

typedef struct {
    u8 pad[0xA];
    u16 unkA;
} Func8009AA20Arg0;

typedef struct {
    u16 pad;
    u16 unk2;
} Func8009AA20Arg1;

/* Decrement the countdown, invoking its handler when exhausted or advancing the cursor by four. */
void tick_countdown_or_advance_cursor(Func8009AA20Arg0 *countdown_state, Func8009AA20Arg1 *cursor_state, SpriteFrameState *context_value) {
    u16 remaining_count;

    remaining_count = countdown_state->unkA - 1;
    countdown_state->unkA = remaining_count;
    if ((s16)remaining_count < 0) {
        initialize_record_with_handler_and_countdown_800(countdown_state, cursor_state, context_value);
        return;
    }
    cursor_state->unk2 += 4;
}
