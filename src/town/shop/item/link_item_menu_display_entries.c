#include "common.h"

extern void build_reverse_indexed_chain(s32, void *, s32);
extern u8 item_display_chain_indices[];

/* Link entries in D_800D1594 order until an index reaches 26. */
void link_item_menu_display_entries(s32 entries) {
    build_reverse_indexed_chain(entries, item_display_chain_indices, 26);
}
