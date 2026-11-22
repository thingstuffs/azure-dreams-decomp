#include "common.h"
#include "shared/def_table.h"
#include "engine/entity.h"
#include "slus.h"
#include "town/shop.h"


void set_display_entry_text_and_position(ItemMenuPart *entry, s32 text, s32 style, s16 x, s32 y);

typedef struct S_800B6094_0 {
    u8 unk_00;
    u8 unk_01;
} S_800B6094_0;   /* held_arg0 in populate_action_display_row */

typedef struct S_800B6094_2 {
    s32 unk_00;
    u8 pad_04[0xC];
    u8 unk_10;
} S_800B6094_2;

/* Populate a display row with entry text and a positioned icon. */
void populate_action_display_row(void *entry_data, ItemMenuPart **parts, s32 row_index) {
    S_800B6094_0 *entry = entry_data;
    s32 text_buffer[3];
    ItemMenuPart *icon;
    s32 icon_id;
    s32 text_y;
    s32 display_value;
    ItemMenuPart **row_data;
    S_800B6094_2 *entry_info;
    ItemMenuPartPosition *position;

    text_y = (row_index * 0x10) + 0xD8;
    row_data = (ItemMenuPart **)(row_index * 4 + (long)parts);
    entry_info = (S_800B6094_2 *)((entry->unk_00 * 0x14) + ((u8 *)item_action_definitions));
    set_display_entry_text_and_position(row_data[8], entry_info->unk_00, 0, 0x58, text_y);
    set_storage_entry_text(row_data[11], build_encoded_display_sequence(entry->unk_01, text_buffer), 0, 0xA0, text_y);
    icon_id = get_low_flag_priority(entry_info->unk_10);
    icon = row_data[14];
    if (test_item_action_pattern(entry->unk_00) != 0) {
        display_value = lookup_patterned_display_icon(icon_id);
    } else {
        display_value = lookup_unpatterned_display_icon(icon_id);
    }
    icon->handler = (void *)(long)display_value;
    parts[row_index + 14]->position->x = -0x30;
    position = parts[row_index + 14]->position;
    position->y = (row_index * 0x10) + 0x67;
}
