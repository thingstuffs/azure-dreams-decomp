#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
s32 func_8009A2B8(u8, u8, s32);                     /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
s16 func_800A4E2C(void *, void *);                  /* extern */
M2C_UNK func_800A56E0(M2C_UNK, s16);                /* extern */
M2C_UNK func_800AA53C(void *);                      /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
M2C_UNK func_80165058();                            /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_8008146E;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_800DDC40;
extern M2C_UNK D_80168888;
extern M2C_UNK D_801688F0;
extern M2C_UNK D_801688F8;

void func_80167E64(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *sp10;
    s16 sp14;
    s16 sp16;
    s32 sp18;
    u8 *sp1C;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    M2C_UNK var_a2_3;
    M2C_UNK var_a2_4;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_s3;
    s32 temp_t0;
    s32 temp_v0_10;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_s6;
    s32 var_s6_2;
    u16 temp_v0_5;
    u16 var_v0;
    u16 var_v0_2;
    u16 var_v0_3;
    u8 temp_v1;
    u8 var_v0_4;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s4;

    temp_s4 = M2C_FIELD(arg0, void **, 0xA8);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_s1 = M2C_FIELD(temp_s4, void **, -0x14);
    sp10 = M2C_FIELD(temp_s4, void **, -0x18);
    switch (temp_v1) {
    case 0:
        M2C_FIELD(arg0, s32 *, 0xAC) = (s32) M2C_FIELD(temp_s4, s32 *, 0x8C);
        if (M2C_FIELD(temp_s4, s32 *, 0x1C) & 0x40000) {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x98) | 0x1000;
        } else {
            var_v0 = M2C_FIELD(arg0, u16 *, 0x98) & 0xEFFF;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = var_v0;
        if (M2C_FIELD(temp_s4, u16 *, 0x98) & 8) {
            var_v0_2 = M2C_FIELD(arg0, u16 *, 0x98) | 0x4000;
        } else {
            var_v0_2 = M2C_FIELD(arg0, u16 *, 0x98) & 0xBFFF;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = var_v0_2;
        if (M2C_FIELD(temp_s4, u16 *, 0x98) & 4) {
            var_v0_3 = M2C_FIELD(arg0, u16 *, 0x98) | 0x2000;
        } else {
            var_v0_3 = M2C_FIELD(arg0, u16 *, 0x98) & 0xDFFF;
        }
        M2C_FIELD(arg0, u16 *, 0x98) = var_v0_3;
        M2C_FIELD(temp_s4, s32 *, 0x8C) = 0;
        temp_s1_2 = M2C_FIELD(temp_s4, void **, -0x14);
        var_a2 = 0x3000;
        if (M2C_FIELD(temp_s4, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(M2C_FIELD(temp_s1_2, u8 *, 0x24), M2C_FIELD(temp_s1_2, u8 *, 0x25), var_a2);
        var_a2_2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2_2 = 0x300;
        }
        func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xFFFBFFFF);
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0xC);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            var_v0_4 = 2;
            if (M2C_FIELD(temp_s1_2, u16 *, 0x14) & 0x8000) {
                M2C_FIELD(arg0, s16 *, 0x96) = 0;
                goto block_55;
            }
        }
        M2C_FIELD(arg0, s16 *, 0x96) = 0xC;
        temp_a0 = (((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 9) & 7) * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (*(temp_a0 + &D_8006CCD8) << 0x16) / 12);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (*(temp_a0 + &D_8006CCE8) << 0x16) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
        M2C_FIELD(temp_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s4, s32 *, 0x1C) & 0xFFFBFFFF);
        M2C_FIELD(temp_s4, u16 *, 0x98) = (u16) (M2C_FIELD(temp_s4, u16 *, 0x98) | 0xC);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801688F0;
        func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801688F0), 0);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    case 1:
        temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0;
        if (temp_v0 == 8) {
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) ((((M2C_FIELD(sp10, s16 *, 0xA) - M2C_FIELD(arg3, s16 *, 0x88)) - *(M2C_FIELD(temp_s4, u8 *, 0x13) + &D_800DDC40)) + 0x10) << 0x10) / temp_v0);
            M2C_FIELD(temp_s4, u16 *, 0x92) = (u16) (M2C_FIELD(temp_s4, u16 *, 0x92) + M2C_FIELD(temp_s4, u16 *, 0x88));
            M2C_FIELD(temp_s4, u16 *, 0x88) = 0U;
        }
        if (M2C_FIELD(arg0, s16 *, 0x96) <= 0) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 0x14) = -0x40000;
            func_800A56E0(0x802, temp_v0);
            M2C_FIELD(arg0, s16 *, 0x96) = 0x10;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801688F8;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801688F8), 0);
block_54:
            var_v0_4 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
block_55:
            M2C_FIELD(arg0, u8 *, 0x9B) = var_v0_4;
        }
        break;
    case 2:
        M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0xFFFE0000);
        M2C_FIELD(temp_s4, u16 *, 0x92) = (u16) ((M2C_FIELD(arg1, u16 *, 0xA) + *(M2C_FIELD(temp_s4, u8 *, 0x13) + &D_800DDC40)) - 0x10);
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
        if (((temp_v0_2 << 0x10) <= 0) || (M2C_FIELD(temp_s1, u16 *, 0x14) & 0x8000)) {
            sp14 = (s16) M2C_FIELD(temp_s1, u8 *, 0x24);
            temp_s3 = (s32) (((s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x800) & 0xFFF) >> 9;
            sp16 = (s16) M2C_FIELD(temp_s1, u8 *, 0x25);
            temp_t0 = temp_s3 * 2;
            sp18 = temp_t0;
            sp1C = temp_t0 + &D_8006CCD8;
            var_s6 = 0x3F;
loop_27:
            if (var_s6 > 0) {
                temp_v0_3 = func_800A4E2C(temp_s1 + 0x24, temp_s1 + 0x25);
                var_s6 -= 1;
                if (temp_v0_3 >= 0) {
                    var_s6_2 = var_s6 + 1;
                    if (temp_v0_3 == M2C_FIELD(&D_80082E80, s8 *, 0x26)) {
                        var_s6 = var_s6_2 - 1;
                        if (D_8008146E < 2) {
                            var_s6_2 = var_s6 + 1;
                            goto block_32;
                        }
                        goto loop_27;
                    }
block_32:
                    var_s6 = var_s6_2 - 1;
                    if (((func_8009A2B8(M2C_FIELD(temp_s1, u8 *, 0x24), M2C_FIELD(temp_s1, u8 *, 0x25), temp_s3) << 0x10) != 0) || (M2C_FIELD(temp_s1, s8 *, 0x26) = (s8) temp_v0_3, M2C_FIELD(arg2, s8 *, 0x26) = (s8) temp_v0_3, M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(temp_s1, u8 *, 0x24) + *sp1C), M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(temp_s1, u8 *, 0x25) + *(sp18 + &D_8006CCE8)), temp_v0_4 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80)), M2C_FIELD(arg3, s16 *, 0x88) = temp_v0_4, var_s6 = (var_s6 + 1) - 1, ((temp_v0_4 < 0x201) == 0)) || (temp_v0_5 = func_800BCB04((M2C_FIELD(temp_s1, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(temp_s1, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80)), M2C_FIELD(temp_s4, u16 *, 0x88) = temp_v0_5, var_s6 = (var_s6 + 1) - 1, (((s16) temp_v0_5 < 0x201) == 0)) || (var_s6 = (var_s6 + 1) - 1, (M2C_FIELD(arg3, s16 *, 0x88) != (s16) temp_v0_5))) {
                        goto loop_27;
                    }
                } else {
                    goto loop_27;
                }
            } else {
                M2C_FIELD(temp_s1, u8 *, 0x24) = (u8) sp14;
                M2C_FIELD(temp_s1, u8 *, 0x25) = (u8) sp16;
            }
            temp_v0_6 = ((M2C_FIELD(temp_s1, u8 *, 0x24) << 6) + 0x20) << 0x10;
            M2C_FIELD(sp10, s32 *, 0) = temp_v0_6;
            M2C_FIELD(arg1, s32 *, 0) = temp_v0_6;
            temp_v0_7 = ((M2C_FIELD(temp_s1, u8 *, 0x25) << 6) + 0x20) << 0x10;
            M2C_FIELD(sp10, s32 *, 4) = temp_v0_7;
            M2C_FIELD(arg1, s32 *, 4) = temp_v0_7;
            M2C_FIELD(arg1, s32 *, 8) = (s32) (((s16) M2C_FIELD(temp_s4, u16 *, 0x88) - 0x100) << 0x10);
            M2C_FIELD(temp_s4, s32 *, 0x90) = (s32) M2C_FIELD(arg0, s32 *, 0x90);
            M2C_FIELD(arg0, s16 *, 0x96) = 8;
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) ((M2C_FIELD(arg3, s16 *, 0x88) << 0x10) - M2C_FIELD(arg1, s32 *, 8)) / 8);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801688F8;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_801688F8), 0);
            func_800AA53C(arg3);
            func_800AA53C(temp_s4);
            goto block_54;
        }
        break;
    case 3:
        M2C_FIELD(temp_s4, u16 *, 0x92) = (u16) (M2C_FIELD(arg0, u16 *, 0x92) + 0x40);
        if (((s16) M2C_FIELD(arg0, u16 *, 0x92) >= 0) || ((temp_v0_8 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1, M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_8, ((temp_v0_8 << 0x10) <= 0)) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000))) {
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(temp_s4, s32 *, 0x90) = 0;
            if (M2C_FIELD(arg0, u16 *, 0x98) & 0x1000) {
                M2C_FIELD(temp_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s4, s32 *, 0x1C) | 0x40000);
            }
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x4000)) {
                M2C_FIELD(temp_s4, u16 *, 0x98) = (u16) (M2C_FIELD(temp_s4, u16 *, 0x98) & 0xFFF7);
            }
            if (!(M2C_FIELD(arg0, u16 *, 0x98) & 0x2000)) {
                M2C_FIELD(temp_s4, u16 *, 0x98) = (u16) (M2C_FIELD(temp_s4, u16 *, 0x98) & 0xFFFB);
            }
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
            M2C_FIELD(temp_s4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s4, s32 *, 0x1C) | 0x40000000);
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg0, s16 *, 0x96) = 8;
            temp_a0_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) -(*(temp_a0_2 + &D_8006CCD8) << 0x16) / 8);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) -(*(temp_a0_2 + &D_8006CCE8) << 0x16) / (s16) M2C_FIELD(arg0, s16 *, 0x96));
            M2C_FIELD(sp10, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            goto block_54;
        }
        break;
    case 4:
        temp_v0_9 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
        M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_9;
        if (((temp_v0_9 << 0x10) <= 0) || (M2C_FIELD(temp_s1, u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg1, s32 *, 0) = (s32) (((M2C_FIELD(arg2, u8 *, 0x24) << 6) + 0x20) << 0x10);
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 4) = (s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) + 0x20) << 0x10);
            M2C_FIELD(temp_s4, s32 *, 0x8C) = (s32) M2C_FIELD(arg0, s32 *, 0xAC);
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80165058;
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            func_800A4ACC(arg3);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF3);
            temp_v0_10 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000;
            M2C_FIELD(arg3, s32 *, 0x1C) = temp_v0_10;
            var_a2_3 = 0x3000;
            if (temp_v0_10 & 0x2000) {
                var_a2_3 = 0x300;
            }
            func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_3);
            var_a2_4 = 0x3000;
            if (M2C_FIELD(temp_s4, s32 *, 0x1C) & 0x2000) {
                var_a2_4 = 0x300;
            }
            func_8009A21C(M2C_FIELD(temp_s1, u8 *, 0x24), M2C_FIELD(temp_s1, u8 *, 0x25), var_a2_4);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168888;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168888), 0);
            M2C_FIELD(arg3, s8 *, 0x6D) = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            goto block_54;
        }
        break;
    }
}
