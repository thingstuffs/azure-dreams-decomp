#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80088A58[];
s32 func_8003E4FC(); /* extern */
void func_800424E0();          /* extern */
void func_80042560();                      /* extern */
M2C_UNK func_80042640();                  /* extern */
void func_80043914();                      /* extern */
M2C_UNK func_80047FF4();                     /* extern */
s32 func_80048118();                   /* extern */
void func_80048A44(); /* extern */
M2C_UNK func_80093C70();      /* extern */
M2C_UNK func_80093D8C();      /* extern */
M2C_UNK func_80093E74(); /* extern */
s32 func_800990FC();                         /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_8009929C();                    /* extern */
s32 func_80099734();                     /* extern */
M2C_UNK func_80099F04();                         /* extern */
M2C_UNK func_80099F70();                         /* extern */
M2C_UNK func_8009A028();                      /* extern */
void *(*func_800A0B94())(M2C_UNK, s8, s8, s16); /* extern */
M2C_UNK func_800A152C();                 /* extern */
s32 func_800A1618();                     /* extern */
M2C_UNK func_800A18E8();                 /* extern */
s32 func_800A2BDC();                         /* extern */
M2C_UNK func_800A31D0();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_8003E140;
extern s32 D_80081488;
extern M2C_UNK D_8008149C;
extern M2C_UNK D_800814A0;
extern void *D_80082EB0[];
extern s16 D_80083228;
extern u16 D_80083460[];
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern u8 D_800DD260;
extern M2C_UNK D_800DD262;
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E06FA;
extern M2C_UNK D_800E0714;
extern s32 D_800E3D74[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

typedef union ScratchS1 {
    s32 value;
    void **base;
} ScratchS1;


typedef struct S_8009345C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8009345C_0;   /* actor in func_8009345C */

typedef struct S_8009345C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8009345C_1;   /* entity in func_8009345C */

typedef struct S_8009345C_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8009345C_2;   /* ctx in func_8009345C */

typedef struct S_8009345C_3 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009345C_3;   /* ((temp_idx * 4) + actor) in func_8009345C */

typedef struct S_8009345C_4 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
} S_8009345C_4;   /* &D_800DD262 in func_8009345C */

typedef struct S_8009345C_5_pre {
    u16 unk_00;
} S_8009345C_5_pre;   /* the 0x2 bytes before temp_v1_2 in func_8009345C, addressed as temp_v1_2[-1] */

typedef struct S_8009345C_6 {
    s32 unk_00;
} S_8009345C_6;   /* &D_800814A0 in func_8009345C */

typedef struct S_8009345C_7 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_8009345C_7;   /* *scratch_s1.base in func_8009345C */

typedef struct S_8009345C_8 {
    u8 unk_00;
} S_8009345C_8;   /* &D_800E3E40 in func_8009345C */

typedef struct S_8009345C_9 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_8009345C_9;   /* D_80082EB0[0] in func_8009345C */

typedef struct S_8009345C_10_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_8009345C_10_pre;   /* the 0x18 bytes before temp_v0_5 in func_8009345C, addressed as temp_v0_5[-1] */

typedef struct S_8009345C_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_8009345C_10;   /* temp_v0_5 in func_8009345C */

typedef struct S_8009345C_11 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009345C_11;   /* temp_v1_3 in func_8009345C */

typedef struct S_8009345C_12 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009345C_12;   /* temp_v1_4 in func_8009345C */

typedef struct S_8009345C_13 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8009345C_13;   /* map in func_8009345C */

typedef struct S_8009345C_14 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_8009345C_14;   /* ((temp_slot * 4) + actor) in func_8009345C */

typedef struct S_8009345C_15 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_8009345C_15;   /* ((S_8009345C_2 *)ctx)->unk_60 in func_8009345C */

typedef struct S_8009345C_16 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8009345C_16;   /* ((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor) in func_8009345C */

void func_8009345C(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *actor = arg0;
    void *map = arg1;
    void *entity = arg2;
    register void *ctx ASM_REG("$19") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    M2C_UNK *var_a0;
    M2C_UNK *var_a0_2;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_object_flags;
    s32 cleanup_slot;
    s32 var_a1;
    u16 temp_v0;
    u16 temp_v0_7;
    u16 temp_flags;
    u16 temp_raw;
    s16 temp_idx;
    s32 temp_slot;
    u8 temp_v1;
    register u8 var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *temp_v0_5;
    void *temp_case0_ptr;
    void *temp_case2_ptr;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    ScratchS1 scratch_s1;

    temp_v1 = ((S_8009345C_0 *)actor)->unk_9B;
    if (temp_v1 >= 0xAU) {
        goto block_36;
    }
    (void)jt_keep; goto *D_80088A58[(u32)(temp_v1)];
jt_c0:
    if (!(((S_8009345C_1 *)entity)->unk_14 & 0x6000)) {
        goto block_36;
    }
    (*(void **)((u8 *)entity + (0x2C))) = D_800DD138;
    func_80048A44(entity, D_800DD138[((s32) (D_80083228 + ((S_8009345C_2 *)ctx)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    func_80093C70(actor, map, entity);
    func_80093D8C(actor, map, entity);
    temp_flags = ((S_8009345C_1 *)entity)->unk_14;
    D_800DD260 = 0;
    ((S_8009345C_1 *)entity)->unk_14 = (u16) (temp_flags | 0x200);
    ((S_8009345C_0 *)actor)->unk_96 = 0x10U;
    temp_idx = ((S_8009345C_2 *)ctx)->unk_8A.s;
    temp_raw = ((S_8009345C_2 *)ctx)->unk_8A.u;
    temp_case0_ptr = (void *) ((S_8009345C_3 *)(((temp_idx * 4) + actor)))->unk_AC;
    ((S_8009345C_4 *)(&D_800DD262))->unk_00.u = temp_raw;
    ((S_8009345C_2 *)ctx)->unk_60 = temp_case0_ptr;
    goto block_33;
jt_c1:
    temp_v0 = ((S_8009345C_0 *)actor)->unk_96 - 1;
    ((S_8009345C_0 *)actor)->unk_96 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_36;
    }
    if (((S_8009345C_2 *)ctx)->unk_60 == NULL) {
        goto block_7;
    }
    func_80093E74(actor, map, entity, ctx);
    goto block_33;
block_7:
    var_v0 = ((S_8009345C_0 *)actor)->unk_9B + 2;
    goto block_35;
jt_c2:
    if (!(((S_8009345C_15 *)(((S_8009345C_2 *)ctx)->unk_60))->unk_1C & 0x800000)) {
        goto block_36;
    }
    scratch_s1.value = func_800990FC();
    temp_a1 = func_8009929C(8, scratch_s1.value);
    if (((S_8009345C_4 *)(&D_800DD262))->unk_00.s == 0) {
        goto block_11;
    }
    var_a0 = &D_800E05F0;
    goto block_12;
block_11:
    var_a0 = &D_800E05E1;
block_12:
    func_80099290(func_80099194(&D_800E06FA, func_80099734(((S_8009345C_2 *)ctx)->unk_60, func_80099194(var_a0, temp_a1))));
    func_800A5720(scratch_s1.value);
    temp_case2_ptr = ((S_8009345C_2 *)ctx)->unk_60;
    D_800DD260 = 1;
    func_800A31D0(temp_case2_ptr);
    ((S_8009345C_16 *)(((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor)))->unk_AC = 0;
    func_800A18E8(((S_8009345C_15 *)(((S_8009345C_2 *)ctx)->unk_60))->unk_13, 3);
    func_8009A028(((S_8009345C_2 *)ctx)->unk_60);
    temp_v1_2 = ((S_8009345C_2 *)ctx)->unk_60;
    ((S_8009345C_5_pre *)temp_v1_2)[-1].unk_00 = (u16) (((S_8009345C_5_pre *)temp_v1_2)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_8009345C_6 *)(&D_800814A0))->unk_00 | 0x8000);
    if (D_80082EB0[0] != NULL) {
        goto block_33;
    }
    ((S_8009345C_0 *)actor)->unk_96 = 0U;
    var_v0 = ((S_8009345C_0 *)actor)->unk_9B + 4;
    goto block_35;
jt_c3:
    scratch_s1.base = D_80082EB0;
    if ((func_800A2BDC(0) << 0x10) != 0) {
        goto block_36;
    }
    temp_v0_3 = func_800A1618(((S_8009345C_7 *)(*scratch_s1.base))->unk_00, 3);
    if (temp_v0_3 == 0) {
        goto block_33;
    }
    D_80081488 = func_80048118(((S_8009345C_7 *)(*scratch_s1.base))->unk_00, &D_8008149C);
    func_800A0B94(((S_8009345C_7 *)(*scratch_s1.base))->unk_00, temp_v0_3, 0);
    (*(s8 *)&D_800E3E40) = 0;
    func_8003E4FC(0xFF, &D_8003E140, &D_800E3E40);
    goto block_33;
jt_c4:
    if (((S_8009345C_8 *)(&D_800E3E40))->unk_00 == 0) {
        goto block_36;
    }
    if (D_80081488 == 0) {
        goto block_33;
    }
    func_80047FF4(((S_8009345C_9 *)(D_80082EB0[0]))->unk_00, D_80081488);
    goto block_33;
jt_c5:
    scratch_s1.base = D_80082EB0;
    temp_v0_4 = func_800A1618(((S_8009345C_7 *)(*scratch_s1.base))->unk_00, 3);
    if (temp_v0_4 == 0) {
        goto block_28;
    }
    func_80043914(*scratch_s1.base);
    temp_v0_5 = func_800A0B94(((S_8009345C_7 *)(*scratch_s1.base))->unk_00, temp_v0_4, 1)(1, ((S_8009345C_2 *)ctx)->unk_72, ((S_8009345C_2 *)ctx)->unk_73, (s16) (((S_8009345C_2 *)ctx)->unk_88 - 0x20));
    if (temp_v0_5 == NULL) {
        goto block_28;
    }
    (*(void **)((u8 *)(((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor)) + (0xAC))) = temp_v0_5;
    D_800E3DF0[((S_8009345C_7 *)(*scratch_s1.base))->unk_03 & 0x1F] = temp_v0_5;
    temp_v1_3 = ((S_8009345C_10_pre *)temp_v0_5)[-1].unk_04;
    ((S_8009345C_11 *)temp_v1_3)->unk_1E = 0x800;
    ((S_8009345C_11 *)temp_v1_3)->unk_1C = 0x800;
    temp_v1_4 = ((S_8009345C_10_pre *)temp_v0_5)[-1].unk_00;
    ((S_8009345C_12 *)temp_v1_4)->unk_02 = (u16) ((S_8009345C_13 *)map)->unk_02;
    ((S_8009345C_12 *)temp_v1_4)->unk_06 = (u16) ((S_8009345C_13 *)map)->unk_06;
    ((S_8009345C_12 *)temp_v1_4)->unk_0A = (s16) (((S_8009345C_13 *)map)->unk_0A - 0x10);
    func_80042640(temp_v0_5, ((S_8009345C_10 *)temp_v0_5)->unk_13);
    func_800424E0(temp_v0_5, ((S_8009345C_10 *)temp_v0_5)->unk_13, *scratch_s1.base);
    temp_object_flags = ((S_8009345C_10 *)temp_v0_5)->unk_1C;
    temp_slot = ((S_8009345C_4 *)(&D_800DD262))->unk_00.s;
    ((S_8009345C_10 *)temp_v0_5)->unk_1C = temp_object_flags | 0x02000000;
    ((S_8009345C_14 *)(((temp_slot * 4) + actor)))->unk_D0 = D_80082EB0[0];
    ((S_8009345C_9 *)(D_80082EB0[0]))->unk_03 = (u8) (((S_8009345C_9 *)(D_80082EB0[0]))->unk_03 | 0x20);
    scratch_s1.value = func_800990FC(0x02000000);
    var_a1 = scratch_s1.value;
    if (D_800DD260 != 0) {
        goto block_24;
    }
    var_a1 = func_8009929C(8, var_a1);
block_24:
    if (((S_8009345C_4 *)(&D_800DD262))->unk_00.s == 0) {
        goto block_26;
    }
    var_a0_2 = &D_800E05F0;
    goto block_27;
block_26:
    var_a0_2 = &D_800E05E1;
block_27:
    func_80099290(func_80099194(&D_800E0714, func_80099734(temp_v0_5, func_80099194(var_a0_2, var_a1))));
    func_800A5720(scratch_s1.value);
    cleanup_slot = ((S_8009345C_4 *)(&D_800DD262))->unk_00.s;
    D_800E3D74[cleanup_slot] = 0;
    func_800A152C(((S_8009345C_9 *)(D_80082EB0[0]))->unk_00, 3);
    func_80042560(temp_v0_5);
    func_800A56E0(0x704);
block_28:
    var_v0 = ((S_8009345C_0 *)actor)->unk_9B;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    ((S_8009345C_0 *)actor)->unk_96 = 0x10U;
    goto block_34;
jt_c7:
    temp_v0_7 = ((S_8009345C_0 *)actor)->unk_96 - 1;
    ((S_8009345C_0 *)actor)->unk_96 = temp_v0_7;
    if ((temp_v0_7 << 0x10) > 0) {
        goto block_36;
    }
    (*(void **)((u8 *)entity + (0x2C))) = D_800DD140;
    func_80048A44(entity, D_800DD140[((s32) (D_80083228 + ((S_8009345C_2 *)ctx)->unk_2A + 0x100) >> 9) & 7], 0, 1);
    goto block_33;
jt_c8:
    if (!(((S_8009345C_1 *)entity)->unk_14 & 0x6000)) {
        goto block_36;
    }
    ((S_8009345C_0 *)actor)->unk_8C = &D_8008ACDC;
    func_80099F70(((S_8009345C_2 *)ctx)->unk_5C);
    func_80099F04(((S_8009345C_2 *)ctx)->unk_5C);
    D_80083460[1] = (u16) (D_80083460[1] | 0x812);
    ((S_8009345C_1 *)entity)->unk_14 = (u16) (((S_8009345C_1 *)entity)->unk_14 & 0xFDFF);
jt_c6:
block_33:
    var_v0 = ((S_8009345C_0 *)actor)->unk_9B;
block_34:
    var_v0 = var_v0 + 1;
block_35:
    ((S_8009345C_0 *)actor)->unk_9B = var_v0;
block_36:
    return;
}
