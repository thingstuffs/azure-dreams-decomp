#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK func_800C58F4(s32, M2C_UNK, M2C_UNK);       /* extern */
extern M2C_UNK D_800D557C;

void func_800C5F14(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D557C);
    func_800C58F4(arg0, arg1, arg2);
}
