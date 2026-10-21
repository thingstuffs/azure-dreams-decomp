#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* Adds each of the three motion increments to its corresponding position component. */
void add_motion_deltas_to_position(ObjectPosition *motion) {
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
}
