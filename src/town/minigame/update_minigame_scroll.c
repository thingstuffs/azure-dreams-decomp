#include "common.h"
#include "town/minigame.h"


/* Updates scrolling through 12 positions, accelerating or settling according to state. */
void update_minigame_scroll(MinigameDisplayObjectsBody *scroll)
{
    s32 state;
    state = scroll->state.s;
    switch (state) {

    case 0:
        scroll->scroll_offset.s = 0;
        scroll->step.s = 0;
        draw_scrolling_column(scroll->column,
                      scroll->column_offset,
                      scroll->scroll_offset.s);
        scroll->state.s = 1;
        return;

    case 2:
    {
        u16 tick;
        tick = scroll->ticks;
        scroll->ticks = tick + 1;
        if ((tick & 1) != 0) {
            if (scroll->step.s < 12) {
                scroll->step.s++;
            } else {
                scroll->state.s = 3;
            }
        }
    }

    case 3:
        scroll->scroll_offset.u = scroll->scroll_offset.u - scroll->step.u;
        if ((s16)scroll->scroll_offset.u < 0) {
            do {
                scroll->scroll_offset.u += 32;
                scroll->column_offset = (scroll->column_offset + 1) % 12;
            } while ((s16)scroll->scroll_offset.u < 0);
        }
        draw_scrolling_column(scroll->column, scroll->column_offset, scroll->scroll_offset.s);
        return;

    case 4:
        scroll->scroll_offset.u -= (s32)(scroll->scroll_offset.u << 16) >> 18;
        if ((s16)scroll->scroll_offset.u < 4) {
            scroll->scroll_offset.u = 0;
            scroll->state.u = 0;
        }
        draw_scrolling_column(scroll->column,
                      scroll->column_offset,
                      scroll->scroll_offset.s);
        return;

    case 1:
        return;
    }
}
