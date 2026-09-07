#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016104();     /* extern */
M2C_UNK func_80018ADC();                     /* extern */
extern M2C_UNK D_80018E48;

void func_80016A20(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_80018ADC(0x5BE);
    func_80016104(&D_80018E48, arg0, arg2);
}
