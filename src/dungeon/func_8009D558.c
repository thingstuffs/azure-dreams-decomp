#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 func_80042900(void *arg0, s32 arg1);


typedef struct S_800A2CB8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_800A2CB8_1;   /* arg1 in func_800A2CB8 */

u32 func_800A2CB8(void *arg0, S_800A2CB8_1 *arg1) {
    if (arg1 == NULL) {
        return 0;
    }
    if (((Rec_D_800E3D7C *)arg0)->unk_1C.as_u32 & 0x410) {
        return 1;
    }
    if (((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v == 0x2B &&
        (((Rec_D_800E3D7C *)arg0)->unk_98 & 0x8000)) {
        return 1;
    }
    if ((arg1->unk_14 & 0x4000) &&
        (((Rec_D_800E3D7C *)arg0)->unk_14.as_u32 & 0x4000)) {
        return ((u16)func_80042900(arg0, 0xC) << 16) != 0;
    }
    return (((((Rec_D_800E3D7C *)arg0)->unk_1C.as_u32 ^
              arg1->unk_1C) & 0x2000) << 16) >> 16;
}
