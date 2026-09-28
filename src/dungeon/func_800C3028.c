#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s16 func_800C8DB0();               /* extern */


/* Test whether the target lookup with record-derived parameters is nonnegative. */
u32 func_800C8788(EntityRec *record, M2C_UNK target) {
    u8 scale;

    scale = (*(u8 *)((u8 *)&record->unk_10 + 1));
    return (u32) ~func_800C8DB0(target, scale * 4, (scale >> 2) + 0x10) >> 0x1F;
}
