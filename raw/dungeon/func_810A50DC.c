#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_80083160;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80152E94;
extern M2C_UNK D_80157F10;
extern M2C_UNK D_80157F28;

void func_801568DC(void *arg0, void *arg2, void *arg3) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F28;
            func_80047784(arg2, *((((s32) (M2C_FIELD(&D_80083160, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F28), 0);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        return;
    case 1:
        if (!(M2C_FIELD(&D_80083160, s32 *, 8) & 0x100) && (M2C_FIELD(&D_80083160, s32 *, 8) & 0xFFFF)) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80157F10;
            func_80047784(arg2, *((((s32) (M2C_FIELD(&D_80083160, s16 *, 0xC8) + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80157F10), 0);
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80152E94;
            M2C_FIELD(arg0, s16 *, 0xA6) = 0;
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
        }
        break;
    }
}
