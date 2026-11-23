#include "common.h"
#include "shared/game_state.h"
#include "town/shop.h"

/* Look up a free slot in the twenty-entry carried item pool. */
void find_unused_default_pool_slot(void) {
    find_unused_pool_slot(GAME_STATE->item_list, 0, 20);
}
