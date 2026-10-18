#include "common.h"
void anyone_now_pos_get(s32 actor_id);                     /* extern */

/* player_now_pos_get: Calls the player position helper with mode 1. */
void player_now_pos_get(void) {
    anyone_now_pos_get(1);
}
