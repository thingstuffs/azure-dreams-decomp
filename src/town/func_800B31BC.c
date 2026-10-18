#include "common.h"

extern void build_reverse_indexed_chain(s32, void *, s32);
extern u8 D_800D15CC[];

/* Links nodes in the order specified by D_800D15CC. */
void link_shop_nodes_in_configured_order(s32 node_table) {
    build_reverse_indexed_chain(node_table, D_800D15CC, 31);
}
