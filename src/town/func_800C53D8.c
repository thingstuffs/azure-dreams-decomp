#include "common.h"

extern s32 query_lowered_transform_position(void *);

/* Return the signed low halfword of the query result, clamped to at most zero. */
s32 get_clamped_transform_coordinate(void *object) {
    s32 result;

    result = query_lowered_transform_position(object);
    if ((result << 16) > 0) {
        result = 0;
    }
    return (result << 16) >> 16;
}
