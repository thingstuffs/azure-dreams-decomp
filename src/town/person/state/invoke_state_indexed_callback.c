#include "town/person/jump_motion.h"
#include "town/person/state.h"

extern TownIndexedHandler person_state_callbacks[];

/* Invoke the town callback selected by the object state. */
void invoke_state_indexed_callback(TownObjectRecord *object, ObjectPosition *position, SpriteFrameState *sprite) {
    TownIndexedHandler *callbacks = person_state_callbacks;
    s32 state_index = (s16)object->phase;
    callbacks[state_index](object, position, sprite);
}
