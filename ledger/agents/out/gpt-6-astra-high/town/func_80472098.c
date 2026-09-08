#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018FDC(s32, s32);             /* extern */

/* Calls func_80018FDC with the supplied value and a zero second argument. */
void func_80472098(s32 value) {
    func_80018FDC(value, 0);
}
