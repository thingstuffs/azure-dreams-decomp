#include "common.h"
#include "town/person/state.h"

extern TownIndexedHandler person_flag_state_callbacks[];

/* Invoke the callback selected by the object state. */
void invoke_flag_state_callback(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    person_flag_state_callbacks[(s16)object->phase](object, position, sprite);
}
