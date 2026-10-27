#include "common.h"
#include "town/player/coordinates.h"



/* Return zero when result[0] is below 0xF45 and result[1] is at least 0x1127. */
s32 check_position_thresholds(void) {
    s16 result[4];

    copy_current_record_components_3(result);
    if (result[0] < 0xF45) {
        if (result[1] < 0x1127) {
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}
