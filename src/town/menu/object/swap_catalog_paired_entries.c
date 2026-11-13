#include "common.h"
#include "town/menu/catalog.h"
#include "town/menu/catalog_parts.h"
#include "town/menu/object.h"


/* Swaps paired entry values and node halfwords, toggles the state flag, and updates. */
void swap_catalog_paired_entries(CatalogDisplay *state)
{
    ItemMenuPart **second_entry;
    ItemMenuPart **first_entry;
    ItemMenuPart **entries;
    ItemMenuPart *first_word;
    void *saved_word;
    s32 entry_index;
    u16 saved_half;
    ItemMenuPartPosition *first_node;

    entry_index = 2;
    entries = catalog_display_node_slots;
    second_entry = entries + 16;
    first_entry = entries + 2;
    do {
        first_word = *first_entry;
        first_entry++;
        saved_word = first_word->handler;
        entry_index++;
        first_word->handler = (*second_entry)->handler;
        (*second_entry)->handler = saved_word;
        second_entry++;
    } while (entry_index < 14);

    first_node = catalog_display_node_slots[8]->position;
    saved_half = (u16)first_node->x;
    first_node->x = (u16)catalog_display_node_slots[22]->position->x;
    catalog_display_node_slots[22]->position->x = saved_half;

    state->unk_16 ^= 1;
    select_paired_value_tables(state);
}
