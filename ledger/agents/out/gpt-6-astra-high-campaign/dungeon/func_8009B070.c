#include "common.h"

s16 func_80065F90();              /* extern */

/* Passes the coordinate differences and destination to func_80065F90. */
s16 func_800A07D0(s16 start_x, s16 start_y, s16 end_x, s16 end_y) {
    return func_80065F90(end_y - start_y, end_x - start_x, end_x, end_y);
}
