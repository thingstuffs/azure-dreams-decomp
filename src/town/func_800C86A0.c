#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
M2C_UNK func_800C58F4();       /* extern */
extern M2C_UNK D_800D5540;

void func_800C5E00(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D5540);
    func_800C58F4(arg0, arg1, arg2);
}
