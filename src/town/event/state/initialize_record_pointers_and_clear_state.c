#include "common.h"
#include "shared/object_node.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/dungeon_effect_views.h"
#include "town/event/state.h"
#include "town/player/object.h"

   /* arg1 in initialize_record_pointers_and_clear_state */



extern void trigger_action_and_finish_record(u16 *record);

/* Initialize the record pointers and clear the associated state field. */
void initialize_record_pointers_and_clear_state(TownObjectRecord *record_data, ObjectPosition *placement, struct SpriteFrameState *unused_sprite) {
    ObjectPosition *state = placement;

    NODE_HEADER(record_data)->update_callback = retire_object_on_check_or_callback;
    record_data->unk_50.as_pv = &trigger_action_and_finish_record;
    state->z.v = 0;
}
