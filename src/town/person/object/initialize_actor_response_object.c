#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object.h"
#include "town/person.h"
extern void create_object_given_position_preset(void *position);

extern s32 D_800D5598[];

// Sets up an object, clears its indexed flag, assigns its state pointer, and runs the follow-up update.
void initialize_actor_response_object(TownObjectRecord *object, ObjectPosition *followupValue, void *setupValue) {
    initialize_object_entries(object, setupValue, D_800D5598);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = install_actor_response_tables;
    create_object_given_position_preset(followupValue);
}
