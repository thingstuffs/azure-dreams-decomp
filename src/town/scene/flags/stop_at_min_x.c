#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

/* Sets the record flag and initializes the state with the supplied value. */
void stop_at_min_x(ColliderView *collider, ObjectPosition *position, s32 value) {
    collider->response_flags[2] = 1;
    position->x.v = value;
    position->velocity_x = 0;
}
