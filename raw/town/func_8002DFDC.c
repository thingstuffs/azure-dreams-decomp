#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D6988;
extern M2C_UNK D_800D6990;
extern M2C_UNK D_800D69B8;
extern M2C_UNK D_800D69BC;

void func_800CB73C(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x58) = &D_800D69B8;
    M2C_FIELD(arg0, M2C_UNK **, 0x5C) = &D_800D69BC;
    M2C_FIELD(arg0, M2C_UNK **, 0x7C) = &D_800D6988;
    M2C_FIELD(arg0, M2C_UNK **, 0x80) = &D_800D6990;
}
