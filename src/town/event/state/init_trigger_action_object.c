#include "common.h"
#include "shared/object_node.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"
#include "town/event/state.h"
#include "town/player/object.h"
#include "town/map.h"

   /* arg1 in init_trigger_action_object */

/* Initialize the record pointers and clear the associated state field. */
void init_trigger_action_object(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *state = placement;

    NODE_HEADER(record_data)->update_callback = retire_object_on_check_or_callback;
    record_data->unk_50.as_pv = &set_guy_sword_pickup_flag;
    state->z.v = 0;
}
