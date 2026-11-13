#include "town/player/position_handlers.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/state.h"

/* extern */
extern s8 D_800CFCED;

/* Set D_800CFCED, initialize the record, and call sync_collision_motion_y. */
void set_player_y_and_sync_collision(ObjectPosition *record, s32 initial_value) {
    D_800CFCED = 1;
    record->y.v = initial_value;
    record->velocity_y = 0;
    sync_collision_motion_y(record);
}
