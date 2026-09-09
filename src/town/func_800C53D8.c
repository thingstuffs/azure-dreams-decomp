#include "common.h"

extern s32 func_800C2AE8(void *);

/* Return the signed low halfword of the query result, clamped to at most zero. */
s32 func_800C2B38(void *object) {
    s32 result;

    result = func_800C2AE8(object);
    if ((result << 16) > 0) {
        result = 0;
    }
    return (result << 16) >> 16;
}
