#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s32 moving_reaction_entries[];


/* Initialize the object and set its data pointer and initial field values. */
void initialize_orbiting_object(TownObjectRecord *object, ObjectPosition *unused_position, SpriteFrameState *sprite) {
    initialize_object_entries(object, sprite, moving_reaction_entries);
    object->state_callback.as_pm = &update_object_orbit_and_timer;
    object->origin_x = 0x50;
    object->timer = 0xD2;
}
