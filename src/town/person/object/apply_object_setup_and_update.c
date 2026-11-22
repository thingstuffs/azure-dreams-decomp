#include "common.h"
#include "shared/town_object.h"





#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person/object.h"
void install_object_handler_and_clear_slot_flag(void *object, void *update_context, void *setup_context);


/* Apply setup from the object descriptor and then run the object update. */
void apply_object_setup_and_update(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *setup_context) {
    initialize_object_entries(object, setup_context, object->descriptor->entries[1]);
    install_object_handler_and_clear_slot_flag(object, update_context, setup_context);
}
