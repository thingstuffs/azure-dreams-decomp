#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A350(s16, s16, M2C_UNK, u16 *);    /* extern */
s32 func_800A6D30();                                /* extern */
s32 func_800A6DA4(M2C_UNK, s32);                    /* extern */
extern M2C_UNK D_80073414;
extern M2C_UNK D_800E3648;
extern M2C_UNK D_800E39C8;

void func_8001D0F4(void *arg0) {
    u16 sp10;
    s16 temp_v0_2;
    s16 temp_v1;
    s32 temp_hi;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s6;
    s32 temp_v0;
    s32 var_s4;
    s32 var_v0;
    void *var_s2;
    void *var_s3;

    temp_s6 = func_800A6D30() & 0xFF;
    temp_v1 = ((s32) (M2C_FIELD(arg0, u16 *, 6) * M2C_FIELD(arg0, u16 *, 4)) >> 3) + (func_800A6D30() & 7);
    var_v0 = temp_v1 << 0x10;
    if (temp_v1 >= 0x1D) {
        var_v0 = 0x1C << 0x10;
    }
    var_s4 = var_v0 >> 0x10;
    if (var_s4 >= 0) {
        var_s3 = (var_s4 * 0x18) + &D_800E39C8;
        var_s2 = (var_s4 * 4) + &D_800E3648;
        do {
            temp_s1 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 4) - 1) & 0xFFFF) & 0xFFFF;
            temp_s0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 6) - 1) & 0xFFFF) & 0xFFFF;
            func_8009A350((s16) ((M2C_FIELD(arg0, u16 *, 0) + temp_s1) - 1), (s16) (M2C_FIELD(arg0, u16 *, 2) + temp_s0), 0, &sp10);
            if (!(sp10 & 0x8820)) {
                M2C_FIELD(var_s3, u8 *, 6) = (u8) ((u8) M2C_FIELD(arg0, u16 *, 0) + temp_s1);
                M2C_FIELD(var_s3, u8 *, 7) = (u8) ((u8) M2C_FIELD(arg0, u16 *, 2) + temp_s0);
                if (temp_s6 == 0) {
                    M2C_FIELD(var_s2, s8 *, 0) = 7;
                    goto block_9;
                }
                temp_v0 = func_800A6D30() & 0xFFFF;
                temp_hi = MULTU_HI(temp_v0, 0xAF286BCB);
                temp_v0_2 = (temp_v0 - (((u32) (temp_hi + ((u32) (temp_v0 - temp_hi) >> 1)) >> 4) * 0x13)) + 1;
                if ((*((temp_v0_2 * 0xC) + M2C_FIELD(&D_80073414, s32 *, 0x1B0)) & 0x3000) != 0x3000) {
                    M2C_FIELD(var_s2, s8 *, 0) = (s8) temp_v0_2;
block_9:
                    M2C_FIELD(var_s2, s8 *, 1) = 0x15;
                    M2C_FIELD(var_s2, s8 *, 3) = 0x80;
                    M2C_FIELD(var_s2, s8 *, 2) = 0;
                    func_8009A21C(M2C_FIELD(var_s3, u8 *, 6), M2C_FIELD(var_s3, u8 *, 7), 0x20);
                }
            }
            var_s3 -= 0x18;
            var_s4 -= 1;
            var_s2 -= 4;
        } while (var_s4 >= 0);
    }
}
