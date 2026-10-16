#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022FDC(s32);                         /* extern */
extern M2C_UNK D_800261F0;
extern M2C_UNK D_800265B8;

void func_800264D8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x34) = &D_800265B8;
    func_80022FDC(arg0 - 0x20);
    M2C_FIELD(arg0, M2C_UNK **, -0x10) = &D_800261F0;
}
