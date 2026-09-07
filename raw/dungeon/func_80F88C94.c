#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, off) (*(type *)((u8 *)(base) + (off)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80045340;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern s32 D_80083498;
extern u8 D_800DEC28[];
extern void *D_800E3DE8;
extern u8 D_80171138[];
extern u8 D_80173F0C[];
extern u8 D_80174AD4[];
extern u8 D_80174AE4[];

void func_80172494(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 sp10;
    s32 temp_s0;
    register s32 temp_s6 ASM_REG("$22");
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_v0 ASM_REG("$2");
    s32 temp_v0_3;
    s32 temp_v0_4;
    register s32 temp_v1 ASM_REG("$3");
    s32 var_s2;
    s32 state;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_v0_2;
    u8 *temp_fp;
    register void *arg3_reg ASM_REG("$23");
    u8 *table0;
    u8 *table6;

    arg3_reg = arg3;
    var_s2 = FIELD(arg3_reg, u16, 0x2A) >> 8;
    temp_a0 = var_s2 & 0xE;
    table0 = (u8 *)&D_8006CCD8;
    table0 += temp_a0;
    table6 = (u8 *)&D_8006CCE8;
    temp_s0 = *(s16 *)table0;
    temp_s6 = *(s16 *)(table6 + temp_a0);
    state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = FIELD(arg0, u16, 0x96) - 1;

    switch (state) {
    case 0:
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, u8, 0x9B) = 0xFF;
            FIELD(arg2, u16, 0x14) |= 0x6000;
            func_8009C12C(arg3_reg, arg2, FIELD(arg3_reg, s16, 0x2A), 1);
            goto L_end;
        }
        temp_a0 = 0xF7FFFFFF;
        temp_v1 = 0xFFFBFFFF;
        temp_v0 = -temp_s0;
        temp_v0 <<= 18;
        FIELD(arg1, s32, 0xC) = temp_v0;
        temp_v0 = -temp_s6;
        temp_v0 <<= 18;
        FIELD(arg1, s32, 0x10) = temp_v0;
        FIELD(arg0, u16, 0x98) |= 8;
        temp_v0 = FIELD(arg3_reg, s32, 0x1C);
        temp_v0 &= temp_a0;
        temp_v0 &= temp_v1;
        FIELD(arg3_reg, s32, 0x1C) = temp_v0;
        FIELD(arg0, u16, 0x96) = 4;
        FIELD(arg1, s32, 0x14) = 0xFFFD0000;
        goto L_inc_load;

    case 1:
        temp_v0 = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) = temp_v0 + (temp_v0 >> 2);
        if (FIELD(arg0, s16, 0x96) > 0) {
            goto L_end;
        }
        temp_v0 = FIELD(arg0, u8, 0x9B);
        FIELD(arg0, u16, 0x96) = 8;
        goto L_inc_after_load;

    case 2:
        temp_v0_3 = FIELD(arg1, s32, 0xC);
        temp_v1 = FIELD(arg1, s32, 0x10);
        FIELD(arg1, s32, 0xC) = temp_v0_3 - (temp_v0_3 >> 3);
        temp_v0_4 = FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x10) = temp_v1 - (temp_v1 >> 3);
        FIELD(arg1, s32, 0x14) = temp_v0_4 - (temp_v0_4 >> 3);
        if ((FIELD(arg0, s16, 0x96) == 4) ||
            (FIELD(arg2, u16, 0x14) & 0x8000)) {
            FIELD(arg1, s32, 0xC) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg2, void *, 0x2C) = D_80174AE4;
            temp_v0 = (D_80083228 + FIELD(arg3_reg, s16, 0x2A) + 0x100) >> 9;
            func_80047784(arg2, D_80174AE4[temp_v0 & 7], 0);
        }
        if (FIELD(arg0, s16, 0x96) > 0) {
            goto L_end;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto L_end;
        }
        FIELD(arg0, u16, 0x96) = 4;
        FIELD(arg1, s32, 0xC) = (temp_s0 << 18) + (temp_s0 << 17);
        FIELD(arg1, s32, 0x10) = (temp_s6 << 18) + (temp_s6 << 17);
        func_800A56E0(0x80E);
        ASM_USE(temp_s6);
        goto L_inc_load;

    case 3:
        FIELD(arg0, s32, 0x90) += 0x80000;
        FIELD(arg1, s32, 0xC) += temp_s0 << 18;
        FIELD(arg1, s32, 0x10) += temp_s6 << 18;
        ASM_USE(temp_s6);
        if (FIELD(arg0, s16, 0x96) > 0) {
            goto L_end;
        }
        func_800A56E0(0x808);
        func_8009C12C(arg3_reg, arg2, FIELD(arg3_reg, s16, 0x2A), 1);

L_inc_load:
        temp_v0 = FIELD(arg0, u8, 0x9B);
L_inc_after_load:
        FIELD(arg0, u8, 0x9B) = temp_v0 + 1;
        goto L_end;

    case 4:
        FIELD(arg0, s32, 0x90) += 0x80000;
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto L_end;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3_reg, s32, 0x1C) |= 0x40000;
        FIELD(arg3_reg, s32, 0x1C) |= 0x08000000;
        FIELD(arg0, u16, 0x96) = state;
        FIELD(arg0, u8, 0x9B) = 0xFF;
        goto L_end;

    case 0xFF:
        temp_v0 = FIELD(arg2, u8, 0x24) << 6;
        temp_v1 = FIELD(arg1, s16, 2) - 0x20;
        temp_v0 -= temp_v1;
        temp_v0 = (temp_v0 << 15) >> 1;
        FIELD(arg1, s32, 0xC) = temp_v0;
        ASM_USE(temp_v0);
        temp_v0 = FIELD(arg2, u8, 0x25) << 6;
        temp_v1 = FIELD(arg1, s16, 6) - 0x20;
        temp_v0 -= temp_v1;
        temp_v0 = (temp_v0 << 15) >> 1;
        FIELD(arg1, s32, 0x10) = temp_v0;
        if (!(FIELD(arg2, u16, 0x14) & 0x8000) &&
            (FIELD(arg0, s16, 0x96) != 0)) {
            var_s2 = 9;
            sp10 = temp_s0 * 0x28;
            temp_fp = D_800DEC28;
            do {
                temp_v0_2 = func_8003FD64(0x312, &D_80083498);
                if (temp_v0_2 != NULL) {
                    func_8004491C(temp_v0_2, &D_80045340);
                    temp_s0_2 = (u8 *)temp_v0_2 + 0x20;
                    FIELD(temp_v0_2, void *, 0x10) = D_80173F0C;
                    temp_s1 = FIELD(temp_v0_2, void *, 0xC);
                    FIELD(temp_s0_2, s16, 0xC) =
                        FIELD(arg1, u16, 2) - sp10;
                    FIELD(temp_s0_2, s16, 0xE) =
                        FIELD(arg1, u16, 6) - (temp_s6 * 0x28);
                    FIELD(temp_s0_2, u16, 0x10) = FIELD(arg1, u16, 0xA);
                    FIELD(temp_s0_2, s16, 4) = rand() & 0xF;
                    FIELD(temp_s0_2, s16, 6) = 0;
                    FIELD(temp_s0_2, s16, 8) = (rand() & 0xF) + 8;
                    temp_v0 = rand();
                    temp_a0 = 0xC00000;
                    FIELD(temp_s0_2, s16, 0x14) = temp_v0;
                    temp_v1 = FIELD(arg3_reg, u16, 0x2A);
                    FIELD(temp_s0_2, s16, 0x48) = 5;
                    FIELD(temp_s0_2, u16, 0x18) = temp_v1;
                    temp_v1 = FIELD(temp_s1, u16, 0x14);
                    FIELD(temp_s1, s16, 0x1E) = 0x1000;
                    FIELD(temp_s1, s16, 0x1C) = 0x1000;
                    FIELD(temp_s1, s16, 0x10) = 0x60;
                    FIELD(temp_s1, void *, 0) = temp_fp;
                    FIELD(temp_s1, u16, 0x14) = temp_v1 | 0xC;
                    temp_v0 = FIELD(temp_fp, s32, 4);
                    temp_a0 |= 0xC0C0;
                    FIELD(temp_s1, s8, 4) = 0;
                    FIELD(temp_s1, s8, 5) = 0;
                    FIELD(temp_s1, s32, 0xC) = temp_a0;
                    FIELD(temp_s1, s32, 8) = temp_v0;
                }
                var_s2--;
            } while (var_s2 >= 0);
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto L_end;
        }
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25));
        func_800AD594(arg3_reg, 0x100);
        FIELD(arg0, void *, 0x8C) = D_80171138;
        D_8008346C = 0;
        FIELD(arg2, void *, 0x2C) = D_80174AD4;
        temp_v0 = (D_80083228 + FIELD(arg3_reg, s16, 0x2A) + 0x100) >> 9;
        func_80047784(arg2, D_80174AD4[temp_v0 & 7], 0);
        func_800A4ACC(arg3_reg);
        if (FIELD(arg3_reg, s8, 0x6D) == 0) {
            FIELD(arg3_reg, u16, 0x46) &= 0x7FFF;
            goto L_end;
        }
        temp_v1 = (s32)((u8 *)&D_800E3DE8 - 0x3DE8);
        temp_v0 = (s32)((u8 *)arg3_reg - 0x20);
        FIELD((void *)temp_v1, void *, 0x3DE8) = (void *)temp_v0;
        goto L_end;

    default:
        goto L_end;
    }

L_end:
    return;
}
