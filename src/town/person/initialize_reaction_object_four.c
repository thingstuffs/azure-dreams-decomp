#include "town/person.h"
#include "town/person/mother_event_motion_g00670.h"
#include "town/person/object_setup.h"
extern s32 D_800D64F0[];


void initialize_reaction_object_four(PersonSetupState *object, void *unused, void *context) {
    initialize_object_entries(object, context, D_800D64F0);
    object->callback = decrement_reaction_timer_and_reinitialize;
    object->timer = 4;
}
