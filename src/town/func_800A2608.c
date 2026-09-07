#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80041E28();              /* extern */
M2C_UNK func_800422DC();              /* extern */
M2C_UNK func_800AB9A0();                   /* extern */
extern M2C_UNK D_80100A10;

void func_8009FD68(s32 arg0) {
    func_80041E28(&D_80100A10, arg0);
    func_800AB9A0(&D_80100A10);
    func_800422DC(arg0, &D_80100A10);
}
