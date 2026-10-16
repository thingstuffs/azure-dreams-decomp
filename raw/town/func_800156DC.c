#include "common.h"
#include "m2c_compat.h"

void func_800B2E3C(void *arg0) {
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), void **, 0x10), void **, 4), s16 *, 8) = (s16) ((((M2C_FIELD(temp_v0, s32 *, 0x24) % 10) / 5) << 7) - 0x38);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), void **, 0x10), void **, 4), s16 *, 0xA) = (s16) ((((M2C_FIELD(temp_v0, s32 *, 0x24) % 10) % 5) * 0x10) + 8);
    temp_v1 = M2C_FIELD(arg0, void **, 0xA8);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x14), void **, 4), s16 *, 8) = (s16) (M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1, void **, 0x10), void **, 4), u16 *, 8) + 0x38);
    temp_v1_2 = M2C_FIELD(arg0, void **, 0xA8);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1_2, void **, 0x14), void **, 4), s16 *, 0xA) = (s16) (M2C_FIELD(M2C_FIELD(M2C_FIELD(temp_v1_2, void **, 0x10), void **, 4), u16 *, 0xA) - 9);
}
