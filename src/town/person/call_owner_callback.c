#include "common.h"
#include "m2c_compat.h"
#include "town/person.h"



/* Invokes the owner's callback. */
void call_owner_callback(OwnerCallbackObject *owner, void *motion, s32 context) {
    owner->callback(owner, motion, context);
}
