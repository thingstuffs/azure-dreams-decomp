#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"
#include "town/data.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern void forward_mother_event_update(TownObjectRecord *object, ObjectPosition *param_1, SpriteFrameState *param_2);
extern s32 mother_event_default_entries[];


/* Initialize the object callback and clear its state values. */
void initialize_mother_event_object(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite) {
    initialize_object_entries((object), sprite, mother_event_default_entries);
    mother_event_reset_byte = 0;
    object->handler = &forward_mother_event_update;
    object->heading = 0;
}
