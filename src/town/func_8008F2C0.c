#include "common.h"
#include "m2c_compat.h"

s16 dungeonEvaluateSummedVectorMinusBase();               /* extern */

/* Returns the minimum indexed value, or 0x7FFF if the count is nonpositive. */
s16 townMinIndexedQuery(s32 context, M2C_UNK data, s32 count) {
    s16 value;
    s16 minimum;
    s32 index;

    minimum = 0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = dungeonEvaluateSummedVectorMinusBase(context, data, index);
            if ((value << 0x10) < (minimum << 0x10)) {
                minimum = value;
            }
            index += 1;
        } while (index < count);
    }
    return minimum;
}
