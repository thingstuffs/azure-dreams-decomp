#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800954C4();                            /* extern */
extern s8 D_800CFCEA;


void func_800966F8(Rec_D_800E3D7C *arg0, s32 arg1) {
    D_800CFCEA = 1;
    arg0->unk_00.at00_s32.v = arg1;
    arg0->unk_0C.as_s32 = 0;
    func_800954C4();
}
