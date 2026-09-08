#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


/* Store tile coordinates as centered positions in 64-unit tiles. */
void func_800A2B04(Rec_D_800E3D7C *record, s32 tile_x, s32 tile_y) {
    record->unk_00.at02_s16.v = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
    record->unk_04.at02_s16.v = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
}
