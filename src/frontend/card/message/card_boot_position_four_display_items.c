#include "frontend/card/message_display.h"
#include "common.h"
#include "frontend/card/message.h"
#include "frontend/card/server_imports.h"

/* Position and update four display items using the selected table row. */
void card_boot_position_four_display_items(CardDevDialogDisplay *state)
{
    s32 item_index;
    s32 draw_offset;
    s32 vertical_offset;
    MenuDisplayNode *item;
    u32 entry_addr;
    u32 row_addr;
    u8 *(*item_table)[4];

    item_index = 0;
    item_table = card_layout_text_items;
    draw_offset = 0x234;
    vertical_offset = 0;
    do {
        u8 *draw_buffer;

        draw_buffer = (u8 *)state + draw_offset;
        draw_offset += sizeof(state->text_buffers[0]);
        item = state->entries[item_index];
        item->block->fields.x = 0x124 - (state->width / 2);
        entry_addr = (u32)(item_index * 4);
        item->block->fields.y = vertical_offset - (state->height / 2) + 0xFC;
        item_index++;
        vertical_offset += 0x11;
        row_addr = (u32)(state->layout_index * 0x10);
        row_addr += (u32)(unsigned long)item_table;
        entry_addr += row_addr;
        item->draw_commands = func_80051B50(
            draw_buffer,
            (s32)(unsigned long)*(u8 **)(unsigned long)entry_addr,
            1);
    } while (item_index < 4);
}
