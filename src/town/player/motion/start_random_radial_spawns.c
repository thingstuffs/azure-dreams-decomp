#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"
#include "town/player/motion.h"
#include "town/person.h"
#include "town/player/effect.h"

   /* arg1 in start_random_radial_spawns */




/* Set the record pointer and state, and copy its signed byte to the output in 16.16 format. */
void start_random_radial_spawns(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *output = placement;

    NODE_HEADER(record_data)->update_callback = tick_random_radial_spawns;
    output->z.v = (s32) (((s8)record_data->variant) << 0x10);
    record_data->timer = 5;
}
