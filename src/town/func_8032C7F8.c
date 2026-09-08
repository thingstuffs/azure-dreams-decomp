#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 func_8001890C();                                /* extern */
M2C_UNK func_80019C68();             /* extern */
M2C_UNK func_8001ACE8();                         /* extern */
M2C_UNK func_8001AD60();                     /* extern */


void func_80016FF8(Rec_func_800165F4_arg0 *arg0, M2C_UNK arg1) {
    func_8001AD60(0xD52);
    if (func_8001890C() != 0) {
        func_8001ACE8(arg0->unk_18);
    }
    func_80019C68(arg0, arg1);
}
