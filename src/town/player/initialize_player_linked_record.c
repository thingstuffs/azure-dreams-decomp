#include "town/player/position.h"
#include "common.h"
#include "town/player/scene_action_setup.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player.h"






/* Set up the object using its linked record and assign its next handler. */
void initialize_player_linked_record(TownObjectRecord *object, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry(object->handler_entries[8], object, ptr2);
    object->unk_04.as_pm = &advance_player_position;
}
