#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B2DA0_arg1.h"

M2C_UNK func_800B2DA0();                 /* extern */
M2C_UNK func_800B30D8();                            /* extern */
M2C_UNK func_800B32D4();                      /* extern */
M2C_UNK func_800B336C();                      /* extern */


void func_800B3440(Rec_func_800B2DA0_arg1 *arg0) {
    func_800B30D8();
    func_800B336C(arg0);
    func_800B32D4(arg0);
    func_800B2DA0(arg0->unk_A8 + 0x68, arg0);
}
