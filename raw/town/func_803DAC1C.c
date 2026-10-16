#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800182A8();                            /* extern */
extern M2C_UNK D_8001691C;
extern M2C_UNK *D_80019BB8;
extern s32 D_80019BBC;

void func_8001741C(void) {
    func_800182A8();
    D_80019BB8 = &D_8001691C;
    D_80019BBC = M2C_FIELD(*(void **)0x80016000, s32 *, 0x40) + 8;
}
