#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008B5D8();                /* extern */
extern s32 D_800CFBA0[];

/* Submit the indexed table value with code 0x23. */
void func_8008B620(s32 entry_index) {
    func_8008B5D8(D_800CFBA0[entry_index], 0x23);
}
