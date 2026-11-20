#include "common.h"
#include "shared/entity.h"
#include "town/person/position.h"

/* Return the queried height, clamped to at most zero. */
s32 get_clamped_transform_coordinate(ObjectPosition *object) {
    s16 result;

    result = query_lowered_transform_position(object);
    if (result > 0) {
        result = 0;
    }
    return result;
}
