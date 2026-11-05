#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/object.h"
#include "town/data.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern void forward_mother_event_update(void *object, void *param_1, void *param_2);
extern s32 D_800D5FA0[];


/* Initialize the object callback and clear its state values. */
void initialize_mother_event_object(TownObjectRecord *object, s32 unused, void *init_data) {
    initialize_object_entries((object), init_data, D_800D5FA0);
    mother_event_reset_byte = 0;
    object->handler = &forward_mother_event_update;
    object->heading = 0;
}
