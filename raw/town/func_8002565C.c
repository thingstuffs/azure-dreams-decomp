#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2CB0(void *, void *, s32, M2C_UNK); /* extern */
s32 func_800C2D94(s16);                             /* extern */

void func_800C2DBC(void *arg0, void *arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x78) = arg2;
    func_800C2CB0(arg0, arg1, *((func_800C2D94(M2C_FIELD(arg0, s16 *, 0x72)) * 4) + M2C_FIELD(arg0, s32 *, 0x78)), 0);
    M2C_FIELD(arg1, s8 *, 5) = 0;
}
