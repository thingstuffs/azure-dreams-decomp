#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800172A0(M2C_UNK *, s16);              /* extern */
s32 func_80033BC0(M2C_UNK);                         /* extern */
M2C_UNK func_8003DB4C(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK func_8003DB94(M2C_UNK *, s32, M2C_UNK);     /* extern */
void *func_8003FE78(M2C_UNK, M2C_UNK *, M2C_UNK);   /* extern */
s32 func_80042900(void *, M2C_UNK);                 /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_800489F4(M2C_UNK *, u8, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_80094988(void *, void *, u8, u8);      /* extern */
M2C_UNK func_80096088(void *, void *);              /* extern */
M2C_UNK func_8009A21C(u8, u8, M2C_UNK);             /* extern */
M2C_UNK func_8009A350(u8, u8, s16, u16 *);          /* extern */
M2C_UNK func_8009D380();                            /* extern */
s8 func_8009FB34(u8, u8, M2C_UNK *, u16);           /* extern */
M2C_UNK func_800A2B04(M2C_UNK *, u8, u8);           /* extern */
s32 func_800A4E2C(u8 *, u8 *);                      /* extern */
M2C_UNK func_800A6C00(s8 *);                        /* extern */
M2C_UNK func_800BC26C(M2C_UNK *, M2C_UNK, void *, void *); /* extern */
s16 func_800BCB04(u16, u16, M2C_UNK);               /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern s32 D_80080A80;
extern s16 D_8008146C;
extern s32 D_80081470;
extern s32 D_80081484;
extern void *D_800814A8;
extern s8 D_80082A3B;
extern M2C_UNK D_80082E60;
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083160;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083498;
extern M2C_UNK D_80083780;
extern M2C_UNK D_80089AA0;
extern M2C_UNK D_800DCE60;
extern s8 D_800DCF5A;
extern M2C_UNK D_800DCFB0;
extern M2C_UNK D_800DD078;
extern M2C_UNK D_800DD090;
extern M2C_UNK D_800DD0A8;
extern M2C_UNK D_800DD264;
extern M2C_UNK D_800DD26C;
extern M2C_UNK D_800DD274;
extern s32 D_800E3540;
extern M2C_UNK D_800E3CF8;
extern M2C_UNK *D_800E3D18;
extern M2C_UNK D_800E3D48;
extern void *D_800E3D7C;
extern M2C_UNK D_800E3D80;
extern M2C_UNK D_800E4938;

void func_800165B8(void) {
    u8 sp10;
    u8 sp11;
    u16 sp12;
    s16 temp_s0;
    s16 temp_v0_2;
    s16 var_s1_2;
    s32 *var_s2;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 var_s1;
    s32 var_s1_3;
    s32 var_v0;
    u16 temp_a3;
    u16 temp_v1_3;
    u8 temp_a1;
    u8 temp_v0_3;
    void *temp_s5;
    void *temp_v0;
    void *temp_v1_2;
    void *var_v0_2;

    D_800DCF5A = 1;
    temp_v0 = func_8003FE78(0, &D_80083498, 0x53);
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80089AA0;
    func_8004491C(temp_v0, &D_80045340);
    M2C_FIELD(temp_v0, M2C_UNK **, 8) = &D_80083780;
    func_8003DB4C(&D_80083780, 6);
    M2C_FIELD(temp_v0, M2C_UNK **, 0xC) = &D_80082E80;
    func_8003DB4C(&D_80082E80, 0xC);
    temp_s5 = temp_v0 + 0x20;
    D_800814A8 = temp_s5;
    D_800E3D7C = temp_s5;
    M2C_FIELD(temp_s5, s8 *, 0x13) = 0;
    if (!(M2C_FIELD(&D_80082E60, u16 *, 0x16) & 1)) {
loop_1:
        do {

        } while (func_800A4E2C(&sp10, &sp11) & 0x8000);
        if ((*(s32 *)0x80012090 == 0) && (func_80033BC0(0x1389) == 0)) {
            var_s1 = 7;
            if (D_8008146C == 0x1F) {
                var_s1_2 = -1;
                temp_s0 = func_800BCB04((sp10 << 6) | 0x20, (sp11 << 6) | 0x20, -0x400);
loop_7:
                func_8009A350(sp10, sp11, var_s1_2, &sp12);
                if (!(sp12 & 0x8000)) {
                    temp_v1 = (var_s1_2 & 7) * 2;
                    var_v0 = (func_800BCB04(((sp10 << 6) + 0x20 + (*(temp_v1 + &D_8006CCD8) << 6)) & 0xFFE0, ((sp11 << 6) + 0x20 + (*(temp_v1 + &D_8006CCE8) << 6)) & 0xFFE0, -0x400) & 0xFF) - (temp_s0 & 0xFF);
                    if (var_v0 < 0) {
                        var_v0 = -var_v0;
                    }
                    var_s1_2 += 1;
                    if (var_v0 < 0x21) {
                        if (var_s1_2 >= 2) {
                            var_s1 = 7;
                        } else {
                            goto loop_7;
                        }
                    } else {
                        goto loop_1;
                    }
                } else {
                    goto loop_1;
                }
            }
        } else {
            goto block_14;
        }
    } else {
        sp10 = M2C_FIELD(&D_80082E60, u8 *, 0x10);
        sp11 = M2C_FIELD(&D_80082E60, u8 *, 0x12);
block_14:
        var_s1 = 7;
    }
    M2C_FIELD(&D_80082E80, u8 *, 0x24) = sp10;
    M2C_FIELD(&D_80082E80, u8 *, 0x25) = sp11;
    func_800A2B04(&D_80083780, sp10, sp11);
    func_8009A21C(sp10, sp11, 0x300);
    temp_v0_2 = func_800BCB04(M2C_FIELD(&D_80083780, u16 *, 2), M2C_FIELD(&D_80083780, u16 *, 6), -0x400);
    M2C_FIELD(&D_80083780, s16 *, 0xA) = temp_v0_2;
    M2C_FIELD(temp_s5, s16 *, 0x88) = temp_v0_2;
    M2C_FIELD(temp_s5, s16 *, 0x8A) = temp_v0_2;
    M2C_FIELD(&D_80082E80, s32 *, 0xC) = 0x2C808080;
    M2C_FIELD(temp_s5, u16 *, 0xA2) = (u16) (M2C_FIELD(temp_s5, u16 *, 0xA2) | 0x10);
    M2C_FIELD(temp_s5, void **, 0x5C) = temp_v0;
    M2C_FIELD(temp_s5, void **, 0x58) = temp_v0;
    M2C_FIELD(&D_80082E80, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(&D_80082E80, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(&D_80082E80, s32 *, 0x28) = (s32) D_80080A80;
    func_80094988(temp_s5, temp_s5, sp10, sp11);
    var_s2 = &D_800E3D80 + 0x1C;
    M2C_FIELD(temp_s5, s32 *, 0x14) = (s32) (M2C_FIELD(temp_s5, s32 *, 0x14) & 0xFFEFFFFF);
    do {
        func_800489F4(&D_80082E80, *(var_s1 + &D_800DD078), 0, 0);
        *var_s2 = M2C_FIELD(&D_80082E80, s32 *, 8);
        var_s2 -= 4;
        func_800489F4(&D_80082E80, *(var_s1 + &D_800DD0A8), 0, 0);
        temp_s0_2 = var_s1 * 4;
        *(temp_s0_2 + &D_800E3CF8) = M2C_FIELD(&D_80082E80, s32 *, 8);
        temp_a1 = *(var_s1 + &D_800DD090);
        var_s1 -= 1;
        func_800489F4(&D_80082E80, temp_a1, 0, 0);
        *(temp_s0_2 + &D_800E3D48) = M2C_FIELD(&D_80082E80, s32 *, 8);
    } while (var_s1 >= 0);
    D_800E3D18 = &D_800E3CF8;
    if ((func_80042900(temp_s5, 0xA) << 0x10) != 0) {
        M2C_FIELD(&D_80082E80, M2C_UNK **, 0x2C) = &D_800DD274;
        func_8003DB94(&D_80082E80, *((((s32) (D_80083228 + M2C_FIELD(temp_s5, s16 *, 0x2A) + 0x100) >> 7) & 0x1C) + &D_800DD274), 0);
    } else {
        func_800489F4(&D_80082E80, 0xB0U, 0, 1);
        M2C_FIELD(&D_80082E80, M2C_UNK **, 0x2C) = &D_800DCFB0;
    }
    M2C_FIELD(temp_s5, s16 *, 0x94) = -1;
    var_s1_3 = 0;
    M2C_FIELD(temp_s5, s16 *, 0x118) = 0;
    M2C_FIELD(temp_s5, s16 *, 0x2A) = (s16) (0x400 - (((u16) D_80083228 + 0x100) & 0xE00));
    func_800BC26C(&D_80083498, 1, &D_80082E80 + 0x2C, temp_s5 + 0x2A);
    M2C_FIELD(temp_s5, s8 *, 0x9A) = 0xFF;
    M2C_FIELD(temp_s5, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_s5, s32 *, 0x1C) & 0xFFEFFFFF);
    func_80096088(temp_s5, temp_s5);
    M2C_FIELD(&D_80082E80, u16 *, 0x14) = (u16) (M2C_FIELD(&D_80082E80, u16 *, 0x14) | 0x8000);
    var_v0_2 = (void *)0x80010000;
    do {
        temp_v0_3 = M2C_FIELD(var_v0_2, u8 *, 0x2D6C);
        temp_v1_2 = temp_s5 + var_s1_3;
        M2C_FIELD(temp_v1_2, u8 *, 0xFA) = temp_v0_3;
        if (temp_v0_3 == 2) {
            M2C_FIELD(temp_v1_2, u8 *, 0xFA) = 1U;
        }
        var_s1_3 += 1;
        var_v0_2 = var_s1_3 + 0x80010000;
    } while (var_s1_3 < 2);
    M2C_FIELD(temp_s5, u16 *, 0xA2) = (u16) (M2C_FIELD(temp_s5, u16 *, 0xA2) | 0x10);
    M2C_FIELD(temp_s5, s32 *, 0x14) = (s32) (M2C_FIELD(temp_s5, s32 *, 0x14) | 0x4000);
    M2C_FIELD(temp_s5, M2C_UNK *, 0x34) = M2C_UNALIGNED32(M2C_FIELD((void *)0x8001020C, M2C_UNK *, 0));
    M2C_FIELD(temp_s5, M2C_UNK *, 0x38) = M2C_UNALIGNED32(M2C_FIELD((void *)0x8001020C, M2C_UNK *, 4));
    M2C_FIELD(temp_s5, M2C_UNK *, 0x3C) = M2C_UNALIGNED32(M2C_FIELD((void *)0x8001020C, M2C_UNK *, 8));
    M2C_FIELD(temp_s5, s8 *, 0x40) = (s8) M2C_FIELD((void *)0x8001020C, s8 *, 0xC);
    M2C_FIELD(temp_s5, s8 *, 0x42) = 0;
    M2C_FIELD(temp_s5, s8 *, 0x41) = 0;
    M2C_FIELD(temp_s5, s32 *, 0xDC) = 0x2C808080;
    M2C_FIELD(temp_s5, s32 *, 0xE0) = 0x2C808080;
    temp_v1_3 = *(((s32) (*(u16 *)0x800120A2 << 0x10) >> 0xF) + &D_800DD264);
    M2C_FIELD(&D_80083160, u16 *, 0xC4) = temp_v1_3;
    M2C_FIELD(&D_800DCE60, u16 *, 0) = temp_v1_3;
    temp_a3 = *(((s32) (*(u16 *)0x800120A0 << 0x10) >> 0xF) + &D_800DD26C);
    M2C_FIELD(&D_800DCE60, s16 *, 4) = 0;
    M2C_FIELD(&D_800DCE60, u16 *, 2) = (u16) M2C_FIELD(&D_80083160, u16 *, 0xC6);
    M2C_FIELD(&D_800E4938, s32 *, 0) = 0;
    M2C_FIELD(&D_800E4938, void **, 4) = temp_v0;
    M2C_FIELD(&D_800E4938, s32 *, 8) = 0;
    M2C_FIELD(&D_80083460, u16 *, 2) = (u16) (M2C_FIELD(&D_80083460, u16 *, 2) | 2);
    M2C_FIELD(&D_800DCE60, u16 *, 6) = temp_a3;
    M2C_FIELD(&D_80082E80, s8 *, 0x26) = func_8009FB34(M2C_FIELD(&D_80082E80, u8 *, 0x24), M2C_FIELD(&D_80082E80, u8 *, 0x25), &D_80083460, temp_a3);
    M2C_FIELD(temp_s5, s8 *, 0x9C) = -2;
    func_8009D380();
    D_800E3540 = 0;
    D_80081484 = 0;
    D_80081470 = 0;
    func_800172A0(&D_80083780, (s16) M2C_FIELD(&D_800DCE60, u16 *, 6));
    D_80082A3B = -0x24;
    if (*(u16 *)0x80013714 & 4) {
        func_800A6C00(&D_80082A3B);
    }
}
