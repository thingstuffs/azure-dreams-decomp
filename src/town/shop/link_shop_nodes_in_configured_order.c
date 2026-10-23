#include "common.h"

extern void build_reverse_indexed_chain(s32, void *, s32);
extern u8 shop_node_order[];

/* Calls build_reverse_indexed_chain with node_table, shop_node_order, 31. */
void link_shop_nodes_in_configured_order(s32 node_table) {
    build_reverse_indexed_chain(node_table, shop_node_order, 31);
}
