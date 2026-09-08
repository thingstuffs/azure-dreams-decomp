#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80025850_arg0.h"

M2C_UNK func_80025D9C();       /* extern */
M2C_UNK func_80025E3C();                 /* extern */
M2C_UNK func_80025FFC();                            /* extern */


void func_80026084(void *arg0) {
    func_80025FFC();
    func_80025D9C(arg0, arg0 + 0x44, arg0 + 0x1C, arg0 + 0x2C);
    func_80025E3C(arg0, ((Rec_func_80025850_arg0 *)arg0)->unk_54);
}
