#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80044A50(void *);                      /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_800BC318(void *);                      /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80164F74;

void func_80167BB8(void *arg0, void *arg2, void *arg3) {
    u8 temp_v0;
    void *temp_s0;

    if (M2C_FIELD(arg0, u8 *, 0x9B) == 0) {
        temp_v0 = M2C_FIELD(arg2, u8 *, 0xC) - 0x10;
        M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            temp_s0 = arg0 - 0x20;
            func_80044A50(temp_s0);
            func_800BC318(temp_s0);
            func_800AD594(arg3, 0x800);
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            M2C_FIELD(arg2, u8 *, 0xC) = 0;
            M2C_FIELD(arg3, s8 *, 0x6D) = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80164F74;
        }
    }
}
