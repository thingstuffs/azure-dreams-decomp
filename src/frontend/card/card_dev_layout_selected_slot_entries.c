#include "common.h"
#include "frontend/card/slot_marker.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Sets up display element content and positions for the selected entry. */
void card_dev_layout_selected_slot_entries(CardDevMenu10 *window) {
    CardDevMenuEntry *element;
    s32 formatted_value;

    element = window->entries[5];
    element->display.block->fields.x = 0x70;
    element->display.block->fields.y = 0x10;
    element->display.payload.data = &D_80084158;

    element = window->entries[1];
    element->display.payload.data = (void *) func_80051B50(window->title_text, (window->slot_index << 7) + (s32) &card_slot_detail_records[0], 1);
    element->display.block->fields.x = 0xF0;
    element->display.block->fields.y = 0x91;

    element = window->entries[2];
    element->display.payload.data = (void *) func_80051B50(window->label_text, (s32) &D_804005EC, 1);
    element->display.block->fields.x = 0x160;
    element->display.block->fields.y = 0x91;

    element = window->entries[4];
    func_80051804(card_slot_detail_records[window->slot_index].words[8], 4, &formatted_value);
    remap_flagged_string_bytes_80051900(&formatted_value);
    element->display.payload.data = (void *) build_positioned_text_glyphs_80051520(window->value_text, &formatted_value, 1);
    element->display.block->fields.x = 0x13F;
    element->display.block->fields.y = 0x91;

    element = window->entries[7];
    element->display.payload.data = window->slot_packets;
    element->display.block->fields.x = 0xAE;
    element->display.block->fields.y = 0x18;
}
