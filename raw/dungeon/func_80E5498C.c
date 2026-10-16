#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_80042640(void *, u8);                  /* extern */
M2C_UNK func_80042710(void *, void *);              /* extern */
M2C_UNK func_8004397C(s32);                         /* extern */
void *(*func_800A0B94(u8, void *, M2C_UNK))(M2C_UNK, u8, u8, s16); /* extern */
void *func_800A1618(u8, M2C_UNK);                   /* extern */
s32 func_800A1BD0(void *);                          /* extern */
s32 func_800A7A38(void *);                          /* extern */
void *func_800B23F8(s32, u8, u8, s16, s32);         /* extern */
extern M2C_UNK D_800E3548;

void *func_8015E18C(void *arg2, void *arg3) {
    M2C_UNK var_a0;
    s32 temp_a0;
    void *(*temp_s0)(M2C_UNK, u8, u8, s16);
    void *temp_v0;
    void *temp_v1;
    void *var_s0;
    void *var_s0_2;
    void *var_v0;

    temp_a0 = M2C_FIELD(arg3, s32 *, 0x60);
    if (temp_a0 > 0) {
        var_s0 = func_800B23F8(((u32) M2C_FIELD(arg3, u32 *, 0x1C) >> 0xD) & 1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x88), func_800A7A38(((s32) (((u16) M2C_FIELD(arg3, s32 *, 0x60) - 1) << 0x10) >> 0xE) + &D_800E3548));
        if (var_s0 != NULL) {
            M2C_FIELD(var_s0, s32 *, 0x14) = 0;
            M2C_FIELD(var_s0, s32 *, 0x1C) = 0;
            func_80042710(var_s0, arg3);
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x20000000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) ((M2C_FIELD(var_s0, s32 *, 0x1C) | 0x02000200) & 0xFFFEFFFF);
        }
        goto block_10;
    }
    *(s8 *)0x800E2968 = 1;
    var_s0_2 = func_800A1618(M2C_FIELD(temp_a0, u8 *, 0x13), 1);
    if (((var_s0_2 != NULL) && (M2C_FIELD(var_s0_2, u8 *, 1) != 0)) || (var_s0_2 = func_800A1618(M2C_FIELD(temp_a0, u8 *, 0x13), 3), var_v0 = NULL, (var_s0_2 != NULL))) {
        func_8004397C(temp_a0);
        temp_s0 = func_800A0B94(M2C_FIELD(temp_a0, u8 *, 0x13), var_s0_2, 1);
        func_8003F320();
        var_a0 = 4;
        if (M2C_FIELD(arg3, u32 *, 0x1C) & 0x2000) {
            var_a0 = 7;
        }
        var_s0 = temp_s0(var_a0, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), M2C_FIELD(arg3, s16 *, 0x88));
        if (var_s0 != NULL) {
            func_80042640(var_s0, M2C_FIELD(var_s0, u8 *, 0x13));
            M2C_FIELD(var_s0, s32 *, 0x14) = 0;
            M2C_FIELD(var_s0, s32 *, 0x1C) = 0;
            func_80042710(var_s0, arg3);
            M2C_FIELD(var_s0, u8 *, 0x28) = (u8) (M2C_FIELD(var_s0, u8 *, 0x28) + 1);
            M2C_FIELD(var_s0, u8 *, 0x13) = (u8) M2C_FIELD(temp_a0, u8 *, 0x13);
            M2C_FIELD(M2C_FIELD(var_s0, void **, -0x14), s16 *, 0x12) = (s16) (M2C_FIELD(M2C_FIELD(temp_a0, void **, -0x14), u16 *, 0x12) & 3);
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x20000000);
            M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) ((M2C_FIELD(var_s0, s32 *, 0x1C) | 0x02000000) & 0xFFFEFFFF);
        }
block_10:
        if (M2C_FIELD(arg3, s32 *, 0x14) & 0x4000) {
            temp_v0 = ((s32) (func_800A1BD0(arg3) << 0x10) >> 0xE) + *(s32 *)0x800E3D7C;
            temp_v1 = M2C_FIELD(temp_v0, void **, 0xAC);
            M2C_FIELD(temp_v0, void **, 0xAC) = var_s0;
            M2C_FIELD(temp_v0, void **, 0xE4) = temp_v1;
        }
        var_v0 = NULL;
        if (var_s0 != NULL) {
            var_v0 = var_s0 - 0x20;
        }
    }
    return var_v0;
}
