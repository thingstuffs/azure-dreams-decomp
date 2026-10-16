#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009FAC4();                            /* extern */
M2C_UNK func_800A69E4(M2C_UNK);                     /* extern */

void func_8014FB74(void) {
    *(s32 *)0x800E296C &= 0xEFFFFFFF;
    func_800A69E4(0xEFFFFFFF);
    *(u16 *)0x80013714 &= 0xFFF6;
    func_8009FAC4();
}
