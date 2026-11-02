#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"



/* Invokes the owner's callback. */
void call_owner_callback(OwnerCallbackObject *owner, ObjectPosition *motion, SpriteFrameState *output) {
    owner->callback(owner, motion, output);
}
