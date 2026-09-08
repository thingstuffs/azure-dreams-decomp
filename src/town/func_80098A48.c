#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80096208(s32);                            /* extern */
M2C_UNK func_800962B8();                         /* extern */

/* Pass the input to func_80096208, then func_800962B8. */
void func_800961A8(s32 input_value) {
    func_80096208(input_value);
    func_800962B8(input_value);
}
