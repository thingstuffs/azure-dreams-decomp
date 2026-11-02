#include "common.h"
#include "engine/texture.h"
#include "town/shop/state.h"
#include "town/data.h"

/* Links the monster status entries through monster_display_chain_indices (limit 24) and returns the chain. */
void *link_monster_status_display_entries(void *target) {
    return build_reverse_indexed_chain(target, monster_display_chain_indices, 24);
}
