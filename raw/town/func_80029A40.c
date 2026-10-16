#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_80082660;
extern M2C_UNK D_800C7138;
extern M2C_UNK D_800D5CAC;

void func_800C71A0(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D5CAC);
    *((M2C_FIELD(arg0, s32 *, 0x60) * 8) + &D_80082660) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800C7138;
}
