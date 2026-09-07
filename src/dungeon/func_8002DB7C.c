#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800CB04C(void *, M2C_UNK, M2C_UNK);                            /* extern */


void func_800CB2DC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = arg0->unk_6C.as_u16 - 1;
    arg0->unk_6C.as_u16 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800CB04C(arg0, arg1, arg2);
        func_800C4174(arg0, arg1, arg2);
    }
}
