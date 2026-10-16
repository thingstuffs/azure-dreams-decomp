#include "common.h"
#include "m2c_compat.h"

s32 func_8001E110(s16, u8, u8);                     /* extern */
s32 func_8001E660(u8 *, u8 *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_8001E824(u8 *);                        /* extern */
M2C_UNK func_8001EC54();                            /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
s32 func_800A4E2C(u8 *, u8 *);                      /* extern */
s16 func_800A6928(M2C_UNK, M2C_UNK);                /* extern */
s32 func_800A6D30(u16);                             /* extern */
s16 func_800A71F4();                                /* extern */
s32 func_800A7A38(u8 *);                            /* extern */
s16 func_800BCA68(s32, s32);                        /* extern */
extern s8 D_8001F6F0;
extern M2C_UNK D_80073414;
extern M2C_UNK D_80081468;
extern M2C_UNK D_800DDC9C;
extern u8 D_800E3548;
extern M2C_UNK D_800E36C8;
extern s32 D_800E3D6C;

void func_8001E18C(void) {
    u8 sp10;
    u8 sp11;
    u8 sp12;
    u8 sp13;
    M2C_UNK *var_s0;
    M2C_UNK *var_s0_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s16 var_s2_2;
    s32 temp_a1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    u16 temp_a0;
    u8 *var_s1;
    u8 *var_s1_2;
    u8 var_v1;
    void *temp_v0_2;
    void *var_v1_2;

    if (D_800E3D6C & 2) {
        var_s2 = 0;
        var_s0 = &D_800E36C8;
        var_s1 = &D_800E3548;
        do {
            if (*var_s1 != 0) {
                func_8009A21C(M2C_FIELD(var_s0, u8 *, 0), M2C_FIELD(var_s0, u8 *, 1), 0x800);
            }
            var_s0 += 0xC;
            var_s2 += 1;
            var_s1 += 4;
        } while (var_s2 < 0x40);
        return;
    }
    temp_a0 = *(u16 *)0x8001209C;
    D_8001F6F0 = 0;
    *(u16 *)0x80013626 = *(u16 *)0x80013624;
    *(u16 *)0x8001209E = temp_a0;
    *(u16 *)0x80013626 += (func_800A6D30(temp_a0) & 3) + 0x33;
    *(u16 *)0x8001209E += (func_800A6D30() & 3) + 0x33;
    if (M2C_FIELD(&D_80081468, s16 *, 6) == 1) {
        var_s5 = 0;
        var_s6 = (func_800A6D30() & 7) + 8;
    } else {
        var_s5 = 0;
        var_s6 = ((s16) (u16) M2C_FIELD(&D_80081468, s16 *, 6) / 2) + (func_800A6D30() & 3);
    }
    if (!(func_800A6D30() & 3)) {
        var_s5 = (s16) *(void *)0x8001209E >= 0x101;
    }
    var_s4 = 0;
    if (!(func_800A6D30() & 3)) {
        var_s4 = (s16) *(void *)0x80013626 >= 0x101;
    }
    var_s2_2 = 0;
    if ((*(s32 *)0x80012090 == 0) && (var_s2_2 = 0, ((func_800A6928(6, 3) < 2) != 0))) {
        if (!(func_800A6D30() & 3)) {
            temp_v0 = func_800A71F4();
            if (temp_v0 >= 0) {
                do {
loop_18:
                    if (func_800A4E2C(&sp10, &sp11) & 0x8000) {
                        goto loop_18;
                    }
                } while (func_8001E110(temp_v0, sp10, sp11) != 0);
                *((temp_v0 * 4) + &D_800E3548) = 0x603;
                temp_v0_2 = (temp_v0 * 0xC) + &D_800E36C8;
                M2C_FIELD(temp_v0_2, u8 *, 0) = sp10;
                M2C_FIELD(temp_v0_2, u8 *, 1) = sp11;
                func_8009A21C(M2C_FIELD(temp_v0_2, u8 *, 0), M2C_FIELD(temp_v0_2, u8 *, 1), 0x800);
                var_s2_2 = 0;
            }
        }
    }
    var_s1_2 = &D_800E3548;
    var_s0_2 = &D_800E36C8;
loop_24:
    if (M2C_FIELD(var_s1_2, u8 *, 1) == 0) {
        if (var_s2_2 < var_s6) {
            if ((func_8001E660(&sp12, &sp13, 0, 0) << 0x10) == 0) {
                if (sp12 != 0) {
                    if (var_s5 != 0) {
                        var_v1 = 1;
                        if (!(func_800A6D30() & 0xF)) {
                            var_v1 = 2;
                        }
                        var_s5 = 0;
                        sp13 = var_v1;
                        sp12 = 2;
                        *(void *)0x8001209E = (u16) (*(void *)0x8001209E & 0xF);
                    } else if (var_s4 != 0) {
                        sp12 = 0x12;
                        sp13 = *((func_800A6D30() & 0x1F) + &D_800DDC9C);
                        temp_a1 = sp13 * 0x14;
                        if ((*(temp_a1 + M2C_FIELD(&D_80073414, s32 *, 0x174)) & 0x10) && (*(temp_a1 + M2C_FIELD(&D_80073414, s32 *, 0x188)) & 0x80) && (sp13 >= 2U)) {
                            sp13 += 1;
                        }
                        var_s4 = 0;
                        *(void *)0x80013626 = (u16) (*(void *)0x80013626 & 0x3F);
                    }
                    goto block_38;
                }
            } else {
block_38:
                M2C_FIELD(var_s1_2, u8 *, 1) = sp12;
                M2C_FIELD(var_s1_2, u8 *, 0) = sp13;
                func_8001E824(var_s1_2);
                do {

                } while (func_800A4E2C(&sp10, &sp11) & 0x8000);
                if (func_8001E110(var_s2_2, sp10, sp11) != 0) {
                    M2C_FIELD(var_s1_2, u8 *, 1) = 0U;
                } else {
                    M2C_FIELD(var_s0_2, u8 *, 0) = sp10;
                    M2C_FIELD(var_s0_2, u8 *, 1) = sp11;
                    goto block_44;
                }
            }
            goto block_45;
        }
    } else {
        sp10 = M2C_FIELD(var_s0_2, u8 *, 0);
        sp11 = M2C_FIELD(var_s0_2, u8 *, 1);
        func_8001E824(var_s1_2);
block_44:
        temp_v0_3 = func_800BCA68((sp10 << 6) | 0x20, (sp11 << 6) | 0x20);
        M2C_FIELD(var_s0_2, s8 *, 7) = 0;
        M2C_FIELD(var_s0_2, s16 *, 4) = temp_v0_3;
        func_8009A21C(sp10, sp11, 0x800);
        M2C_FIELD(var_s0_2, s32 *, 8) = func_800A7A38(var_s1_2);
block_45:
        var_s1_2 += 4;
        var_s2_2 += 1;
        var_s0_2 += 0xC;
        if (var_s2_2 < 0x40) {
            goto loop_24;
        }
    }
    if (var_s2_2 < 0x40) {
        var_v1_2 = (var_s2_2 * 4) + &D_800E3548;
        do {
            M2C_FIELD(var_v1_2, s8 *, 1) = 0;
            M2C_FIELD(var_v1_2, s8 *, 0) = 0;
            var_s2_2 += 1;
            var_v1_2 += 4;
        } while (var_s2_2 < 0x40);
    }
    func_8001EC54();
}
