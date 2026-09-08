#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Dispatches command 0x13 with the supplied argument and two zero arguments. */
void func_8002316C(s32 command_arg) {
    s32 zero = 0;
    func_80022D60(command_arg, 0x13, zero, zero);
}
