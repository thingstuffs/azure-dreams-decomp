#include "common.h"
#include "m2c_compat.h"

s32 func_800A6D30();                                /* extern */
s32 func_800A6DA4(M2C_UNK, s32, s32);               /* extern */
extern s32 D_800E296C;
extern M2C_UNK D_800E3648;
extern M2C_UNK D_800E39C8;

void func_8001CFB8(void *arg0) {
    M2C_UNK *var_s1;
    M2C_UNK *var_s2;
    s16 temp_v1;
    s16 var_s4;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_v1;

    if (!(D_800E296C & 0x10000000)) {
        temp_lo = M2C_FIELD(arg0, u16 *, 6) * M2C_FIELD(arg0, u16 *, 4);
        temp_v1 = (temp_lo >> 2) + (func_800A6D30() & 7);
        var_s4 = temp_v1;
        var_v1 = 0;
        if (temp_v1 >= 0x1D) {
            var_s4 = 0x1C;
        }
        var_s1 = &D_800E3648;
        var_s2 = &D_800E39C8;
loop_4:
        var_v1 += 1;
        if (M2C_FIELD(var_s1, u8 *, 1) == 0) {
            temp_s0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 4) - 1) & 0xFFFF, temp_lo) & 0xFFFF;
            temp_v0 = func_800A6DA4(0, (M2C_FIELD(arg0, u16 *, 6) - 1) & 0xFFFF);
            M2C_FIELD(var_s2, s8 *, 6) = (s8) (M2C_FIELD(arg0, u8 *, 0) + temp_s0);
            M2C_FIELD(var_s2, s8 *, 7) = (s8) (M2C_FIELD(arg0, u8 *, 2) + (temp_v0 & 0xFFFF));
            M2C_FIELD(var_s1, s8 *, 0) = 0x13;
            M2C_FIELD(var_s1, u8 *, 1) = 0x15U;
            M2C_FIELD(var_s1, s8 *, 3) = 0xC0;
            M2C_FIELD(var_s1, s8 *, 2) = (s8) var_s4;
            M2C_FIELD(var_s2, s32 *, 8) = 0;
            return;
        }
        var_s1 += 4;
        var_s2 += 0x18;
        if (var_v1 >= 0x20) {

        } else {
            goto loop_4;
        }
    }
}
