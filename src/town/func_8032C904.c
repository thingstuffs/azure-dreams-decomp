#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019DFC(); /* extern */
M2C_UNK func_8001ACE8();                     /* extern */
extern M2C_UNK D_8001BB44;
extern M2C_UNK D_8001C358;

void func_80017104(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8001ACE8(0x145C);
    func_80019DFC(&D_8001BB44, &D_8001C358, arg0, arg2);
}
