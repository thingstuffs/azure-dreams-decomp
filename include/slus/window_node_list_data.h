#ifndef SLUS_WINDOW_NODE_LIST_DATA_H
#define SLUS_WINDOW_NODE_LIST_DATA_H

#include "common.h"

/* Resident window node storage at 0x80082BC0. The next link-map symbol is
 * 0x80082D08, so the extent is 0x148 bytes. The runtime creator clears
 * 0x49 words and uses the first 0x20 bytes as a node-list header. The
 * town callback accesses still use the inherited byte-array spelling. */
extern u8 window_node_list_storage[0x148];

#endif
