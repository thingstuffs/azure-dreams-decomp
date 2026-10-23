#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* Copy six fields from the source record to the destination. */
void copy_entity_record_fields(ObjectPosition *destination, ObjectPosition *source) {
    destination->x.v = (s32) source->x.v;
    destination->y.v = (s32) source->y.v;
    destination->z.v = (s32) source->z.v;
    destination->velocity_x = (s32) source->velocity_x;
    destination->velocity_y = (s32) source->velocity_y;
    destination->velocity_z = (s32) source->velocity_z;
}
