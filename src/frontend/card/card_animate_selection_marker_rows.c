#include "common.h"
#include "frontend/card/command_panel.h"
#include "frontend/card.h"

/* Animate the menu selection marker and each row's horizontal offset and color. */
void card_animate_selection_marker_rows(CardDevCommandPanel *panel)
{
    s32 i;
    s32 step;
    s32 start;
    s32 delta;
    s32 num;
    u8 *slot;
    u8 offset;
    u8 next;
    u8 row_offset;

    start = panel->start_row;
    delta = panel->target_row - start;
    num = delta * (panel->frame << 4);
    step = num / panel->frames;
    step += 10;
    panel->resource_entry->block->fields.y = start * 16 + step;

    for (i = 0; i < 4; i++) {
        slot = (u8 *)panel + i + 0x7C;
        offset = *slot;
        if (i == panel->target_row) {
            step = (8 - offset) / (panel->frames - panel->frame + 1);
            next = offset + step;
        } else {
            next = offset;
            if (next != 0)
                next--;
        }
        *slot = next;
        row_offset = panel->row_offsets[i];
        panel->middle[i]->block->fields.x = row_offset + 0x24;
        panel->lower[i]->block->fields.x = row_offset + 0x8F;
        panel->left[i]->block->fields.x = row_offset + 9;
        panel->right[i]->block->fields.x = row_offset + 0x42;
        panel->middle[i]->block->color.r = panel->row_offsets[i] * 3 + 0x68;
        panel->middle[i]->block->color.g = panel->row_offsets[i] * 3 + 0x68;
        panel->middle[i]->block->color.b = panel->row_offsets[i] * 4 + 0x60;
    }

    if (panel->frame < panel->frames)
        panel->frame++;
}
