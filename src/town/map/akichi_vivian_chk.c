#include "common.h"
#include "shared/game_state.h"
#include "town/map.h"
#include "town/data.h"

/* akichi_vivian_chk: return the vacant-lot Vivian check flag. */
u8 akichi_vivian_chk(void) {
    return GAME_STATE->building_slots[31][0];
}
