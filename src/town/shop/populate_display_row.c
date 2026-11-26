#include "common.h"
#include "engine/item.h"
#include "engine/menu.h"
#include "town/shop.h"
#include "town/shop/position.h"
#include "town/shop/stat_display.h"



/* Populate and position a display row from an entry. */
void populate_display_row(DungeonItemEntry *entry, ItemMenuPart **parts, s32 row)
{
    u8 detail_info[16];
    s32 entry_info[2];
    s32 row_offset;
    s32 text_y;
    s32 entry_value;
    s32 *info_out;
    ItemMenuPart **widgets;

    info_out = entry_info;
    entry_value = select_item_data(entry, info_out);
    row_offset = row * 0x10;
    text_y = row_offset + 0xD8;
    widgets = (ItemMenuPart **)(row * sizeof(*parts) + (unsigned long)parts);
    set_display_entry_text_and_position(widgets[8], entry_value, entry_info[0], 0x58, text_y);
    set_storage_entry_text(widgets[11],
                  format_optional_signed_value(entry, detail_info), 0, 0xA0, text_y);
    widgets[14]->handler = (void *)(long)lookup_item_category_mapped_value(
        entry->kind, entry->unk_00);
    widgets[14]->position->x = -0x30;
    widgets[14]->position->y =
        (s16)(row_offset + 0x66);
}

/* MECHANISM: Sibling detail_info/entry_info arrays produce the retail 0x48 frame; keeping the
   entry_info pointer live hoists sp+0x28 and lets the $s2 save fill the first jal slot. */
