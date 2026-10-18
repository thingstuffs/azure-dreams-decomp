#include "common.h"

extern void build_reverse_indexed_chain(s32 node_table, void *indices, s32 index_limit);
extern u8 D_800D17AC[];

/* Chains nodes using D_800D17AC indices until an index reaches 24. */
void link_monster_status_main_entries(s32 nodes) {
    build_reverse_indexed_chain(nodes, D_800D17AC, 24);
}
