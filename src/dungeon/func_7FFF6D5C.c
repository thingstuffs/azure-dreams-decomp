#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80094984();  /* extern */
extern M2C_UNK D_80092698;
extern M2C_UNK D_800D0120;


void func_800944BC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80053DA8(0x511);
    func_80094984(&D_800D0120, arg0, arg2);
    arg0->unk_00.as_pm = &D_80092698;
    arg0->unk_0A.as_s16 = 6;
}
