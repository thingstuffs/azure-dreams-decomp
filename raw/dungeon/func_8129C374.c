#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009E8B4();                            /* extern */
M2C_UNK func_800A569C(M2C_UNK);                     /* extern */

void func_80154B74(void) {
    *(s32 *)0x800E1D4C &= 0xEFFFFFFF;
    func_800A569C(0xEFFFFFFF);
    *(u16 *)0x80013714 &= 0xFFF6;
    func_8009E8B4();
}
