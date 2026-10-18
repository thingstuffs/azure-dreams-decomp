#include "common.h"
#include "m2c_compat.h"
void func_800179A0(void);                            /* extern */
extern M2C_UNK D_800190BC;

/* Calls func_800179A0 and returns the address of D_800190BC. */
s32 *func_806974BC(void) {
    func_800179A0();
    return &D_800190BC;
}
