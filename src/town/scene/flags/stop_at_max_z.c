#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/scene/flags.h"
/* Set the state flag, initialize the object's fixed-point value, and clear its paired field. */
void stop_at_max_z(ColliderView *collider, ObjectPosition *position, s32 value) {
    collider->response_flags[1] = 1;
    position->z.v = (s32) (value << 0x10);
    position->velocity_z = 0;
}
