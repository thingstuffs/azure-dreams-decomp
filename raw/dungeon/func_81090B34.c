#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80169F20;

void func_80166334(void *arg0, void *arg2, void *arg3) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0xA6) + 1;
    M2C_FIELD(arg0, u16 *, 0xA6) = temp_v0;
    if ((u32) (temp_v0 & 0xFFFF) >= 0x3DU) {
        M2C_FIELD(arg0, u16 *, 0xA6) = 0x3CU;
        M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) + 1);
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80169F20;
        func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80169F20), 0);
    }
}
