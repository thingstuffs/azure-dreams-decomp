#include "common.h"
#include "town/person/object_setup.h"
#include "shared/object_index_slots.h"
#include "town/person/object.h"

extern u32 person_motion_tag[4];
extern u32 person_slot_flag_handler_address[4];
typedef struct {
    u8 pad0;
    s8 val;
    u8 pad2[6];
} Rec8;


/* Installs object handlers, sets its status, and clears its object and slot state bytes. */
void initialize_object_handlers(TownObjectRecord *object, void *unused_context, void *unused_setup) {
    object->unk_50.as_pm = &person_motion_tag[0];
    object->unk_92 = 1;
    object->handler = &person_slot_flag_handler_address[0];
    object->unk_15 = 0;
    object_index_slots[object->slot].unk_01 = 0;
}
