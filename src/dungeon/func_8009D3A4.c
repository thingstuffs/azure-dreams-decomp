#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


/* Store tile coordinates as centered positions in 64-unit tiles. */
void func_800A2B04(EntityRec *record, s32 tile_x, s32 tile_y) {
    record->x.w.i = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
    record->y.w.i = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
}
