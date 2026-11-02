#include "common.h"
#include "engine/texture.h"
#include "town/shop/item.h"
#include "town/data.h"

/* Links the item menu entries through item_display_chain_indices (limit 26) and returns the chain. */
void *link_item_menu_display_entries(void *entries) {
    return build_reverse_indexed_chain(entries, item_display_chain_indices, 26);
}
