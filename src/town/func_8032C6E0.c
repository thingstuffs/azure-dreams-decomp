#include "common.h"

extern void townCopyCurrentRecordComponents3(s16 *result);


/* Return zero when result[0] is below 0xF45 and result[1] is at least 0x1127. */
s32 townCheckPositionThresholds(void) {
    s16 result[4];

    townCopyCurrentRecordComponents3(result);
    if (result[0] < 0xF45) {
        if (result[1] < 0x1127) {
            return 1;
        }
        goto return_zero;
    }

    return 1;

return_zero:
    return 0;
}
