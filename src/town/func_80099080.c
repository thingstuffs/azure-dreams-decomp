#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800954F4(Rec_D_800E3D7C *);                            /* extern */
extern s8 D_800CFCE8;


void func_800967E0(Rec_D_800E3D7C *arg0, s32 arg1) {
    D_800CFCE8 = 1;
    arg0->unk_08.at00_s32.v = arg1;
    arg0->unk_14.as_s32 = 0;
    func_800954F4(arg0);
}
