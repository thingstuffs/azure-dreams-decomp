#include "common.h"
#include "shared/town_object.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"                /* extern */
#include "town/person/state_updates.h"
#include "engine/window.h"


/* Initializes the object, assigns its state data, and sets a value in multiples of 21. */
void initialize_object_assigns_state_data(TownObjectRecord *object, void *unusedArg, void *initializationArg) {
    initialize_object_entries((object), initializationArg, *object->unk_7C.as_pps32);
    object->unk_50.as_pm = &run_unhandled_update_and_choose_direction;
    object->timer = (s16) (((scale_random_to_unsigned_halfword_limit(4) & 0xFFFF) * 0x15) + 0x15);
}
