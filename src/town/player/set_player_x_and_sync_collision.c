#include "town/player/position_handlers.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player.h"

extern s8 D_800CFCEB;


/* Set D_800CFCEB, initialize the record, and call copy_x_to_collision_motion. */
void set_player_x_and_sync_collision(ObjectPosition *record, s32 initial_value) {
    D_800CFCEB = 1;
    record->x.v = initial_value;
    record->velocity_x = 0;
    copy_x_to_collision_motion(record);
}
