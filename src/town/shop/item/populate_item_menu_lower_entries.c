/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "shared/item_menu.h"

s32 lookup_item_category_mapped_value(s32, s32);

/* Leading id and kind bytes of a listed item record. */
typedef struct S_800AF520_2 {
    u8 unk_00;
    u8 unk_01;
} S_800AF520_2;

/* Fill slots 6 through 15 from the current page of entries, then clear unused slots. */
void populate_item_menu_lower_entries(ItemMenuObject *context) {
    ItemMenuPart *empty_slot;
    ItemMenuPart **slots;
    register s32 entry_index;
    s32 page_index;
    s32 index_offset;
    s32 value;
    register s32 has_entry;
    s32 slot_index;
    s32 has_slot;
    S_800AF520_2 *entry;
    ItemMenuPart *slot;
    ItemMenuState *entries;
    ItemMenuObject *ctx = context;

    page_index = ctx->menu->page;
    slot_index = 6;
    index_offset = page_index << 2;
    index_offset += page_index;
    entry_index = index_offset << 1;
    while (1) {
        entries = ctx->menu;
        has_entry = entry_index < entries->count;
        if (has_entry == 0) {
            break;
        }
        entry = entries->entries[entry_index];
        value = lookup_item_category_mapped_value(entry->unk_01, entry->unk_00);
        entry_index += 1;
        slots = ctx->parts;
        slot = slots[slot_index];
        slot_index += 1;
        slot->handler = (void *)value;
        has_slot = slot_index < 0x10;
        if (has_slot == 0) {
            break;
        }
    }
    while (slot_index < 0x10) {
        empty_slot = ctx->parts[slot_index];
        slot_index += 1;
        empty_slot->handler = 0;
    }
}
