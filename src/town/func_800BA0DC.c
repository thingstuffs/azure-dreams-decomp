#include "common.h"
#include "m2c_compat.h"

void func_800B7428(s16 x, s16 y, u16 *src_tiles);                    /* extern */

/* Forwards tilemap coordinates to the tile copy routine. */
void func_800B783C(s16 x, s16 y, u16 *src_tiles) {
    func_800B7428(x, y, src_tiles);
}
