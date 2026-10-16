#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001E660(void *, void *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
s32 func_8009A350(s32, u8, M2C_UNK, u16 *);         /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A6DA4(M2C_UNK, s32);                    /* extern */
extern M2C_UNK D_800E3549;
extern M2C_UNK D_800E36C8;

void func_8001D328(void *arg0) {
    u16 sp10;
    s16 temp_v1;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s2;
    s32 var_v0;
    void *var_s1;
    void *var_s3;
    void *var_s4;

    temp_v1 = ((s32) (M2C_FIELD(arg0, u16 *, 6) * M2C_FIELD(arg0, u16 *, 4)) >> 6) + (func_800A6D30() & 7) + 4;
    var_v0 = temp_v1 << 0x10;
    if (temp_v1 >= 0x3D) {
        var_v0 = 0x3C << 0x10;
    }
    var_s2 = var_v0 >> 0x10;
    if (var_s2 >= 0) {
        temp_v1_2 = var_s2 * 4;
        var_s4 = temp_v1_2 + (&D_800E3549 - 1);
        var_s3 = temp_v1_2 + &D_800E3549;
        var_s1 = (var_s2 * 0xC) + &D_800E36C8;
        do {
            temp_s0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 4) - 1) & 0xFFFF) & 0xFFFF;
            temp_v0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 6) - 1) & 0xFFFF) & 0xFFFF;
            M2C_FIELD(var_s1, u8 *, 0) = (u8) (M2C_FIELD(arg0, u8 *, 0) + temp_s0);
            M2C_FIELD(var_s1, u8 *, 1) = (u8) (M2C_FIELD(arg0, u8 *, 2) + temp_v0);
            if (((func_8009A350(M2C_FIELD(var_s1, u8 *, 0) - 1, M2C_FIELD(var_s1, u8 *, 1), 0, &sp10) << 0x10) == 0) || !(sp10 & 0xFF20)) {
                func_8009A21C(M2C_FIELD(var_s1, u8 *, 0), M2C_FIELD(var_s1, u8 *, 1), 0x800);
                func_8001E660(var_s3, var_s4, 0, 1);
            }
            var_s4 -= 4;
            var_s3 -= 4;
            var_s2 -= 1;
            var_s1 -= 0xC;
        } while (var_s2 >= 0);
    }
}
