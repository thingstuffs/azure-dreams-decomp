#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_80082660;
extern M2C_UNK D_800C3BF4;
extern M2C_UNK D_800D675C;
extern M2C_UNK D_800D67AC;
extern M2C_UNK D_800D67B4;
extern M2C_UNK D_800D67DC;
extern M2C_UNK D_800D67E0;

void func_800CACB8(void *arg0, M2C_UNK arg2) {
    *((M2C_FIELD(arg0, s32 *, 0x60) * 8) + &D_80082660) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x58) = &D_800D67DC;
    M2C_FIELD(arg0, M2C_UNK **, 0x5C) = &D_800D67E0;
    M2C_FIELD(arg0, M2C_UNK **, 0x7C) = &D_800D67AC;
    M2C_FIELD(arg0, M2C_UNK **, 0x80) = &D_800D67B4;
    func_800C2E84(arg2, &D_800D675C);
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800C3BF4;
}
