#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

/*
 * Sets the object flag at offset 0x38, stores the supplied initial state at offset 4, and clears
 * its motion word at offset 0x10.
 */
void stop_at_min_y(ColliderView *collider, ObjectPosition *position, s32 value) {
    collider->response_flags[4] = 1;
    position->y.v = value;
    position->velocity_y = 0;
}
