#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800181C8();
M2C_UNK func_80018B58();
s32 func_80018C50();
extern M2C_UNK D_80018EF4;
extern M2C_UNK D_80018F0C;
extern M2C_UNK D_8001925C;

void func_80016800(s32 arg0, s32 unused, M2C_UNK arg2) {
    register void *arg ASM_REG("$4");   /* MATCH pin: retail immediate-load split depends on it */

    func_80018B58(0xFE2);
    if (func_80018C50(0xFB1) == 0) {
        arg = &D_80018EF4;
    } else {
        arg = &D_80018F0C;
    }
    func_800181C8(arg, &D_8001925C, arg0, arg2);
}
