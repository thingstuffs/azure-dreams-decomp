#include "common.h"
#include "m2c_compat.h"

s32 func_8003DE58(s32, void *, void *, M2C_UNK);    /* extern */
void *func_8003FD64(M2C_UNK, M2C_UNK *, void *);    /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s16 func_80066460(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s16 func_8006649C(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_8009C12C(void *, void *, s16, M2C_UNK); /* extern */
M2C_UNK func_800A2B04(void *, u8, u8);              /* extern */
M2C_UNK func_800A4ACC(void *);                      /* extern */
M2C_UNK func_800A56E0(M2C_UNK);                     /* extern */
M2C_UNK func_800AD594(void *, M2C_UNK);             /* extern */
M2C_UNK func_800C8EFC(s32, M2C_UNK);                /* extern */
M2C_UNK func_80158E94();                            /* static */
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DB618;
extern M2C_UNK D_800DB660;
extern void *D_800E3DE8;
extern M2C_UNK D_80158838;
extern M2C_UNK D_8015884C;
extern M2C_UNK D_8015CA8C;
extern M2C_UNK D_8015CA94;
extern M2C_UNK D_8015CAA4;
extern M2C_UNK D_8015CAAC;

void func_8015A7B4(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp10;
    M2C_UNK sp14;
    M2C_UNK sp16;
    M2C_UNK sp18;
    M2C_UNK sp1C;
    s16 sp20;
    M2C_UNK sp28;
    M2C_UNK sp2C;
    M2C_UNK sp30;
    M2C_UNK sp34;
    s16 sp38;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_7;
    u8 temp_v1;
    void *temp_a2;
    void *temp_s0;
    void *temp_v0_2;
    void *temp_v0_6;
    void *temp_v1_4;

    sp10 = M2C_UNALIGNED32(M2C_FIELD(&D_80158838, M2C_UNK *, 0));
    sp14 = M2C_UNALIGNED32(M2C_FIELD(&D_80158838, M2C_UNK *, 4));
    sp18 = M2C_UNALIGNED32(M2C_FIELD(&D_80158838, M2C_UNK *, 8));
    sp1C = M2C_UNALIGNED32(M2C_FIELD(&D_80158838, M2C_UNK *, 0xC));
    sp20 = M2C_FIELD(&D_80158838, s16 *, 0x10);
    sp28 = M2C_UNALIGNED32(M2C_FIELD(&D_8015884C, M2C_UNK *, 0));
    sp2C = M2C_UNALIGNED32(M2C_FIELD(&D_8015884C, M2C_UNK *, 4));
    sp30 = M2C_UNALIGNED32(M2C_FIELD(&D_8015884C, M2C_UNK *, 8));
    sp34 = M2C_UNALIGNED32(M2C_FIELD(&D_8015884C, M2C_UNK *, 0xC));
    sp38 = M2C_FIELD(&D_8015884C, s16 *, 0x10);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    switch (temp_v1) {
    case 0:
        M2C_FIELD(arg0, u16 *, 0xA8) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(arg0, u16 *, 0xAA) = (u16) M2C_FIELD(arg1, u16 *, 6);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
            M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            return;
        }
        temp_v0 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 9) & 7;
        temp_a0 = temp_v0 + 4;
        var_v1 = temp_a0;
        if (temp_a0 < 0) {
            var_v1 = temp_v0 + 0xB;
        }
        temp_v1_2 = (temp_a0 - (var_v1 & 0x18)) * 2;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(temp_v1_2 + &D_8006CCD8) * 0x30000);
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(temp_v1_2 + &D_8006CCE8) * 0x30000);
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CA8C;
        func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CA8C), 0);
block_27:
block_28:
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        return;
    case 1:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CA94;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CA94), 0);
            M2C_FIELD(arg0, s32 *, 0x90) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
            M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF40000;
            goto block_27;
        }
    default:
        return;
    case 2:
        temp_v1_3 = M2C_FIELD(arg1, s32 *, 0x14) + 0x20000;
        M2C_FIELD(arg1, s32 *, 0x14) = temp_v1_3;
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + temp_v1_3);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) -M2C_FIELD(arg1, s32 *, 0xC) >> 1);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) -M2C_FIELD(arg1, s32 *, 0x10) >> 1);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CAA4;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CAA4), 0);
            M2C_FIELD(arg0, u16 *, 0x96) = 7U;
            goto block_28;
        }
        break;
    case 3:
        temp_a2 = arg0 + 0xAC;
        if (M2C_FIELD(arg2, s8 *, 4) < 3) {
            if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, temp_a2, 0) == 0) {
                M2C_FIELD(arg0, u16 *, 0xB0) = 0U;
                M2C_FIELD(arg0, u16 *, 0xAE) = 0U;
                M2C_FIELD(arg0, u16 *, 0xAC) = 0U;
            }
            M2C_FIELD(arg0, u16 *, 0xAC) = (u16) (M2C_FIELD(arg0, u16 *, 0xAC) + M2C_FIELD(arg1, u16 *, 2));
            M2C_FIELD(arg0, u16 *, 0xAE) = (u16) (M2C_FIELD(arg0, u16 *, 0xAE) + M2C_FIELD(arg1, u16 *, 6));
            M2C_FIELD(arg0, u16 *, 0xB0) = (u16) (M2C_FIELD(arg0, u16 *, 0xB0) + M2C_FIELD(arg1, u16 *, 0xA));
        } else {
            temp_v0_2 = func_8003FD64(1, &D_80083498, temp_a2);
            if (temp_v0_2 != NULL) {
                M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_800DB618;
                func_8004491C(temp_v0_2, &D_800DB660);
                temp_s0 = temp_v0_2 + 0x20;
                M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) M2C_FIELD(arg0, u16 *, 0xAC);
                M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) M2C_FIELD(arg0, u16 *, 0xAE);
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) M2C_FIELD(arg0, u16 *, 0xB0);
                if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, arg0 + 0xAC, 0) == 0) {
                    M2C_FIELD(arg0, u16 *, 0xB0) = 0U;
                    M2C_FIELD(arg0, u16 *, 0xAE) = 0U;
                    M2C_FIELD(arg0, u16 *, 0xAC) = 0U;
                }
                temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xAC) + M2C_FIELD(arg1, u16 *, 2);
                M2C_FIELD(arg0, u16 *, 0xAC) = temp_v0_3;
                M2C_FIELD(temp_s0, u16 *, 8) = temp_v0_3;
                temp_v0_4 = M2C_FIELD(arg0, u16 *, 0xAE) + M2C_FIELD(arg1, u16 *, 6);
                M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_4;
                M2C_FIELD(temp_s0, u16 *, 0xA) = temp_v0_4;
                temp_v0_5 = M2C_FIELD(arg0, u16 *, 0xB0) + M2C_FIELD(arg1, u16 *, 0xA);
                M2C_FIELD(arg0, u16 *, 0xB0) = temp_v0_5;
                M2C_FIELD(temp_s0, u16 *, 0xC) = temp_v0_5;
                M2C_FIELD(temp_s0, s16 *, 0x2E) = 0x10;
                M2C_FIELD(temp_s0, s16 *, 0x30) = 0x10;
                M2C_FIELD(temp_s0, s16 *, 0x36) = 0x10;
                M2C_FIELD(temp_s0, s32 *, 4) = 0x200020;
                M2C_FIELD(temp_s0, s32 *, 0x18) = 0xC0C0C0;
                M2C_FIELD(temp_s0, u16 *, 0x2C) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
                M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (((6 - M2C_FIELD(arg2, s8 *, 4)) * 0x30303) + 0x141414);
                temp_v0_6 = (M2C_FIELD(arg2, s8 *, 4) * 6) + &sp10;
                M2C_FIELD(temp_v0_2, M2C_UNK *, 0x40) = M2C_UNALIGNED32(M2C_FIELD(temp_v0_6, M2C_UNK *, -0x12));
                M2C_FIELD(temp_v0_2, s16 *, 0x44) = (s16) M2C_FIELD(temp_v0_6, s16 *, -0xE);
                temp_v1_4 = &sp16 + (M2C_FIELD(arg2, s8 *, 4) * 6);
                M2C_FIELD(temp_v0_2, M2C_UNK *, 0x46) = M2C_UNALIGNED32(M2C_FIELD(temp_v1_4, M2C_UNK *, 0));
                M2C_FIELD(temp_v0_2, s16 *, 0x4A) = (s16) M2C_FIELD(temp_v1_4, s16 *, 4);
                M2C_FIELD(temp_s0, s16 *, 0x32) = func_80066460(0, 1, 0x2C0, 0x100);
                M2C_FIELD(temp_s0, s16 *, 0x34) = func_8006649C(0, 0x1F8);
            }
        }
        temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_7;
        if (((temp_v0_7 << 0x10) == 0) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
            func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
            func_800A56E0(0x808);
        }
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CAAC;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CAAC), 0);
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
            return;
        }
        break;
    case 4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_8015CAAC;
            func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_8015CAAC), 0);
            if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
                func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            }
            goto block_27;
        }
        break;
    case 5:
        var_v0 = (s16) M2C_FIELD(arg1, u16 *, 2) - (s16) M2C_FIELD(arg0, u16 *, 0xA8);
        if (var_v0 < 0) {
            var_v0 = -var_v0;
        }
        if (var_v0 < 0x41) {
            var_v0_2 = (s16) M2C_FIELD(arg1, u16 *, 6) - (s16) M2C_FIELD(arg0, u16 *, 0xAA);
            if (var_v0_2 < 0) {
                var_v0_2 = -var_v0_2;
            }
            if (var_v0_2 >= 0x41) {
                goto block_35;
            }
        } else {
block_35:
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        }
        if (((s16) M2C_FIELD(arg1, u16 *, 2) == (s16) M2C_FIELD(arg0, u16 *, 0xA8)) && ((s16) M2C_FIELD(arg1, u16 *, 6) == (s16) M2C_FIELD(arg0, u16 *, 0xAA))) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AD594(arg3, 0x100);
            M2C_FIELD(arg0, M2C_UNK (**)(), 0x8C) = func_80158E94;
            D_8008346C = 0;
            func_800A4ACC(arg3);
            if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
                M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
            } else {
                D_800E3DE8 = arg3 - 0x20;
            }
            temp_a0_2 = M2C_FIELD(arg3, s32 *, 0x60);
            if ((temp_a0_2 != 0) && !(M2C_FIELD(arg3, s32 *, 0x14) & 0x20000)) {
                func_800C8EFC(temp_a0_2, 0x10);
            }
        }
        break;
    }
}
