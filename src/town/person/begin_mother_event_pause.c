#include "town/person.h"
#include "town/person/mother_event_motion_g00670.h"
extern s32 mother_event_default_entries[];

void begin_mother_event_pause(TownObjectRecord *object, ObjectPosition *unused, SpriteFrameState *context) {
    initialize_object_entries(object, context, mother_event_default_entries);
    object->state_callback.as_pm = reset_mother_event_callback_on_expiry;
    mother_event_ticks.value = 21;
}
