#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern s32 D_80083834[];

/* Tint the slot window's frame and show or hide its saved-slot marker at (102, 24). */
void card_devkit_set_window_saved_marker(CardDevSlotWindow *panel, s32 flag)
{
    CardMenuDisplayNode *marker;

    if (panel != 0) {
        panel->body.frame_block.words[0] = 0x808080;
        marker = &panel->body.entries[9]->display;
        if (flag != 0) {
            marker->payload.data = D_80083834;
        } else {
            marker->payload.word = 0;
        }
        marker->block->fields.x = 102;
        marker->block->fields.y = 24;
    }
}
