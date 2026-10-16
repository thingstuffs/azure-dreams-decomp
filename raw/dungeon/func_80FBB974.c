#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */

void func_8016F174(void *arg0, void *arg2) {
    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
