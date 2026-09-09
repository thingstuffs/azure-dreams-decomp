#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027AD0_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80028050();       /* extern */
M2C_UNK func_800280FC();                 /* extern */
M2C_UNK func_80028210(void *, s32, s32, s32);                            /* extern */


void func_8002823C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80028210(arg0, arg1, arg2, arg3);
    func_80028050(arg0, arg0 + 0x78, arg0 + 0x50, arg0 + 0x60);
    func_800280FC(arg0, ((Rec_func_80027AD0_arg0 *)arg0)->unk_88);
}
