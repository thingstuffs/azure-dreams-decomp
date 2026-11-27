#include "town/person.h"
#include "town/person/mother_event_motion_g00670.h"
#include "town/person/object_setup.h"
extern s32 D_800D64F0[];


void start_reaction_countdown(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    initialize_object_entries(object, sprite, D_800D64F0);
    object->state_callback.as_pm = restart_reaction_when_timer_ends;
    object->timer = 4;
}
