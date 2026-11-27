#include "common.h"
#include "shared/town_object.h"
#include "town/person/object.h"

extern s32 D_800D6220[];
extern s32 *mia_animation_lists[];
extern PersonDescriptor mia_descriptor;
extern s32 mia_state_handlers[];
extern TownIndexedHandler mia_script_action_handlers[];

/* Assign the object data pointers and link the shared data entry. */
void set_object_data_tables_with_link(TownObjectRecord *object) {
    object->state_handlers = mia_state_handlers;
    object->indexed_handlers = mia_script_action_handlers;
    object->animation_tables.as_pps32 = mia_animation_lists;
    object->descriptor = &mia_descriptor;
    mia_descriptor.entries[1] = D_800D6220;
}
