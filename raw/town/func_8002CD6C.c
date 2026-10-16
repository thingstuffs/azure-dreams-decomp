#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800C9F1C;
extern M2C_UNK D_800D652C;

void func_800CA4CC(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D652C);
    *(s8 *)0x800826B8 = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800C9F1C;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0x15;
}
