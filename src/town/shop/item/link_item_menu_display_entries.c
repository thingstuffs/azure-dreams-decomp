#include "common.h"
#include "engine/texture.h"
#include "town/shop/item.h"

extern u8 item_display_chain_indices[];

/* Calls build_reverse_indexed_chain with entries, item_display_chain_indices, 26. */
void link_item_menu_display_entries(s32 entries) {
    build_reverse_indexed_chain(entries, item_display_chain_indices, 26);
}
