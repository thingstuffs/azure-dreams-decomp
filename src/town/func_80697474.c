#include "common.h"
#include "m2c_compat.h"
void func_800179A0(void);                            /* extern */
extern M2C_UNK D_80018F44;

/* Calls func_800179A0 and returns the address of D_80018F44. */
s32 *func_80697474(void) {
    func_800179A0();
    return &D_80018F44;
}
