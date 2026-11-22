#include "town/player/position.h"
#include "common.h"
#include "town/player/scene_action_setup.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player.h"
#include "town/player/state.h"






/* Set up the object using its linked record and assign its next handler. */
void initialize_player_linked_record(TownObjectRecord *object, struct ObjectPosition *unused_position, struct SpriteFrameState *sprite) {
    dispatch_selected_entry_if_nonzero(object->handler_entries[8], object, sprite);
    object->unk_04 = &advance_player_position;
}
