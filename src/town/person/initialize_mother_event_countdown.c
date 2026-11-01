#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 mother_event_reset_byte;
extern s32 D_800C7E70;
extern s32 mother_event_object_entries;


/* Initialize the object state, callback, countdown, and starting value. */
void initialize_mother_event_countdown(TownObjectRecord *object, s32 unused, void *init_data) {
    initialize_object_entries((Struct800C5724 *)(object), init_data, &mother_event_object_entries);
    mother_event_reset_byte = 0;
    object->handler = &D_800C7E70;
    object->timer.as_s16 = 0xA;
    object->heading.as_s16 = 0xC00;
}
