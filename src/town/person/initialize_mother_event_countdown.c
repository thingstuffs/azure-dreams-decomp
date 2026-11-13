#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"
#include "town/data.h"
#include "town/person/mother_event_motion_g00670.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s32 D_800C7E70;


/* Initialize the object state, callback, countdown, and starting value. */
void initialize_mother_event_countdown(TownObjectRecord *object, s32 unused, void *init_data) {
    initialize_object_entries((object), init_data, &mother_event_object_entries);
    mother_event_reset_byte = 0;
    object->handler = &D_800C7E70;
    object->timer = 0xA;
    object->heading = 0xC00;
}
