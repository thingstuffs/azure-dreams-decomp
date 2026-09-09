#include "common.h"
#include "m2c_compat.h"

M2C_UNK anyone_now_pos_get();                     /* extern */

/* player_now_pos_get: Calls the player position helper with mode 1. */
void player_now_pos_get(void) {
    anyone_now_pos_get(1);
}
