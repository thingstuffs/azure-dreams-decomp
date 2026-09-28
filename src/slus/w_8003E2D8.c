#include "common.h"
#include "shared/game_work.h"

/* D_80083160: shared state table (own view here). field_8 (cur reading) is
 * accessed directly on the base struct; a separate history view starting
 * at the SAME offset+8 holds cur again at +0 (unused via this view), the
 * previous reading (old, +4) and the trg mask (+8). */

typedef struct {
    s32 cur;
    s32 old;
    s32 trg;
} Hist_8003E2D8;


extern s32 func_8003E240(s32 a0);

/* Updates controller state, clears invalid readings, and records newly pressed buttons. */
void func_8003E2D8(void)
{
    GameWork *pad_state = &gameWork;
    Hist_8003E2D8 *history = (Hist_8003E2D8 *)&pad_state->buttons;
    s32 prev_buttons = pad_state->buttons;
    s32 buttons;

    history->old = prev_buttons;
    pad_state->buttons = func_8003E240(0);

    if ((pad_state->buttons & 0xF000) == 0xF000) {
        pad_state->buttons = 0;
    }

    buttons = pad_state->buttons;
    history->trg = (buttons ^ history->old) & buttons;
}
