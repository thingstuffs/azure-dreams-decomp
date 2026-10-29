#include "common.h"
#include "engine/texture.h"
#include "town/shop.h"

extern u8 shop_node_order[];

/* Links the shop nodes in shop_node_order (limit 31) and returns the chain. */
void *link_shop_nodes_in_configured_order(s32 node_table) {
    return build_reverse_indexed_chain(node_table, shop_node_order, 31);
}
