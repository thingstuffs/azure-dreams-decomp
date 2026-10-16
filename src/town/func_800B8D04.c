#include "common.h"

extern void buildReverseIndexedChain(s32 node_table, void *indices, s32 index_limit);
extern u8 D_800D17AC[];

/* Chains nodes using D_800D17AC indices until an index reaches 24. */
void townLinkMonsterStatusMainEntries(s32 nodes) {
    buildReverseIndexedChain(nodes, D_800D17AC, 24);
}
