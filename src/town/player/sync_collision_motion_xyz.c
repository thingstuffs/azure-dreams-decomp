#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/state.h"

#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                         /* extern */

/*
 * Copies all three source coordinates into town collision state through the component helpers,
 * clearing their paired motion words.
 */
void sync_collision_motion_xyz(ObjectPosition *context) {
    copy_x_to_collision_motion(context);
    sync_collision_motion_y((context));
    copy_z_to_collision_motion((context));
}
