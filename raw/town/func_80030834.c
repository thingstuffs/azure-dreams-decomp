#include "common.h"
#include "m2c_compat.h"

s32 func_800374F4(M2C_UNK);                         /* extern */
M2C_UNK func_800C2E84(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_800CDBB8;
extern M2C_UNK D_800D7284;

void func_800CDF94(void *arg0, M2C_UNK arg2) {
    func_800C2E84(arg2, &D_800D7284);
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800CDBB8;
    M2C_FIELD(arg0, s16 *, 0x6C) = (s16) (((func_800374F4(4) & 0xFFFF) * 0x15) + 0x15);
}
