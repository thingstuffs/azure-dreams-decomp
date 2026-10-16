#include "common.h"

extern void buildReverseIndexedChain(s32, void *, s32);
extern u8 D_800D15CC[];

/* Links nodes in the order specified by D_800D15CC. */
void townLinkShopNodesInConfiguredOrder(s32 node_table) {
    buildReverseIndexedChain(node_table, D_800D15CC, 31);
}
