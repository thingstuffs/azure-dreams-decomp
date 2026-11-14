#include "town/person.h"
#include "town/person/mother_event_motion_g00670.h"
#include "town/person/object_setup.h"
extern s32 D_800D64F0[];


void start_reaction_countdown(PersonSetupState *object, void *unused, void *context) {
    initialize_object_entries(object, context, D_800D64F0);
    object->callback = restart_reaction_when_timer_ends;
    object->timer = 4;
}
