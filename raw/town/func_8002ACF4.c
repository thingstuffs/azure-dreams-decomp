#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C3050(M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, M2C_UNK *); /* extern */
extern M2C_UNK D_800D6220;
extern M2C_UNK D_800D62D8;
extern M2C_UNK D_800D62E0;
extern M2C_UNK D_800D6308;
extern M2C_UNK D_800D630C;

void func_800C8454(void *arg0) {
    func_800C3050(0xA, &D_800D6308, &D_800D630C, &D_800D62D8, &D_800D62E0);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x80), M2C_UNK **, 4) = &D_800D6220;
}
