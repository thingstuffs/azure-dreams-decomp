#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "records/Rec_func_800233D0_arg0.h"

   /* ((S_80023600_3 *)(((Rec_func_800233D0_arg0 *)arg0)->unk_1A0))->unk_04 in card_boot_layout_command_panel */

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"

/* Initialize the panel and position its elements in three rows. */
void card_boot_layout_command_panel(CardCommandPanelBody *panel) {
    void *panel_arg = panel;
    s32 lower_x;
    s32 left_x;
    s32 right_x;
    s32 middle_x;
    s32 row_y;
    s32 lower_y;
    s32 row_index;

    panel->animation_frames = 1;
    panel->animation_tick = 1;
    card_boot_format_command_panel_labels(panel_arg);
    card_boot_set_centered_rectangle((s32)(panel_arg + 4), 0x36, 0x10);
    card_boot_bind_command_panel_resources(panel);
    row_index = 0;
    lower_x = 0x8E;
    left_x = 9;
    right_x = 0x42;
    middle_x = 0x24;
    row_y = 0xA;
    lower_y = 0x82;
    panel->heading->block->fields.y = 0x1A;
    do {
        panel->labels[row_index]->block->fields.x = lower_x;
        panel->labels[row_index]->block->fields.y = lower_y;
        panel->left[row_index]->block->fields.x = left_x;
        panel->left[row_index]->block->fields.y = row_y;
        panel->right[row_index]->block->fields.x = right_x;
        panel->right[row_index]->block->fields.y = row_y;
        panel->highlight[row_index]->block->fields.x = middle_x;
        lower_y += 0x10;
        panel->highlight[row_index]->block->fields.y = row_y;
        row_y += 0x10;
        row_index += 1;
    } while (row_index < 3);
    card_boot_reset_three_row_highlight(panel);
}
