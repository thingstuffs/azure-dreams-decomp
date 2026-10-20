#include "common.h"
#include "shared/game_work.h"
#include "shared/pad_state.h"

/* D_80083160: shared state table (own view here). field_8 (cur reading) is
 * accessed directly on the base struct; a separate history view starting
 * at the SAME offset+8 holds cur again at +0 (unused via this view), the
 * previous reading (old, +4) and the trg mask (+8). */


extern s32 read_combined_controller_buttons(s32 a0);

/* Updates controller state, clears invalid readings, and records newly pressed buttons. */
void update_controller_buttons_and_triggers(void)
{
    GameWork *pad_state = &g_game_work;
    ControllerButtonHistory *history = (ControllerButtonHistory *)&pad_state->buttons;
    s32 prev_buttons = pad_state->buttons;
    s32 buttons;

    history->old = prev_buttons;
    pad_state->buttons = read_combined_controller_buttons(0);

    if ((pad_state->buttons & 0xF000) == 0xF000) {
        pad_state->buttons = 0;
    }

    buttons = pad_state->buttons;
    history->trg = (buttons ^ history->old) & buttons;
}
