#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388(void *);                      /* extern */
M2C_UNK func_800C2E84(void *, M2C_UNK, M2C_UNK *);  /* extern */
extern M2C_UNK D_800CE800;
extern M2C_UNK D_800D72E8;

void func_800CE8CC(void *arg0, void *arg1, M2C_UNK arg2) {
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    func_80095388(arg1);
    if (M2C_FIELD(arg1, s32 *, 0x14) >= 0) {
        func_800C2E84(arg0, arg2, &D_800D72E8);
        M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800CE800;
    }
}
