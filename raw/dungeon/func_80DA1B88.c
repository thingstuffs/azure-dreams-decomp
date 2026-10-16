#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
s16 func_8009A66C(s16, void *, void *, M2C_UNK);    /* extern */
s16 func_800A0818(u8, u8, u8, u8, s32);             /* extern */
M2C_UNK func_8015FD14(void *, M2C_UNK, void *, void *); /* extern */
extern M2C_UNK D_80161864;

void func_8015F388(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0_2;
    s16 temp_v0_3;
    u8 temp_s0;
    u8 temp_s2;
    u8 temp_v1;
    void *temp_v0;

    if ((M2C_FIELD(arg3, s8 *, 0x71) > 0) && (M2C_FIELD(arg3, s16 *, 0x8A) < (s32) (u8) M2C_FIELD(arg3, s8 *, 0x71))) {
        if (M2C_FIELD(arg2, M2C_UNK **, 0x2C) != &D_80161864) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80161864;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80161864), 0);
        }
        temp_s0 = M2C_FIELD(arg2, u8 *, 0x24);
        temp_s2 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(temp_s0, temp_s2, var_a2);
        temp_v0 = arg3 + M2C_FIELD(arg3, s16 *, 0x8A);
        temp_v0_2 = func_800A0818(temp_s0, temp_s2, M2C_FIELD(temp_v0, u8 *, 0x74), M2C_FIELD(temp_v0, u8 *, 0x7C), arg0 + 0x98);
        temp_v0_3 = func_8009A66C(temp_v0_2, arg2, arg3, 0x20);
        M2C_FIELD(arg2, u8 *, 0x24) = (u8) M2C_FIELD((arg3 + M2C_FIELD(arg3, s16 *, 0x8A)), u8 *, 0x74);
        var_a2_2 = 0x3000;
        M2C_FIELD(arg2, u8 *, 0x25) = (u8) M2C_FIELD((arg3 + M2C_FIELD(arg3, s16 *, 0x8A)), u8 *, 0x7C);
        M2C_FIELD(arg3, s16 *, 0x8A) = (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x8A) + 1);
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2_2 = 0x300;
        }
        func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
        M2C_FIELD(arg3, s16 *, 0x2A) = temp_v0_2;
        if (temp_v0_3 == 3) {
            if (!(*(u16 *)0x80083462 & 0x80) && !(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
                func_8015FD14(arg0, arg1, arg2, arg3);
                M2C_FIELD(arg0, s32 *, 0x8C) = 0;
            } else {
                goto block_13;
            }
        } else {
block_13:
            M2C_FIELD(arg0, s8 *, 0x9A) = 0xF;
            M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        }
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
        if (*(void *)0x80083462 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x96) = 8;
        temp_v1 = (u8) M2C_FIELD(arg3, s8 *, 0x71);
        if ((s32) temp_v1 > 0) {
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) (8 / (s32) temp_v1);
        }
    }
}
