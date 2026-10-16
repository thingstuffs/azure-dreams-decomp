#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *);                      /* extern */
extern s32 D_800814A0;

void func_80024374(void *arg0, void *arg2) {
    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
