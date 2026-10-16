#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK, M2C_UNK);              /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, s32);      /* extern */
M2C_UNK *func_8004A658(u8, u8);                     /* extern */
M2C_UNK func_800A56E0(M2C_UNK, s32);                /* extern */
M2C_UNK func_800AD058(void *, void *, void *, void *); /* extern */
M2C_UNK func_800BC26C(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_8015B770;

void func_8015B90C(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK *var_v0;
    s32 temp_a2;
    u8 temp_v1;
    void *temp_s1;
    void *temp_s5;
    void *temp_v0;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {                              /* irregular */
    case 0:
        if (*(s16 *)0x8008346A == 0) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 1U;
        case 1:
            if (M2C_FIELD(arg3, u8 *, 0x49) != 0) {
                temp_v0 = func_8003FC64(0x12, 0x800000);
                if (temp_v0 != NULL) {
                    temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
                    temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
                    M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
                    M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
                    temp_a2 = M2C_FIELD(arg1, s32 *, 8);
                    M2C_FIELD(temp_v1_2, s32 *, 0x10) = 0;
                    M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0;
                    M2C_FIELD(temp_v1_2, s32 *, 0x14) = 0xFFEE0000;
                    M2C_FIELD(temp_v1_2, s32 *, 8) = temp_a2;
                    func_8004491C(temp_v0, &D_80045340, temp_a2);
                    M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
                    temp_s5 = temp_v0 + 0x20;
                    M2C_FIELD(temp_s1, s16 *, 0x1E) = 0xC90;
                    M2C_FIELD(temp_s1, s16 *, 0x1C) = 0xC90;
                    if (M2C_FIELD(arg3, u8 *, 0x49) == 0x12) {
                        var_v0 = &D_8006E240;
                    } else {
                        var_v0 = func_8004A658(M2C_FIELD(arg3, u8 *, 0x49), M2C_FIELD(arg3, u8 *, 0x48));
                    }
                    M2C_FIELD(temp_s1, M2C_UNK **, 8) = var_v0;
                    M2C_FIELD(temp_s5, s16 *, 0xA8) = (s16) M2C_FIELD(arg2, u8 *, 0x24);
                    M2C_FIELD(temp_s5, s16 *, 0xAA) = (s16) M2C_FIELD(arg2, u8 *, 0x25);
                    M2C_FIELD(temp_s5, M2C_UNK *, 0x48) = M2C_UNALIGNED32(M2C_FIELD(arg3, u8 *, 0x48));
                    func_800BC26C(temp_v0, 0, 0, 0);
                    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8015B770;
                }
                M2C_FIELD(arg3, u8 *, 0x48) = 0U;
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
        func_800AD058(arg0, arg1, arg2, arg3);
        break;
    }
}
