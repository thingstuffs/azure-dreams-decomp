#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_80082660;
extern M2C_UNK D_800C3BF4;
extern M2C_UNK D_800D6734;
extern M2C_UNK D_800D6770;
extern M2C_UNK D_800D6778;
extern M2C_UNK D_800D67A0;
extern M2C_UNK D_800D67A4;

void func_800CAD40(void *arg0, M2C_UNK arg2) {
    *((M2C_FIELD(arg0, s32 *, 0x60) * 8) + &D_80082660) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x58) = &D_800D67A0;
    M2C_FIELD(arg0, M2C_UNK **, 0x5C) = &D_800D67A4;
    M2C_FIELD(arg0, M2C_UNK **, 0x7C) = &D_800D6770;
    M2C_FIELD(arg0, M2C_UNK **, 0x80) = &D_800D6778;
    func_800C2E84(arg2, &D_800D6734);
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800C3BF4;
}
