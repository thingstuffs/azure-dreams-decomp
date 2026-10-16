#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A3D0(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
s16 func_800A4E2C(void *, void *);                  /* extern */
M2C_UNK func_800A56E0(M2C_UNK, u8);                 /* extern */
M2C_UNK func_800AA53C(void *);                      /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
s16 func_800BCB04(s32, s32, s16);                   /* extern */
M2C_UNK func_801650F4();                            /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_80081468;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80168EF8;
extern M2C_UNK D_80168F00;
extern M2C_UNK D_80168F58;
extern M2C_UNK D_80168FC4;
extern M2C_UNK D_80168FD4;

void func_80168428(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_s3;
    s16 temp_s4;
    s16 temp_v0_2;
    s32 temp_a0;
    s32 var_s1;
    s32 var_s1_2;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v0_3;
    u8 temp_a1;
    u8 temp_s3_2;
    u8 temp_s4_2;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_a0 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
    temp_s3 = *(temp_a0 + &D_8006CCD8);
    temp_s4 = *(temp_a0 + &D_8006CCE8);
    switch (temp_a1) {
    case 0:
        var_a2 = 0x3000;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168EF8;
        func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168EF8), 0);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s3 * 0xC0000);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s4 * 0xC0000);
        M2C_FIELD(arg0, u16 *, 0x96) = 4U;
        func_800A56E0(0x80E);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        /* fallthrough */
    case 1:
        if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) || (temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1, M2C_FIELD(arg0, u16 *, 0x96) = temp_v0, ((temp_v0 << 0x10) <= 0))) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168F58;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168F58), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_s3 * -0x40000);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_s4 * -0x40000);
block_27:
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
    default:
        return;
    case 2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168F00;
            func_80047784(arg2, *((((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80168F00), 0);
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                M2C_FIELD(arg0, u16 *, 0x96) = 7U;
                M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
                return;
            }
            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) & 0xFFF);
            goto block_27;
        }
        break;
    case 3:
        temp_a0_2 = M2C_FIELD(arg3, u16 *, 0x2A);
        if (((s16) M2C_FIELD(arg3, u16 *, 0x2A) == 0x400) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_80047784(arg2, 0x37U, 0);
            goto block_27;
        }
        if ((u32) (temp_a0_2 - 0x401) < 0x800U) {
            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (temp_a0_2 - 0x80);
            return;
        }
        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) ((temp_a0_2 + 0x80) & 0xFFF);
        return;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            func_80047784(arg2, 0x38U, 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            temp_s3_2 = M2C_FIELD(arg2, u8 *, 0x24);
            temp_s4_2 = M2C_FIELD(arg2, u8 *, 0x25);
            var_s1 = 0x3F;
loop_21:
            if (var_s1 > 0) {
                temp_v0_2 = func_800A4E2C(arg2 + 0x24, arg2 + 0x25);
                var_s1 -= 1;
                if (temp_v0_2 >= 0) {
                    var_s1_2 = var_s1 + 1;
                    if (temp_v0_2 == M2C_FIELD(&D_80082E80, s8 *, 0x26)) {
                        var_s1 = var_s1_2 - 1;
                        if (M2C_FIELD(&D_80081468, s16 *, 6) < 2) {
                            var_s1_2 = var_s1 + 1;
                            goto block_26;
                        }
                        goto loop_21;
                    }
block_26:
                    var_s1 = var_s1_2 - 1;
                    if (func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80)) >= 0x201) {
                        goto loop_21;
                    }
                } else {
                    goto loop_21;
                }
            } else {
                M2C_FIELD(arg2, u8 *, 0x24) = temp_s3_2;
                M2C_FIELD(arg2, u8 *, 0x25) = temp_s4_2;
            }
            goto block_27;
        }
        break;
    case 5:
        M2C_FIELD(arg2, u16 *, 0x1C) = (u16) *(((s16) M2C_FIELD(arg0, u16 *, 0x96) * 2) + &D_80168FC4);
        M2C_FIELD(arg2, u16 *, 0x1E) = (u16) *(((s16) M2C_FIELD(arg0, u16 *, 0x96) * 2) + &D_80168FD4);
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 4) {
            func_800A56E0(0x705, temp_a1);
        }
        if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) || (temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) + 1, M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3, (((s16) temp_v0_3 < 8) == 0))) {
            M2C_FIELD(&D_80083460, u16 *, 0xA) = (u16) (M2C_FIELD(&D_80083460, u16 *, 0xA) - 1);
            func_800AA53C(arg3);
            M2C_FIELD(arg3, s16 *, 0x88) = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg1, u16 *, 0xA) - 0x80));
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80168F00;
            func_800AD594(arg3, 0x200);
            func_80047784(arg2, *(M2C_FIELD(arg2, M2C_UNK **, 0x2C) + (((s32) (D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7)), 0);
            var_a2_2 = 0x3000;
            if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), var_a2_2);
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            M2C_FIELD(arg2, u16 *, 0x1E) = 0x1000U;
            M2C_FIELD(arg2, u16 *, 0x1C) = 0x1000U;
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_801650F4;
            func_800A4ACC(arg3);
            M2C_FIELD(arg3, s8 *, 0x6D) = 0;
            M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
        }
        break;
    }
}
