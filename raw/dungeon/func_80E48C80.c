#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, M2C_UNK, M2C_UNK);    /* extern */
s32 func_80069EF8();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8016A3D0;

void func_8016A480(void *arg0, void *arg1) {
    s32 var_s2;
    void *temp_a0;
    void *temp_s0;
    void *temp_v0;

    var_s2 = 0x10;
    do {
        temp_v0 = func_8003FC64(0x300);
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016A3D0;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x800;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x800;
            M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
            M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
            M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (M2C_FIELD(arg1, u16 *, 0x12) - 0x80);
            func_80047784(temp_a0, 0x41, 0);
            temp_s0 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 2);
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(arg0, u16 *, 6);
            M2C_FIELD(temp_s0, s16 *, 0xA) = (s16) (M2C_FIELD(arg0, u16 *, 0xA) - (func_80069EF8() & 0x1F));
            M2C_FIELD(temp_s0, s16 *, 0x16) = (s16) ((-(func_80069EF8() & 0xF) - 8) * 2);
            M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (((func_80069EF8() & 3) - 2) << 0x10);
            M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (((func_80069EF8() & 3) - 2) << 0x10);
            M2C_FIELD(temp_v0, s16 *, 0x40) = 0x10;
        }
        var_s2 -= 1;
    } while (var_s2 > 0);
}
