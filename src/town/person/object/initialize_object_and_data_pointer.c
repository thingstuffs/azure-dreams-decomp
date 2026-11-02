#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s32 D_800D72AC[];


/* Initialize the object and set its data pointer and initial field values. */
void initialize_object_and_data_pointer(TownObjectRecord *object, s32 unused, void *init_value) {
    initialize_object_entries((object), init_value, D_800D72AC);
    object->unk_50.as_pm = &update_object_orbit_and_timer;
    object->unk_84.as_s16 = 0x50;
    object->timer.as_s16 = 0xD2;
}
