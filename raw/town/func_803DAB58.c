#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018FC8(s32 *, M2C_UNK *, s32, M2C_UNK); /* extern */
extern M2C_UNK D_800170D0;
extern M2C_UNK D_80017124;

void func_80017358(s32 arg0, M2C_UNK arg2) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;

    sp10 = M2C_FIELD(&D_80017124, s32 *, 0);
    sp14 = M2C_FIELD(&D_80017124, s32 *, 4);
    sp18 = M2C_FIELD(&D_80017124, s32 *, 8);
    sp1C = M2C_FIELD(&D_80017124, s32 *, 0xC);
    func_80018FC8(&sp10, &D_800170D0, arg0, arg2);
}
