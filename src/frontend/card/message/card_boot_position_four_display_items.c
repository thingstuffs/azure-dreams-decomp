#include "frontend/card/message_display.h"
#include "common.h"
#include "frontend/card/message.h"

extern s32 func_80051B50(void *buffer, s32 value, s32 option);
extern u8 card_layout_text_items[];

/* Position and update four display items using the selected table row. */
void card_boot_position_four_display_items(u8 *state)
{
    s32 item_index;
    s32 draw_offset;
    s32 vertical_offset;
    u8 *item_cursor;
    CardMenuDisplayNode *item;
    u32 entry_addr;
    u32 row_addr;
    u8 *item_table;

    item_index = 0;
    item_table = card_layout_text_items;
    draw_offset = 0x234;
    vertical_offset = 0;
    item_cursor = state;
    do {
        u8 *draw_buffer;

        draw_buffer = state + draw_offset;
        draw_offset += 0x108;
        item = ((CardDevDialogDisplay *)item_cursor)->entries[0];
        item_cursor += 4;
        item->block->fields.x = 0x124 - (((CardDevDialogDisplay *)state)->width / 2);
        entry_addr = (u32)(item_index * 4);
        item->block->fields.y = vertical_offset - (((CardDevDialogDisplay *)state)->height / 2) + 0xFC;
        item_index++;
        vertical_offset += 0x11;
        row_addr = (u32)(((CardDevDialogDisplay *)state)->layout_index * 0x10);
        row_addr += (u32)(unsigned long)item_table;
        entry_addr += row_addr;
        item->payload.word = func_80051B50(
            draw_buffer,
            *(s32 *)(unsigned long)entry_addr,
            1);
    } while (item_index < 4);
}
