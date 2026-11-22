#include "common.h"
#include "town/map/animation.h"
#include "town/map.h"

/* Copy the integer part of each 16.16 position component to a projection vertex. */
void copy_position_integer_parts(SVECTOR *destination, const ObjectPosition *source) {
    destination->vx = source->x.w.i;
    destination->vy = source->y.w.i;
    destination->vz = source->z.w.i;
}
