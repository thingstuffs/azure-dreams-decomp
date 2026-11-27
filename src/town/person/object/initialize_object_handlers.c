#include "common.h"
#include "town/person/object_setup.h"
#include "shared/object_index_slots.h"
#include "town/person/object.h"
#include "town/person_callbacks_api.h"



typedef struct {
    u8 pad0;
    s8 val;
    u8 pad2[6];
} Rec8;


/* Installs object handlers, sets its status, and clears its object and slot state bytes. */
void initialize_object_handlers(TownObjectRecord *object, ObjectPosition *unused_context, SpriteFrameState *unused_setup) {
    object->state_callback.as_pm = call_object_callback;
    object->animation_hold = 1;
    object->handler = dispatch_record_handler;
    object->scene_active = 0;
    object_index_slots[object->slot].active = 0;
}
