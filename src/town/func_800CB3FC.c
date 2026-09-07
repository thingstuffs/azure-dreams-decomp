#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082D58.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800C8BB4;
extern M2C_UNK D_800D6374;



void func_800C8B5C(Rec_D_80082D58 *arg0, Rec_D_800E3D7C *arg1) {
    arg1->unk_14.as_s32 = (s32) *(M2C_UNK *)((u8 *)&D_800D6374 + ((arg0->unk_90.as_s16) * 4));
    arg0->unk_50.as_pm = &D_800C8BB4;
}
