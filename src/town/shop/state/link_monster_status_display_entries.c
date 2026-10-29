#include "common.h"
#include "engine/texture.h"
#include "town/shop/state.h"

extern u8 monster_display_chain_indices[];

/* Calls build_reverse_indexed_chain with target, monster_display_chain_indices, 24. */
void link_monster_status_display_entries(void *target) {
    build_reverse_indexed_chain(target, monster_display_chain_indices, 24);
}
