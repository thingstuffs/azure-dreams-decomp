#include "common.h"
#include "shared/vector.h"
#include "town/person/position.h"

extern s16 find_min_qualifying_plane_height_at(); /* Unprototyped: two or three arguments; the third register argument is ignored. */

typedef struct {
    IntVector3 coordinates;
    s32 reserved[3];
} HeightProbe;

/* Queries the position after lowering its third coordinate by eight fixed-point units. */
s16 query_lowered_transform_position(void *position) {
    const IntVector3 *coordinates = position;
    HeightProbe adjusted_position;
    long long result_storage;
    long long *result_ptr;

    adjusted_position.coordinates.x = coordinates->x;
    adjusted_position.coordinates.y = coordinates->y;
    result_ptr = &result_storage;
    adjusted_position.coordinates.z = coordinates->z + 0xFFF80000;
    return find_min_qualifying_plane_height_at(&adjusted_position, &result_ptr);
}

/* MECHANISM: A 24-byte escaped record plus an 8-byte pointee force the retail 0x40 frame.
   Copying both leading fields before linking sp30 to sp28 delays that address live range,
   reproducing the exact prologue, stack-store order, callee ABI setup, and s16 return. */
