#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A56E0(M2C_UNK, M2C_UNK);            /* extern */
M2C_UNK func_800AD058(void *, void *, void *);      /* extern */
M2C_UNK func_8016ED48(M2C_UNK, void *, void *);     /* extern */

void func_8016D6EC(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (*(s16 *)0x8008346A == 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 1U;
        case 1:
            if (M2C_FIELD(arg3, u8 *, 0x49) != 0) {
                func_8016ED48(arg1, arg2, arg3);
                M2C_FIELD(arg3, s8 *, 0x48) = 0;
                M2C_FIELD(arg3, u8 *, 0x49) = 0U;
            }
            M2C_FIELD(arg2, s16 *, 0x10) = 0x20;
            M2C_FIELD(arg2, u16 *, 0x12) = (u16) (M2C_FIELD(arg2, u16 *, 0x12) - 0x80);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
            M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
            M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            func_800A56E0(0x805, 0x808080);
            return;
        }
        return;
    case 2:
        func_800AD058(arg0, arg2, arg3);
        break;
    }
}
