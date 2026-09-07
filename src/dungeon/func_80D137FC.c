#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172FFC_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FFC_0;   /* arg0 in func_80172FFC */



typedef struct S_80172FFC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FFC_3;   /* arg1 in func_80172FFC */

typedef struct S_80172FFC_4 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x8];
    void * unk_A8;
    u8 pad_AC[0x8];
    s32 unk_B4;
} S_80172FFC_4;   /* temp_s2 in func_80172FFC */

typedef struct S_80172FFC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80172FFC_5;   /* temp_v0_3 in func_80172FFC */

typedef struct S_80172FFC_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80172FFC_6;   /* temp_s1 in func_80172FFC */

typedef struct S_80172FFC_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FFC_7;   /* temp_s0 in func_80172FFC */

typedef struct S_80172FFC_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80172FFC_8;   /* sp50 in func_80172FFC */

typedef struct S_80172FFC_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80172FFC_9;   /* temp_a1_2 in func_80172FFC */

typedef struct S_80172FFC_10 {
    s16 unk_00;
    u16 unk_02;
} S_80172FFC_10;   /* &sp60[((u16) ((S_80172FFC_4 *)temp_s2)->unk_94 >> 7) & 0x1C] in func_80172FFC */


typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Packed32;

typedef struct {
    s64 out18;
    Packed32 copy;
} WorkMid;

typedef struct {
    s32 words[4];
} Copy16;

s32 func_8003DE58();     /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C(); /* extern */
M2C_UNK func_80047784();         /* extern */
s32 func_80065420(); /* extern */
s32 rand();                                /* extern */
M2C_UNK func_8009C12C(); /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
void func_800AD594(void *, s32);  /* extern */
void func_801731C8(void);  /* extern */
void func_80173618(void); /* extern */
extern M2C_UNK D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern s8 D_800DCECC[];
extern Packed32 D_80170838;
extern M2C_UNK D_80170874;
extern M2C_UNK D_80171760;
extern u8 D_80174E90[];
extern u8 D_80174EB8[];
extern u8 D_80174EC0;

void func_80172FFC(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp10[3];
    u16 sp18[3];
    WorkMid mid;
    M2C_UNK sp48;
    M2C_UNK sp4C;
    void *sp50;
    u16 sp58;                                       /* compiler-managed */
    u8 *sp60;
    u16 *sp64;
    M2C_UNK *sp68;
    M2C_UNK temp_a0;
    M2C_UNK temp_a1;
    s16 temp_v0_2;
    s32 temp_v0_4;
    s32 random_value;
    s32 base_value;
    register s32 final_value ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    u16 temp_v0;
    u16 temp_v0_5;
    u16 temp_v1_2;
    u8 table_byte;
    s32 temp_v1;
    void *temp_a1_2;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0_3;
    Copy16 *var_a2;
    Copy16 *var_a3;
    Copy16 *copy_end;
    Packed32 *copy_source = &D_80170838;

    mid.copy = *copy_source;
    sp50 = arg0 - 0x20;
    temp_v1 = ((S_80172FFC_0 *)arg0)->unk_9B;
    if (temp_v1 == 1) {
        goto state1;
    }
    if ((s32) temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state0;
        }
        goto done;
    }
    if (temp_v1 == 2) {
        goto state2;
    }
    if (temp_v1 == 3) {
        goto state3;
    }
    goto done;

state0:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172FFC_0 *)arg0)->unk_9B = 3U;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x6000);
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        goto done;
    }
    ((S_80172FFC_3 *)arg1)->unk_14 = 0;
    ((S_80172FFC_3 *)arg1)->unk_10 = 0;
    ((S_80172FFC_3 *)arg1)->unk_0C = 0;
    goto advance;

state1:
    temp_v0_5 = ((S_80172FFC_0 *)arg0)->unk_96 + 1;
    ((S_80172FFC_0 *)arg0)->unk_96 = temp_v0_5;
    if (((s16) temp_v0_5 != 4) && !(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_80174EB8;
    func_80047784(arg2, D_80174EB8[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);

advance:
    ASM_KEEP_NV(arg0);   /* MATCH pin: load-bearing for the whole function shape */
    ((S_80172FFC_0 *)arg0)->unk_96 = 0U;
    ((S_80172FFC_0 *)arg0)->unk_9B = (u8) (((S_80172FFC_0 *)arg0)->unk_9B + 1);
    goto done;

state2:
            temp_v0 = ((S_80172FFC_0 *)arg0)->unk_96 + 1;
            ((S_80172FFC_0 *)arg0)->unk_96 = temp_v0;
            if (((s16) temp_v0 == 0x11) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
                ((S_80172FFC_0 *)arg0)->unk_96 = 0U;
                ((S_80172FFC_0 *)arg0)->unk_9B = (u8) (((S_80172FFC_0 *)arg0)->unk_9B + 1);
            }
            if (((s16) ((S_80172FFC_0 *)arg0)->unk_96 == 0xB) || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
                func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
            }
            if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
                (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_80174E90;
                func_80047784(arg2, D_80174E90[((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            }
            temp_v1_2 = ((S_80172FFC_0 *)arg0)->unk_96;
            if ((u32) (temp_v1_2 - 9) < 5U) {
                if ((s16) temp_v1_2 == 9) {
                    func_800A56E0(0x810);
                }
                sp60 = (u8 *)&mid.copy;
                sp64 = &sp18;
                sp58 = 0;
                sp68 = (M2C_UNK *)&mid.out18;
                do {
                    temp_v0_3 = func_8003FD64(0x112, &D_80083498);
                    temp_s2 = temp_v0_3 + 0x20;
                    if (temp_v0_3 != NULL) {
                        ((S_80172FFC_4 *)temp_s2)->unk_96 = 0x19;
                        ((S_80172FFC_4 *)temp_s2)->unk_9E = 0x19;
                        ((S_80172FFC_5 *)temp_v0_3)->unk_10 = &D_80170874;
                        ((S_80172FFC_4 *)temp_s2)->unk_A8 = arg1;
                        var_a3 = (Copy16 *)arg2;
                        copy_end = (Copy16 *)arg2 + 3;
                        ((S_80172FFC_4 *)temp_s2)->unk_94 = (u16) ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16;
                        temp_s1 = ((S_80172FFC_5 *)temp_v0_3)->unk_0C;
                        var_a2 = (Copy16 *)temp_s1;
                        do {
                            *var_a2 = *var_a3;
                            var_a3++;
                            var_a2++;
                        } while (var_a3 != copy_end);
                        ((S_80172FFC_6 *)temp_s1)->unk_1E = 0;
                        ((S_80172FFC_6 *)temp_s1)->unk_1C = 0;
                        ((S_80172FFC_6 *)temp_s1)->unk_0E = 0x80;
                        ((S_80172FFC_6 *)temp_s1)->unk_0D = 0x80;
                        ((S_80172FFC_6 *)temp_s1)->unk_0C = 0x80;
                        func_8004491C(temp_v0_3, &D_80045340, var_a2, var_a3);
                        table_byte = D_80174EC0;
                        ((S_80172FFC_6 *)temp_s1)->unk_2C = &D_80174EC0;
                        func_80047784(temp_s1, table_byte, 0);
                        temp_s0 = ((S_80172FFC_5 *)temp_v0_3)->unk_08;
                        ((S_80172FFC_7 *)temp_s0)->unk_02 = (u16) ((S_80172FFC_3 *)arg1)->unk_02;
                        ((S_80172FFC_7 *)temp_s0)->unk_06 = (u16) ((S_80172FFC_3 *)arg1)->unk_06;
                        ((S_80172FFC_7 *)temp_s0)->unk_0A = (u16) ((S_80172FFC_3 *)arg1)->unk_0A;
                        temp_a1_2 = ((S_80172FFC_8 *)sp50)->unk_0C;
                        if (func_8003DE58(((S_80172FFC_9 *)temp_a1_2)->unk_08, temp_a1_2, sp10, 0) != 0) {
                            ((S_80172FFC_7 *)temp_s0)->unk_02 = (u16) (((S_80172FFC_7 *)temp_s0)->unk_02 + sp10[0]);
                            ((S_80172FFC_7 *)temp_s0)->unk_06 = (u16) (((S_80172FFC_7 *)temp_s0)->unk_06 + sp10[1]);
                            ((S_80172FFC_7 *)temp_s0)->unk_0A = (u16) (((S_80172FFC_7 *)temp_s0)->unk_0A + sp10[2]);
                        }
                        ((S_80172FFC_7 *)temp_s0)->unk_14 = (s32) (((0xD - (s16) ((S_80172FFC_0 *)arg0)->unk_96) << 0x11) + 0xFFE80000);
                        ((S_80172FFC_4 *)temp_s2)->unk_B4 = 0xC000;
                        ((S_80172FFC_7 *)temp_s0)->unk_0C = (s32) (((S_80172FFC_10 *)(&sp60[((u16) ((S_80172FFC_4 *)temp_s2)->unk_94 >> 7) & 0x1C]))->unk_00 << 0x11);
                        ((S_80172FFC_7 *)temp_s0)->unk_10 = (s32) (((S_80172FFC_10 *)(&sp60[((u16) ((S_80172FFC_4 *)temp_s2)->unk_94 >> 7) & 0x1C]))->unk_02 << 0x11);
                        random_value = rand();
                        base_value = ((S_80172FFC_7 *)temp_s0)->unk_0C + 0xFFFE0000;
                        base_value += (random_value & 0x3FFF) << 4;
                        ((S_80172FFC_7 *)temp_s0)->unk_0C = base_value;
                        random_value = rand();
                        base_value = ((S_80172FFC_7 *)temp_s0)->unk_10 + 0xFFFE0000;
                        base_value += (random_value & 0x3FFF) << 4;
                        ((S_80172FFC_7 *)temp_s0)->unk_10 = base_value;
                        random_value = rand();
                        base_value = 0xFFF80000;
                        final_value = ((S_80172FFC_7 *)temp_s0)->unk_14;
                        final_value += base_value;
                        final_value += (random_value & 0x3FFF) << 6;
                        ((S_80172FFC_7 *)temp_s0)->unk_14 = final_value;
                        sp18[0] = ((S_80172FFC_7 *)temp_s0)->unk_02;
                        sp18[1] = ((S_80172FFC_7 *)temp_s0)->unk_06;
                        sp18[2] = ((S_80172FFC_7 *)temp_s0)->unk_0A;
                        temp_v0_4 = func_80065420(sp64, sp68, &sp48, &sp4C);
                        sp18[0] = ((S_80172FFC_3 *)arg1)->unk_02;
                        sp18[1] = ((S_80172FFC_3 *)arg1)->unk_06;
                        sp18[2] = ((S_80172FFC_3 *)arg1)->unk_0A;
                        ((S_80172FFC_6 *)temp_s1)->unk_06 = (s16) ((temp_v0_4 - func_80065420(sp64, sp68, &sp48, &sp4C)) - (D_800DCECC[((s32) (D_80083228 + (s16) ((S_80172FFC_4 *)temp_s2)->unk_94 + 0x100) >> 9) & 7] * 2));
                    }
                    temp_v0_2 = sp58 + 1;
                    sp58 = temp_v0_2;
                } while (temp_v0_2 < 2);
            }
    goto done;

state3:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_80172FFC_0 *)arg0)->unk_8C = &D_80171760;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x7FFF);
    }

done:
    return;
}
