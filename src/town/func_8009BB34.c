/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/action_reset_data.h"
#include "town/player/object_initialization_g00546.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
#include "town/player/object.h"
#include "town.h"
#include "town/data.h"

void init_four_tick_target_action(TownObjectRecord *object, ObjectPosition *motion_context, void *handler_context) {
    dispatch_selected_entry_if_nonzero(&player_event_handler_entries, object, handler_context);
    town_action_reset_byte = 0;
    object->unk_04 = &target_action_update_address;
    object->unk_0A = 4;
    clear_object_velocity((motion_context));
}
