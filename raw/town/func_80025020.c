#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F074(s32);                         /* extern */
extern M2C_UNK D_800C27DC;
extern M2C_UNK D_800D4F88;

void func_800C2780(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x8C) = 0x40;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0x40;
    func_8008F074(*((M2C_FIELD(arg0, u8 *, 0x94) * 4) + &D_800D4F88));
    M2C_FIELD(arg0, M2C_UNK **, 0x50) = &D_800C27DC;
}
