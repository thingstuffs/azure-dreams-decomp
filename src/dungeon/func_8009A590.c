#include "common.h"

/* Returns the Chebyshev distance between two byte-sized coordinate pairs. */
s16 set_item_w0(s32 start_x, s32 start_y, s32 end_x, s32 end_y) {
    end_x &= 0xFF;
    start_x &= 0xFF;
    end_x -= start_x;
    if (end_x < 0) {
        end_x = -end_x;
    }
    end_y &= 0xFF;
    start_y &= 0xFF;
    end_y -= start_y;
    if (end_y < 0) {
        end_y = -end_y;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (end_x < end_y) {
        return end_y;
    }
    return end_x;
}
