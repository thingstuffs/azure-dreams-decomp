#include "common.h"

#include "town/person/state_updates.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "town/person.h"
#include "town/person/object.h"


/* Updates the object using its stored value and installs its next handler. */
void install_stored_value_handler(TownObjectRecord *object, ObjectPosition *unused, SpriteFrameState *update_arg) {
    initialize_object_entries(object, update_arg, *object->animation_tables.as_pps32);
    object->state_callback.as_pm = forward_to_select_setup_path;
}
