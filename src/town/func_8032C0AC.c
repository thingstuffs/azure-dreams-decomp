#include "common.h"
#include "m2c_compat.h"

void func_80019B54(s32, s32);             /* extern */
void func_80019BC0(void);                 /* extern */
s32 func_8001B0C8(void);                  /* extern */

void func_800168AC(s32 arg0, M2C_UNK arg1) {
    if (func_8001B0C8() >= 0xF) {
        func_80019BC0();
    }
    func_80019B54(arg0, arg1);
}
