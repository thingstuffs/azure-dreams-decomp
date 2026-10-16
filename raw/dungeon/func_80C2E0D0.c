#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
s16 func_800A0818(u8, u8, u8, u8, void *);          /* extern */
extern M2C_UNK D_8015C494;
extern M2C_UNK D_8015C49C;

void func_801598D0(void *arg0, void *arg2, void *arg3) {
    M2C_UNK *temp_v1;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    u8 temp_a3;
    u8 temp_s3;
    u8 temp_s4;

    if ((M2C_FIELD(arg3, s8 *, 0x71) > 0) && (M2C_FIELD(arg3, s16 *, 0x8A) < (s32) (u8) M2C_FIELD(arg3, s8 *, 0x71))) {
        temp_v1 = M2C_FIELD(arg2, M2C_UNK **, 0x2C);
        if ((temp_v1 != &D_8015C494) && (temp_v1 != &D_8015C49C)) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015C49C;
            func_80047784(arg2, *((((s32) (*(s16 *)0x80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015C49C), 0);
            M2C_FIELD(arg0, s16 *, 0xA8) = 0;
        }
        temp_s3 = M2C_FIELD(arg2, u8 *, 0x24);
        temp_s4 = M2C_FIELD(arg2, u8 *, 0x25);
        var_a2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(temp_s3, temp_s4, var_a2);
        M2C_FIELD(arg2, u8 *, 0x24) = (u8) M2C_FIELD((arg3 + M2C_FIELD(arg3, s16 *, 0x8A)), u8 *, 0x74);
        M2C_FIELD(arg2, u8 *, 0x25) = (u8) M2C_FIELD((arg3 + M2C_FIELD(arg3, s16 *, 0x8A)), u8 *, 0x7C);
        M2C_FIELD(arg3, s16 *, 0x8A) = (s16) ((u16) M2C_FIELD(arg3, s16 *, 0x8A) + 1);
        var_a2_2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2_2 = 0x300;
        }
        func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(temp_s3, temp_s4, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), arg0 + 0x98);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
        M2C_FIELD(arg0, s8 *, 0x9A) = 0xF;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        if (*(u16 *)0x80083462 & 0x80) {
            M2C_FIELD(arg0, s16 *, 0x96) = 0;
            return;
        }
        M2C_FIELD(arg0, s16 *, 0x96) = 8;
        temp_a3 = (u8) M2C_FIELD(arg3, s8 *, 0x71);
        if ((s32) temp_a3 > 0) {
            M2C_FIELD(arg0, s16 *, 0x96) = (s16) (8 / (s32) temp_a3);
        }
    }
}
