#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "town/person.h"

extern s32 D_800D6374[];


/* Load the indexed state value and install the object callback. */
void set_bounce_velocity(OwnerCallbackObject *object, ObjectPosition *position, SpriteFrameState *unused_output) {
    position->velocity_z = D_800D6374[object->contacts_left.as_s16];
    object->callback = &move_object_velocity;
}
