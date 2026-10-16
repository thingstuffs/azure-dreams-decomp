#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009A21C(u8, u8, M2C_UNK, void *);     /* extern */
s32 func_800A4E2C(u8 *, u8 *);                      /* extern */
s32 func_800A6D30();                                /* extern */
extern s16 D_8008146C;
extern M2C_UNK D_8008333C;
extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E3648;
extern M2C_UNK D_800E36C8;
extern M2C_UNK D_800E39C8;
extern M2C_UNK D_800E3CD8;

void func_8001784C(void) {
    u8 sp10;
    u8 sp11;
    M2C_UNK *var_a1;
    M2C_UNK *var_a1_2;
    M2C_UNK *var_v1;
    M2C_UNK *var_v1_2;
    s16 *var_v1_3;
    s32 temp_s1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s0_2;
    void *temp_a3;
    void *temp_v0;

    temp_s1 = M2C_FIELD(&D_8008333C, s32 *, 0);
    if ((*(s32 *)0x80012090 == 2) || (D_8008146C != 0x28)) {
        var_s0 = 0;
loop_3:
loop_4:
        if (func_800A4E2C(&sp10, &sp11) & 0x8000) {
            goto loop_4;
        }
        var_a0 = 0;
        var_v1 = &D_800E36C8;
        var_a1 = &D_800E3548;
        do {
            if ((M2C_FIELD(var_a1, u8 *, 1) != 0) && (M2C_FIELD(var_v1, u8 *, 0) == sp10) && (M2C_FIELD(var_v1, u8 *, 1) == sp11)) {
                goto loop_3;
            }
            var_v1 += 0xC;
            var_a0 += 1;
            var_a1 += 4;
        } while (var_a0 < 0x40);
        var_a0_2 = 0;
        var_v1_2 = &D_800E39C8;
        var_a1_2 = &D_800E3648;
        do {
            if ((M2C_FIELD(var_a1_2, u8 *, 1) != 0) && (M2C_FIELD(var_v1_2, u8 *, 6) == sp10) && (M2C_FIELD(var_v1_2, u8 *, 7) == sp11)) {
                goto loop_3;
            }
            var_v1_2 += 0x18;
            var_a0_2 += 1;
            var_a1_2 += 4;
        } while (var_a0_2 < 0x20);
        temp_a3 = (var_s0 * 8) + &D_800E3CD8;
        M2C_FIELD(temp_a3, s16 *, 0) = 2;
        M2C_FIELD(temp_a3, s16 *, 2) = (s16) sp10;
        M2C_FIELD(temp_a3, s16 *, 4) = (s16) sp11;
        temp_v0 = ((sp10 + (sp11 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s1;
        M2C_FIELD(temp_v0, u16 *, 2) = (u16) (M2C_FIELD(temp_v0, u16 *, 2) - 0x20);
        M2C_FIELD(temp_a3, u16 *, 6) = (u16) M2C_FIELD((((sp10 + (sp11 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s1), u16 *, 2);
        *(((sp10 + (sp11 << M2C_FIELD(&D_8008333C, s16 *, 0x14))) * 6) + temp_s1) = 1;
        func_8009A21C(sp10, sp11, 0x20, temp_a3);
        if (!(func_800A6D30() & 0x3F)) {
            var_s0 += 1;
            if (var_s0 < 4) {
                goto loop_4;
            }
        }
        var_s0_2 = var_s0 + 1;
        if (var_s0_2 < 4) {
            var_v1_3 = (var_s0_2 * 8) + &D_800E3CD8;
            do {
                *var_v1_3 = 0;
                var_s0_2 += 1;
                var_v1_3 += 8;
            } while (var_s0_2 < 4);
        }
    }
}
