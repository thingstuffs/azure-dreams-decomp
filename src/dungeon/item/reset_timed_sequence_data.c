#include "common.h"
#include "shared/game_state.h"
#include "m2c_compat.h"
#include "dungeon/item.h"


/* Stores address 0x80013720 in the pointer slot at 0x8001371C. */
void reset_timed_sequence_data(void) {
    GAME_STATE->log.data = GAME_STATE->log_data;
}
