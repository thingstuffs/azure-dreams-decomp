#include "common.h"

extern s32 townQueryLoweredTransformPosition(void *);

/* Return the signed low halfword of the query result, clamped to at most zero. */
s32 townGetClampedTransformCoordinate(void *object) {
    s32 result;

    result = townQueryLoweredTransformPosition(object);
    if ((result << 16) > 0) {
        result = 0;
    }
    return (result << 16) >> 16;
}
