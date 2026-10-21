#include "common.h"

extern void build_reverse_indexed_chain(void *a0, void *a1, int a2);
extern u8 monster_display_chain_indices[];

/* Passes the target and D_800D17C4 to build_reverse_indexed_chain with argument 24. */
void link_monster_status_display_entries(void *target) {
    build_reverse_indexed_chain(target, monster_display_chain_indices, 24);
}
