#include "common.h"
#include "m2c_compat.h"

void *func_8003F958(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_800444B8(void *, M2C_UNK *, void *, void *); /* extern */
M2C_UNK func_80047320(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_80044EDC;
extern M2C_UNK D_800871C8;
extern M2C_UNK D_80157D44;
extern M2C_UNK D_8015AEB4;

void func_80157E18(void *arg1, void *arg2, void *arg3) {
    s32 temp_t0;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *var_a2;
    void *var_a3;

    temp_v0 = func_8003F958(0x112, &D_800871C8);
    var_a2 = arg2;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x96) = 7;
        M2C_FIELD(temp_v1, s16 *, 0xA8) = 7;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80157D44;
        M2C_FIELD(temp_v1, void **, 0xAC) = arg1;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_t0 = var_a2 + 0x30;
        var_a3 = temp_s0;
        do {
            M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
            M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
            M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
            M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != temp_t0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0x50;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0x50;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0x50;
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0xFF80;
        M2C_FIELD(temp_s0, s16 *, 0x22) = 0xFFF1;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        func_800444B8(temp_v0, &D_80044EDC, var_a2, var_a3);
        M2C_FIELD(temp_s0, M2C_UNK **, 0x2C) = &D_8015AEB4;
        func_80047320(temp_s0, *((((s32) (*(s16 *)0x800848E0 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015AEB4), 0);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1_2, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    }
}
