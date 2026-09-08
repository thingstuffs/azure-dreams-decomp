#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172494_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172494_0;   /* arg3_reg in func_80172494 */

typedef struct S_80172494_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172494_1;   /* arg0 in func_80172494 */


typedef struct S_80172494_3 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172494_3;   /* arg1 in func_80172494 */

typedef struct S_80172494_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80172494_4;   /* temp_v0_2 in func_80172494 */

typedef struct S_80172494_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u8 pad_1A[0x2E];
    s16 unk_48;
} S_80172494_5;   /* temp_s0_2 in func_80172494 */

typedef struct S_80172494_6 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172494_6;   /* temp_s1 in func_80172494 */

typedef struct S_80172494_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172494_7;   /* temp_fp in func_80172494 */

typedef struct S_80172494_8 {
    u8 pad_00[0x3DE8];
    void * unk_3DE8;
} S_80172494_8;   /* (void *)temp_v1 in func_80172494 */



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
    register s32 temp_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 temp_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v0_3;
    s32 temp_v0_4;
    register s32 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_s2;
    s32 state;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_v0_2;
    u8 *temp_fp;
    register void *arg3_reg ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *table0;
    u8 *table6;

    arg3_reg = arg3;
    var_s2 = ((S_80172494_0 *)arg3_reg)->unk_2A.s >> 8;
    temp_a0 = var_s2 & 0xE;
    table0 = (u8 *)&D_8006CCD8;
    table0 += temp_a0;
    table6 = (u8 *)&D_8006CCE8;
    temp_s0 = *(s16 *)table0;
    temp_s6 = *(s16 *)(table6 + temp_a0);
    state = ((S_80172494_1 *)arg0)->unk_9B;
    ((S_80172494_1 *)arg0)->unk_96.s = ((S_80172494_1 *)arg0)->unk_96.s - 1;

    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172494_1 *)arg0)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(arg3_reg, arg2, ((S_80172494_0 *)arg3_reg)->unk_2A.u, 1);
            goto L_end;
        }
        temp_a0 = 0xF7FFFFFF;
        temp_v1 = 0xFFFBFFFF;
        temp_v0 = -temp_s0;
        temp_v0 <<= 18;
        ((S_80172494_3 *)arg1)->unk_0C = temp_v0;
        temp_v0 = -temp_s6;
        temp_v0 <<= 18;
        ((S_80172494_3 *)arg1)->unk_10 = temp_v0;
        ((S_80172494_1 *)arg0)->unk_98 |= 8;
        temp_v0 = ((S_80172494_0 *)arg3_reg)->unk_1C;
        temp_v0 &= temp_a0;
        temp_v0 &= temp_v1;
        ((S_80172494_0 *)arg3_reg)->unk_1C = temp_v0;
        ((S_80172494_1 *)arg0)->unk_96.s = 4;
        ((S_80172494_3 *)arg1)->unk_14 = 0xFFFD0000;
        goto L_inc_load;

    case 1:
        temp_v0 = ((S_80172494_3 *)arg1)->unk_14;
        ((S_80172494_3 *)arg1)->unk_14 = temp_v0 + (temp_v0 >> 2);
        if (((S_80172494_1 *)arg0)->unk_96.u > 0) {
            goto L_end;
        }
        temp_v0 = ((S_80172494_1 *)arg0)->unk_9B;
        ((S_80172494_1 *)arg0)->unk_96.s = 8;
        goto L_inc_after_load;

    case 2:
        temp_v0_3 = ((S_80172494_3 *)arg1)->unk_0C;
        temp_v1 = ((S_80172494_3 *)arg1)->unk_10;
        ((S_80172494_3 *)arg1)->unk_0C = temp_v0_3 - (temp_v0_3 >> 3);
        temp_v0_4 = ((S_80172494_3 *)arg1)->unk_14;
        ((S_80172494_3 *)arg1)->unk_10 = temp_v1 - (temp_v1 >> 3);
        ((S_80172494_3 *)arg1)->unk_14 = temp_v0_4 - (temp_v0_4 >> 3);
        if ((((S_80172494_1 *)arg0)->unk_96.u == 4) ||
            (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            ((S_80172494_3 *)arg1)->unk_0C = 0;
            ((S_80172494_3 *)arg1)->unk_10 = 0;
            ((S_80172494_3 *)arg1)->unk_14 = 0;
            (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AE4;
            temp_v0 = (D_80083228 + ((S_80172494_0 *)arg3_reg)->unk_2A.u + 0x100) >> 9;
            func_80047784(arg2, D_80174AE4[temp_v0 & 7], 0);
        }
        if (((S_80172494_1 *)arg0)->unk_96.u > 0) {
            goto L_end;
        }
        if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto L_end;
        }
        ((S_80172494_1 *)arg0)->unk_96.s = 4;
        ((S_80172494_3 *)arg1)->unk_0C = (temp_s0 << 18) + (temp_s0 << 17);
        ((S_80172494_3 *)arg1)->unk_10 = (temp_s6 << 18) + (temp_s6 << 17);
        func_800A56E0(0x80E);
        ASM_USE(temp_s6);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        goto L_inc_load;

    case 3:
        ((S_80172494_1 *)arg0)->unk_90 += 0x80000;
        ((S_80172494_3 *)arg1)->unk_0C += temp_s0 << 18;
        ((S_80172494_3 *)arg1)->unk_10 += temp_s6 << 18;
        ASM_USE(temp_s6);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (((S_80172494_1 *)arg0)->unk_96.u > 0) {
            goto L_end;
        }
        func_800A56E0(0x808);
        func_8009C12C(arg3_reg, arg2, ((S_80172494_0 *)arg3_reg)->unk_2A.u, 1);

L_inc_load:
        temp_v0 = ((S_80172494_1 *)arg0)->unk_9B;
L_inc_after_load:
        ((S_80172494_1 *)arg0)->unk_9B = temp_v0 + 1;
        goto L_end;

    case 4:
        ((S_80172494_1 *)arg0)->unk_90 += 0x80000;
        if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto L_end;
        }
        ((S_80172494_3 *)arg1)->unk_14 = 0;
        ((S_80172494_1 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172494_0 *)arg3_reg)->unk_1C |= 0x40000;
        ((S_80172494_0 *)arg3_reg)->unk_1C |= 0x08000000;
        ((S_80172494_1 *)arg0)->unk_96.s = state;
        ((S_80172494_1 *)arg0)->unk_9B = 0xFF;
        goto L_end;

    case 0xFF:
        temp_v0 = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        temp_v1 = ((S_80172494_3 *)arg1)->unk_02.s - 0x20;
        temp_v0 -= temp_v1;
        temp_v0 = (temp_v0 << 15) >> 1;
        ((S_80172494_3 *)arg1)->unk_0C = temp_v0;
        ASM_USE(temp_v0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v0 = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        temp_v1 = ((S_80172494_3 *)arg1)->unk_06.s - 0x20;
        temp_v0 -= temp_v1;
        temp_v0 = (temp_v0 << 15) >> 1;
        ((S_80172494_3 *)arg1)->unk_10 = temp_v0;
        if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) &&
            (((S_80172494_1 *)arg0)->unk_96.u != 0)) {
            var_s2 = 9;
            sp10 = temp_s0 * 0x28;
            temp_fp = D_800DEC28;
            do {
                temp_v0_2 = func_8003FD64(0x312, &D_80083498);
                if (temp_v0_2 != NULL) {
                    func_8004491C(temp_v0_2, &D_80045340);
                    temp_s0_2 = (u8 *)temp_v0_2 + 0x20;
                    ((S_80172494_4 *)temp_v0_2)->unk_10 = D_80173F0C;
                    temp_s1 = ((S_80172494_4 *)temp_v0_2)->unk_0C;
                    ((S_80172494_5 *)temp_s0_2)->unk_0C =
                        ((S_80172494_3 *)arg1)->unk_02.u - sp10;
                    ((S_80172494_5 *)temp_s0_2)->unk_0E =
                        ((S_80172494_3 *)arg1)->unk_06.u - (temp_s6 * 0x28);
                    ((S_80172494_5 *)temp_s0_2)->unk_10 = ((S_80172494_3 *)arg1)->unk_0A;
                    ((S_80172494_5 *)temp_s0_2)->unk_04 = rand() & 0xF;
                    ((S_80172494_5 *)temp_s0_2)->unk_06 = 0;
                    ((S_80172494_5 *)temp_s0_2)->unk_08 = (rand() & 0xF) + 8;
                    temp_v0 = rand();
                    temp_a0 = 0xC00000;
                    ((S_80172494_5 *)temp_s0_2)->unk_14 = temp_v0;
                    temp_v1 = ((S_80172494_0 *)arg3_reg)->unk_2A.s;
                    ((S_80172494_5 *)temp_s0_2)->unk_48 = 5;
                    ((S_80172494_5 *)temp_s0_2)->unk_18 = temp_v1;
                    temp_v1 = ((S_80172494_6 *)temp_s1)->unk_14;
                    ((S_80172494_6 *)temp_s1)->unk_1E = 0x1000;
                    ((S_80172494_6 *)temp_s1)->unk_1C = 0x1000;
                    ((S_80172494_6 *)temp_s1)->unk_10 = 0x60;
                    ((S_80172494_6 *)temp_s1)->unk_00 = temp_fp;
                    ((S_80172494_6 *)temp_s1)->unk_14 = temp_v1 | 0xC;
                    temp_v0 = ((S_80172494_7 *)temp_fp)->unk_04;
                    temp_a0 |= 0xC0C0;
                    ((S_80172494_6 *)temp_s1)->unk_04 = 0;
                    ((S_80172494_6 *)temp_s1)->unk_05 = 0;
                    ((S_80172494_6 *)temp_s1)->unk_0C = temp_a0;
                    ((S_80172494_6 *)temp_s1)->unk_08 = temp_v0;
                }
                var_s2--;
            } while (var_s2 >= 0);
        }
        if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            goto L_end;
        }
        ((S_80172494_3 *)arg1)->unk_10 = 0;
        ((S_80172494_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24,
                      ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3_reg, 0x100);
        ((S_80172494_1 *)arg0)->unk_8C = D_80171138;
        D_8008346C = 0;
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AD4;
        temp_v0 = (D_80083228 + ((S_80172494_0 *)arg3_reg)->unk_2A.u + 0x100) >> 9;
        func_80047784(arg2, D_80174AD4[temp_v0 & 7], 0);
        func_800A4ACC(arg3_reg);
        if (((S_80172494_0 *)arg3_reg)->unk_6D == 0) {
            ((S_80172494_0 *)arg3_reg)->unk_46 &= 0x7FFF;
            goto L_end;
        }
        temp_v1 = (s32)((u8 *)&D_800E3DE8 - 0x3DE8);
        temp_v0 = (s32)((u8 *)arg3_reg - 0x20);
        ((S_80172494_8 *)((void *)temp_v1))->unk_3DE8 = (void *)temp_v0;
        goto L_end;

    default:
        goto L_end;
    }

L_end:
    return;
}
