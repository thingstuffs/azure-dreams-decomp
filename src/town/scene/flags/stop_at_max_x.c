#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

/* Sets the control flag and initializes the record with a value and a cleared trailing field. */
void stop_at_max_x(ColliderView *collider, ObjectPosition *position, s32 value) {
    collider->response_flags[3] = 1;
    position->x.v = value;
    position->velocity_x = 0;
}
