#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

M2C_UNK func_80019B54();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
s32 func_8001ADE0();                         /* extern */


void func_8001762C(Rec_func_800165F4_arg0 *arg0, M2C_UNK arg1) {
    if ((func_8001ADE0(0x1388) != 0) || (func_8001ADE0(0x138A) != 0)) {
        func_8001ACE8(arg0->unk_18);
    }
    func_80019B54(arg0, arg1);
}
