#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s16 func_800C8DB0();               /* extern */


/* Test whether the target lookup with record-derived parameters is nonnegative. */
u32 func_800C8788(Rec_D_800E3D7C *record, M2C_UNK target) {
    u8 scale;

    scale = record->unk_10.at01_u8.v;
    return (u32) ~func_800C8DB0(target, scale * 4, (scale >> 2) + 0x10) >> 0x1F;
}
