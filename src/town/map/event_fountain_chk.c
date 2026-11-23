#include "common.h"
#include "shared/game_state.h"
#include "town/map.h"


/* event_fountain_chk: return the fountain event check flag. */
u8 event_fountain_chk(void) {
    return GAME_STATE->building_slots[16][0];
}
