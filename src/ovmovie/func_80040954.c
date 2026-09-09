#include "common.h"
#include "m2c_compat.h"

M2C_UNK Control_CD();       /* extern */
M2C_UNK func_8003F320();                            /* extern */
s32 func_80061350();                                /* extern */
s32 func_80063424();                         /* extern */

/* Start operation 0x15 and wait for the 0x1C0 completion check. */
void func_80040954(void) {
    Control_CD(0x15, func_80061350(), 0);
    func_8003F320();
    do {

    } while (func_80063424(0x1C0) == 0);
}
