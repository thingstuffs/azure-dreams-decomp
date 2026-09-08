#include "common.h"
#include "m2c_compat.h"

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct S_80024B54_0_pre {
    u16 unk_00;
} S_80024B54_0_pre;   /* the 0x2 bytes before arg0 in func_80024B54, addressed as arg0[-1] */

typedef struct S_80024B54_0 {
    s32 unk_00;
    u16 * unk_04;
    u8 unk_08;
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    s16 unk_1A;
} S_80024B54_0;   /* arg0 in func_80024B54 */

typedef struct S_80024B54_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024B54_1_pre;   /* the 0x14 bytes before temp_v1_2 in func_80024B54, addressed as temp_v1_2[-1] */

typedef struct S_80024B54_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    s16 unk_88;
    u8 pad_8A[0x1C];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x4B];
    s32 unk_F4;
    u8 pad_F8[0x13B0];
    void * unk_14A8;
} S_80024B54_1;   /* temp_v1_2 in func_80024B54 */

typedef struct S_80024B54_2 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_80024B54_2;   /* case1_page in func_80024B54 */

typedef struct S_80024B54_3 {
    u8 pad_00[0x14A8];
    void * unk_14A8;
} S_80024B54_3;   /* case2_page in func_80024B54 */

typedef struct S_80024B54_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80024B54_4;   /* table_s5 in func_80024B54 */

typedef struct S_80024B54_5 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80024B54_5;   /* temp_a0 in func_80024B54 */

typedef struct S_80024B54_6_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
} S_80024B54_6_pre;   /* the 0x18 bytes before temp_v0_3 in func_80024B54, addressed as temp_v0_3[-1] */

typedef struct S_80024B54_7 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
} S_80024B54_7;   /* var_s1 in func_80024B54 */

typedef struct S_80024B54_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024B54_8;   /* held_arg1 in func_80024B54 */

typedef struct S_80024B54_9 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024B54_9;   /* temp_a2 in func_80024B54 */

typedef struct S_80024B54_10 {
    u8 pad_00[0x2E94];
    u16 unk_2E94;
} S_80024B54_10;   /* var_v0 in func_80024B54 */

typedef struct S_80024B54_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80024B54_11;   /* var_v1 in func_80024B54 */

typedef struct S_80024B54_12 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_80024B54_12;   /* ((S_80024B54_3 *)case2_page)->unk_14A8 in func_80024B54 */

typedef struct S_80024B54_13_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80024B54_13_pre;   /* the 0x14 bytes before ((S_80024B54_0 *)arg0)->unk_14 in func_80024B54, addressed as ((S_80024B54_0 *)arg0)->unk_14[-1] */

typedef struct {
    UnalignedS32 word;
} Packed4;

typedef struct {
    s32 words[4];
} FourWords __attribute__((aligned(4)));

typedef struct {
    Packed4 part[2];
} Packed8;

typedef struct {
    s32 words[8];
} EightWords;

extern void *D_80024008[];
void func_8002401C();
void func_80024494();
void func_800249E4();
s32 func_8003DE58();
s32 func_80053EF0();
M2C_UNK func_80065820();
s32 func_80069EF8();
M2C_UNK func_8009CE1C();
void *func_800A05A4();
s32 func_800A45D8();
s32 func_800A56E0();
s16 func_800BCAD0();
extern M2C_UNK D_8006CCD8;
extern M2C_UNK D_8006CCE8;
extern M2C_UNK D_800814A0;
extern M2C_UNK D_800814A8;
extern M2C_UNK D_80082E80;
extern u16 D_80082E94;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern s32 D_80083780;
extern M2C_UNK D_800DE5DC;
extern s32 D_800E3D18;

void func_80024B54(void *arg0, void *arg1) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK sp38[6];
    Packed8 sp50;
    FourWords sp58[2];
    s16 sp78[3];
    M2C_UNK *var_s1;
    register u8 *case2_page ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *table_s5;
    u8 *table_s6;
    M2C_UNK *var_v1;
    s32 *base_83780;
    register u8 *case1_page ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *held_arg1 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 temp_s7 ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    register s32 temp_v0_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_a1;
    register s32 var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 *var_v0;
    s32 temp_check;
    register s32 table_step ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    s32 post_mask;
    s32 post_color;
    u16 temp_v0;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    register u16 next_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 coord_y;
    void *temp_a0;
    void *temp_a2;
    s32 temp_a3;
    void *temp_v0_3;
    register void *temp_v1_2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    held_arg1 = arg1;
    temp_v1 = ((S_80024B54_0 *)arg0)->unk_0A.s;
    ((S_80024B54_0 *)arg0)->unk_10 = (u16)(((S_80024B54_0 *)arg0)->unk_10 + 1);
    if ((u32)temp_v1 >= 5U) {
        goto block_46;
    }
    (void)jt_keep;
    goto *D_80024008[(u32)temp_v1];
jt_c0:
    temp_a2 = (void *)0x800E0000;
    temp_v1_2 = (void *)0x80080000;
    next_state = ((S_80024B54_0 *)arg0)->unk_0A.u;
    ASM_KEEP_DEP_NV(temp_v1_2, next_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v1_2 = ((S_80024B54_1 *)temp_v1_2)->unk_14A8;
    ASM_KEEP_DEP_NV(temp_a2, temp_v1_2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    temp_a2 = (u8 *)temp_a2 - 0x1A24;
    ((S_80024B54_0 *)arg0)->unk_10 = 0U;
    ((S_80024B54_0 *)arg0)->unk_0A.s = (s16)(next_state + 1);
    ((S_80024B54_1 *)temp_v1_2)->unk_F4 = 0;
    func_80024494(((S_80024B54_0 *)arg0)->unk_00 - 0x20, ((S_80024B54_0 *)arg0)->unk_04, temp_a2);
jt_c1:
    if (!(*((S_80024B54_0 *)arg0)->unk_04 & 0x80)) {
        goto block_46;
    }
    case1_page = (u8 *)0x80080000;
    temp_v1_2 = ((S_80024B54_2 *)case1_page)->unk_14A8;
    ((S_80024B54_0 *)arg0)->unk_18 = 0xAU;
    ((S_80024B54_1 *)temp_v1_2)->unk_A6 = (u16)(((S_80024B54_1 *)temp_v1_2)->unk_A6 - 1);
    temp_v0_2 = 4;
    ((S_80024B54_1 *)temp_v1_2)->unk_A8 = (u8)((S_80024B54_0 *)arg0)->unk_08;
    temp_v1_2 = ((S_80024B54_2 *)case1_page)->unk_14A8;
    next_state = ((S_80024B54_0 *)arg0)->unk_0A.u;
    temp_v1_2 = (void *)(s32)((S_80024B54_1 *)temp_v1_2)->unk_2A.u;
    ((S_80024B54_0 *)arg0)->unk_0A.s = (s16)(next_state + 1);
    ((S_80024B54_0 *)arg0)->unk_0E = (u16)(s32)temp_v1_2;
    if (func_80053EF0(temp_v0_2, case1_page) == 2) {
        goto block_6;
    }
    func_800A56E0(0x300);
    ((S_80024B54_0 *)arg0)->unk_1A = 0;
    return;
block_6:
    func_800A56E0(0x4300);
    ((S_80024B54_0 *)arg0)->unk_1A = 0;
    return;
jt_c2:
    temp_v0 = ((S_80024B54_0 *)arg0)->unk_18 - 1;
    ((S_80024B54_0 *)arg0)->unk_18 = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_46;
    }
    temp_v0_2 = func_80069EF8();
    var_a1 = temp_v0_2;
    if (temp_v0_2 >= 0) {
        goto block_10;
    }
    var_a1 = temp_v0_2 + 0xFFF;
block_10:
    base_83780 = &D_80083780;
    table_step = (s32)D_80083780;
    ASM_CLOBBER("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    case2_page = (u8 *)0x80080000;
    (*(s32 *)((u8 *)held_arg1 + 0)) = table_step;
    table_step = var_a1 >> 0xC;
    table_step <<= 0xC;
    temp_s7 = temp_v0_2 - table_step;
    temp_v1_2 = (void *)base_83780[1];
    (*(s32 *)((u8 *)held_arg1 + 4)) = (s32)temp_v1_2;
    ASM_KEEP_NV(case2_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    table_step = (s32)0x80080000;
    ASM_KEEP(table_step);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    temp_v1_2 = ((S_80024B54_3 *)case2_page)->unk_14A8;
    table_s5 = (u8 *)(table_step + 0x2E80);
    table_step = ((S_80024B54_1 *)temp_v1_2)->unk_88;
    temp_a2 = sp78;
    table_step = (table_step - 0x50) << 0x10;
    (*(s32 *)((u8 *)held_arg1 + 8)) = table_step;
    table_step = D_80083228;
    temp_v1 = ((S_80024B54_1 *)temp_v1_2)->unk_2A.s;
    temp_a3 = 0;
    table_step = ((table_step + temp_v1 + 0x100) >> 7) & 0x1C;
    temp_a0 = (void *)(s32)*(M2C_UNK *)(table_step + D_800E3D18);
    ASM_KEEP_DEP_NV(table_s5, temp_a0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (func_8003DE58(temp_a0, table_s5, temp_a2, temp_a3) == 0) {
        goto block_12;
    }
    (*(s32 *)((u8 *)held_arg1 + 0)) = (s32)((*(s32 *)((u8 *)held_arg1 + 0)) + (sp78[0] << 0x10));
    (*(s32 *)((u8 *)held_arg1 + 4)) = (s32)((*(s32 *)((u8 *)held_arg1 + 4)) + (sp78[1] << 0x10));
    (*(s32 *)((u8 *)held_arg1 + 8)) = (s32)((*(s32 *)((u8 *)held_arg1 + 8)) + (sp78[2] << 0x10));
block_12:
    temp_a0 = ((S_80024B54_3 *)case2_page)->unk_14A8;
    temp_v0_3 = func_800A05A4(temp_a0, ((S_80024B54_4 *)table_s5)->unk_24, ((S_80024B54_4 *)table_s5)->unk_25, (s16)((S_80024B54_5 *)temp_a0)->unk_2A, 8);
    ((S_80024B54_0 *)arg0)->unk_14 = temp_v0_3;
    if (temp_v0_3 == NULL) {
        goto block_14;
    }
    var_s1 = ((S_80024B54_6_pre *)temp_v0_3)[-1].unk_00;
    goto block_21;
block_14:
    var_s1 = sp38;
    var_s0 = 0;
    table_s6 = (u8 *)&D_8006CCD8;
    ((S_80024B54_7 *)var_s1)->unk_02.u = (u16)((((S_80024B54_4 *)table_s5)->unk_24 << 6) + 0x20);
    coord_y = ((S_80024B54_4 *)table_s5)->unk_25;
    table_s5 = (u8 *)&D_8006CCE8;
    ((S_80024B54_7 *)var_s1)->unk_06.u = (u16)((coord_y << 6) + 0x20);
loop_15:
    temp_a0 = ((S_80024B54_3 *)case2_page)->unk_14A8;
    table_step = *(s16 *)((s32)((((S_80024B54_5 *)temp_a0)->unk_2A >> 8) & 0xE) + (s32)table_s6);
    ((S_80024B54_7 *)var_s1)->unk_02.u = (u16)(((S_80024B54_7 *)var_s1)->unk_02.u + (table_step << 6));
    table_step = *(s16 *)((s32)((((S_80024B54_5 *)temp_a0)->unk_2A >> 8) & 0xE) + (s32)table_s5);
    ((S_80024B54_7 *)var_s1)->unk_06.u = (u16)(((S_80024B54_7 *)var_s1)->unk_06.u + (table_step << 6));
    ((S_80024B54_7 *)var_s1)->unk_0A.u = (u16)((S_80024B54_5 *)temp_a0)->unk_88;
    temp_v0_4 = func_800BCAD0(var_s1);
    ((S_80024B54_7 *)var_s1)->unk_0A.u = temp_v0_4;
    if ((s16)temp_v0_4 < 0x201) {
        goto block_17;
    }
    ((S_80024B54_7 *)var_s1)->unk_0A.u = (u16)((S_80024B54_12 *)(((S_80024B54_3 *)case2_page)->unk_14A8))->unk_88;
block_17:
    temp_check = func_800A45D8(((S_80024B54_7 *)var_s1)->unk_02.u, ((S_80024B54_7 *)var_s1)->unk_06.u, (s16)((S_80024B54_7 *)var_s1)->unk_0A.u);
    ASM_KEEP(temp_check);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    var_s0 += 1;
    if ((temp_check << 0x10) == 0) {
        goto block_20;
    }
    temp_a0 = ((S_80024B54_3 *)case2_page)->unk_14A8;
    table_step = *(s16 *)((s32)((((S_80024B54_5 *)temp_a0)->unk_2A >> 8) & 0xE) + (s32)table_s6);
    ((S_80024B54_7 *)var_s1)->unk_02.u = (u16)(((S_80024B54_7 *)var_s1)->unk_02.u - (table_step << 5));
    table_step = *(s16 *)((s32)((((S_80024B54_5 *)temp_a0)->unk_2A >> 8) & 0xE) + (s32)table_s5);
    ((S_80024B54_7 *)var_s1)->unk_06.u = (u16)(((S_80024B54_7 *)var_s1)->unk_06.u - (table_step << 5));
    ((S_80024B54_7 *)var_s1)->unk_0A.u = (u16)((S_80024B54_5 *)temp_a0)->unk_88;
    temp_v0_5 = func_800BCAD0(var_s1);
    ((S_80024B54_7 *)var_s1)->unk_0A.u = temp_v0_5;
    if ((s16)temp_v0_5 < 0x201) {
        goto block_21;
    }
    ((S_80024B54_7 *)var_s1)->unk_0A.u = (u16)((S_80024B54_12 *)(((S_80024B54_3 *)case2_page)->unk_14A8))->unk_88;
    goto block_21;
block_20:
    if (var_s0 < 8) {
        goto loop_15;
    }
block_21:
    func_8002401C(((S_80024B54_8 *)held_arg1)->unk_02, ((S_80024B54_8 *)held_arg1)->unk_06, ((S_80024B54_8 *)held_arg1)->unk_0A, ((S_80024B54_7 *)var_s1)->unk_02.s, (s32)((S_80024B54_7 *)var_s1)->unk_06.s, (s32)((S_80024B54_7 *)var_s1)->unk_0A.s, &sp50);
    func_80065820(&sp50, sp58);
    func_800249E4((s32)arg0, held_arg1, var_s1, temp_s7, sp58[0], sp58[1], sp50);
    func_800249E4((s32)arg0, held_arg1, var_s1, (s16)(temp_s7 + 0x555), sp58[0], sp58[1], sp50);
    func_800249E4((s32)arg0, held_arg1, var_s1, (s16)(temp_s7 + 0xAAA), sp58[0], sp58[1], sp50);
    next_state = ((S_80024B54_0 *)arg0)->unk_0A.u;
    ((S_80024B54_0 *)arg0)->unk_18 = 0x18U;
    goto block_43_store;
jt_c3:
    temp_a0 = ((S_80024B54_0 *)arg0)->unk_14;
    if (temp_a0 == NULL) {
        goto block_36;
    }
    (*(s32 *)((u8 *)temp_a0 + 0x1C)) = (s32)((*(s32 *)((u8 *)temp_a0 + 0x1C)) | 0x10000000);
    temp_a2 = ((S_80024B54_13_pre *)(((S_80024B54_0 *)arg0)->unk_14))[-1].unk_00;
    if ((s16)((S_80024B54_0 *)arg0)->unk_18 < 0xC) {
        goto block_30;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0C = (u8)(((S_80024B54_9 *)temp_a2)->unk_0C + 8);
    ((S_80024B54_9 *)temp_a2)->unk_0D = (u8)(((S_80024B54_9 *)temp_a2)->unk_0D - 8);
    ((S_80024B54_9 *)temp_a2)->unk_0E = (u8)(((S_80024B54_9 *)temp_a2)->unk_0E - 8);
    if ((u8)((S_80024B54_9 *)temp_a2)->unk_0C < 0xE1U) {
        goto block_26;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0C = 0xE0U;
block_26:
    if ((u8)((S_80024B54_9 *)temp_a2)->unk_0D >= 0x20U) {
        goto block_28;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0D = 0x20U;
block_28:
    if ((u8)((S_80024B54_9 *)temp_a2)->unk_0E >= 0x20U) {
        goto block_36;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0E = 0x20U;
    goto block_36;
block_30:
    ((S_80024B54_9 *)temp_a2)->unk_0C = (u8)(((S_80024B54_9 *)temp_a2)->unk_0C - 8);
    ((S_80024B54_9 *)temp_a2)->unk_0D = (u8)(((S_80024B54_9 *)temp_a2)->unk_0D + 8);
    ((S_80024B54_9 *)temp_a2)->unk_0E = (u8)(((S_80024B54_9 *)temp_a2)->unk_0E + 8);
    if ((u8)((S_80024B54_9 *)temp_a2)->unk_0C >= 0x80U) {
        goto block_32;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0C = 0x80U;
block_32:
    if ((u8)((S_80024B54_9 *)temp_a2)->unk_0D < 0x81U) {
        goto block_34;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0D = 0x80U;
block_34:
    var_v0 = (u16 *)(u32)((S_80024B54_9 *)temp_a2)->unk_0E;
    if ((u32)var_v0 < 0x81U) {
        var_v0 = (u16 *)0x80080000;
        goto block_37;
    }
    ((S_80024B54_9 *)temp_a2)->unk_0E = 0x80U;
block_36:
    var_v0 = (u16 *)0x80080000;
block_37:
    if (((S_80024B54_10 *)var_v0)->unk_2E94 & 0x8000) {
        goto block_39;
    }
    temp_v0_6 = ((S_80024B54_0 *)arg0)->unk_18 - 1;
    ((S_80024B54_0 *)arg0)->unk_18 = temp_v0_6;
    if ((s16)temp_v0_6 >= 0) {
        goto block_46;
    }
block_39:
    if (((S_80024B54_0 *)arg0)->unk_14 == NULL) {
        goto block_41;
    }
    func_8009CE1C(((S_80024B54_0 *)arg0)->unk_14, 0xA, ((S_80024B54_0 *)arg0)->unk_09, 9, (s32)(s16)((((S_80024B54_0 *)arg0)->unk_0E << 9) + 0x800), ((S_80024B54_0 *)arg0)->unk_00, 1);
    post_mask = 0xEFFFFFFF;
    post_color = 0x00808080;
    temp_v1_2 = ((S_80024B54_0 *)arg0)->unk_14;
    ((S_80024B54_1 *)temp_v1_2)->unk_1C = (s32)(((S_80024B54_1 *)temp_v1_2)->unk_1C & post_mask);
    temp_a2 = ((S_80024B54_1_pre *)temp_v1_2)[-1].unk_00;
    (*(s32 *)((u8 *)temp_a2 + 0xC)) = post_color;
block_41:
    var_v1 = (M2C_UNK *)0x80080000;
    if (((S_80024B54_0 *)arg0)->unk_1A == 0) {
        goto block_45_base;
    }
block_43:
    next_state = ((S_80024B54_0 *)arg0)->unk_0A.u;
block_43_store:
    ((S_80024B54_0 *)arg0)->unk_0A.s = (s16)(next_state + 1);
    goto block_46;
jt_c4:
    if (((S_80024B54_0 *)arg0)->unk_1A != 0) {
        goto block_46;
    }
    var_v1 = (M2C_UNK *)0x80080000;
block_45_base:
    var_v1 = (M2C_UNK *)((u8 *)var_v1 + 0x3460);
block_45:
    (*(s32 *)((u8 *)var_v1 + 0xC)) = 0;
    ((S_80024B54_11 *)var_v1)->unk_0A = (u16)(((S_80024B54_11 *)var_v1)->unk_0A - 1);
    (*(u16 *)((u8 *)arg0 + -2)) = (u16)(((S_80024B54_0_pre *)arg0)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32)((*(s32 *)((u8 *)(&D_800814A0) + 0)) | 0x8000);
    return;
block_46:
    ((S_80024B54_0 *)arg0)->unk_1A = 0;
    return;
}
