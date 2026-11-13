#include "common.h"
#include "shared/town_object.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_effect_views.h"
#include "town.h"
#include "town/event/state.h"
#include "town/player/object.h"


   /* arg1 in init_item_flag_check_object */

/* Initialize the record's pointers and clear the associated state field. */
void init_item_flag_check_object(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *state = placement;

    NODE_HEADER(record_data)->update_callback = &retire_object_on_check_or_callback;
    record_data->unk_50.as_pm = &set_resident_flag_when_item_present;
    state->z.v = 0;
}
