#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_delay_views.h"
#include "town/map.h"
#include "town/map/position.h"
#include "town/person.h"

   /* arg1 in start_raised_position_pair */

/* Sets the record's pointer and state and copies its signed byte to the output's high half. */
void start_raised_position_pair(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *output = placement;

    NODE_HEADER(record_data)->update_callback = &process_raised_position_pair;
    output->z.v = (s32) (((s8)record_data->variant) << 0x10);
    record_data->timer = 5;
}
