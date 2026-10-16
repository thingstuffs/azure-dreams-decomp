#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80150158;

void func_8014DEFC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_s0;
    s32 temp_s0_2;

    M2C_FIELD(arg0, s8 *, 0x9A) = 0x10;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80150158;
    temp_s0 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7;
    func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80150158), 0);
    temp_s0_2 = temp_s0 * 2;
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) - (*(temp_s0_2 + &D_8006CCD8) << 0x13));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) - (*(temp_s0_2 + &D_8006CCE8) << 0x13));
}
