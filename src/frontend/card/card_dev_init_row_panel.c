#include "frontend/card/command_panel.h"
#include "common.h"
#include "shared/widget_views.h"
#include "frontend/card.h"








   /* ((S_8001C8C8_3 *)(((S_8001C8C8_1 *)arg0)->unk_1B8))->unk_04 in card_dev_init_row_panel */





void initialize_values(CardDevCommandPanel *panel, s32 unused_row_y, s32 unused_lower_y, s32 unused_row);       /* extern */
u8 *func_80403868(u8 *packets, s32 width, s32 height);


/* Initialize the panel and position four rows of display elements. */
void card_dev_init_row_panel(CardDevCommandPanel *panel) {
    s32 lower_x;
    s32 left_x;
    s32 right_x;
    s32 middle_x;
    s32 row_y;
    s32 lower_y;
    s32 row;


    panel->unk_80 = 1;
    panel->unk_84 = 1;
    card_dev_bind_row_labels(panel);
    func_80403868(panel->highlight_packets, 0x36, 0x10);
    card_dev_init_row_tables(panel);
    row = 0;
    lower_x = 0x8E;
    left_x = 9;
    right_x = 0x42;
    middle_x = 0x24;
    row_y = 0xA;
    lower_y = 0x82;
    panel->marker->block->fields.y = 0x22;
    for (; row < 4; row++) {
        panel->lower[row]->block->fields.x = lower_x;
        panel->lower[row]->block->fields.y = lower_y;
        panel->left[row]->block->fields.x = left_x;
        panel->left[row]->block->fields.y = row_y;
        panel->right[row]->block->fields.x = right_x;
        panel->right[row]->block->fields.y = row_y;
        panel->middle[row]->block->fields.x = middle_x;
        lower_y += 0x10;
        panel->middle[row]->block->fields.y = row_y;
        row_y += 0x10;
    }
    initialize_values(panel, row_y, lower_y, row);
}
