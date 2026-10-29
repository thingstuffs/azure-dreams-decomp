#include "common.h"
#include "town/person.h"
#include "town/player.h"

/* player_now_pos_get: Calls the player position helper with mode 1. */
void player_now_pos_get(void) {
    anyone_now_pos_get(1);
}
