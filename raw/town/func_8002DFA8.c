#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800D69DC;
extern M2C_UNK D_800D69E4;
extern M2C_UNK D_800D6A0C;
extern M2C_UNK D_800D6A10;

void func_800CB708(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x58) = &D_800D6A0C;
    M2C_FIELD(arg0, M2C_UNK **, 0x5C) = &D_800D6A10;
    M2C_FIELD(arg0, M2C_UNK **, 0x7C) = &D_800D69DC;
    M2C_FIELD(arg0, M2C_UNK **, 0x80) = &D_800D69E4;
}
