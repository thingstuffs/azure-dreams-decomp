#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800CDADC;
extern M2C_UNK D_800D72E8;

void func_800CDF54(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D72E8);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800CDADC;
}
