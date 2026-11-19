#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

/* Set the object flag, store the state value, and clear the state's secondary field. */
void stop_at_max_y(ColliderView *collider, ObjectPosition *position, s32 value) {
    collider->response_flags[5] = 1;
    position->y.v = value;
    position->velocity_y = 0;
}
