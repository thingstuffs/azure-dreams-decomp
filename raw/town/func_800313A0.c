#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800CE38C;
extern M2C_UNK D_800D72D4;

void func_800CEB00(void *arg0, void *arg1, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D72D4);
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800CE38C;
    M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF60000;
}
