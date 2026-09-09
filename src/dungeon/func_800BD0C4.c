#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C2824_0 {
    void * unk_00;
    s16 unk_04;
    s16 unk_06;
} S_800C2824_0;   /* arg0 in func_800C2824 */

typedef struct S_800C2824_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800C2824_1;   /* temp_s0 in func_800C2824 */

typedef struct S_800C2824_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C2824_2;   /* temp_v1_2 in func_800C2824 */

typedef struct S_800C2824_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800C2824_3;   /* arg1 in func_800C2824 */

typedef struct S_800C2824_4 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    union { struct { s32 v; } at00; struct { s8 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C2824_4;   /* arg2 in func_800C2824 */

typedef struct S_800C2824_5 {
    u8 pad_00[0xA93];
    s8 unk_A93;
} S_800C2824_5;   /* page_base + (var_a2 * 0x54) in func_800C2824 */

typedef struct S_800C2824_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800C2824_6_pre;   /* the 0x14 bytes before c2_object in func_800C2824, addressed as c2_object[-1] */

typedef struct S_800C2824_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C2824_6;   /* c2_object in func_800C2824 */

typedef struct S_800C2824_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2824_7;   /* (void *)c2_coord in func_800C2824 */

typedef struct S_800C2824_8 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800C2824_8;   /* temp_t0 in func_800C2824 */

typedef struct S_800C2824_9_pre {
    u16 unk_00;
} S_800C2824_9_pre;   /* the 0x2 bytes before c3_object in func_800C2824, addressed as c3_object[-1] */

typedef struct S_800C2824_10 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800C2824_10;   /* c3_page in func_800C2824 */

typedef struct S_800C2824_11 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2824_11;   /* temp_a1_2 in func_800C2824 */

typedef struct S_800C2824_12_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800C2824_12_pre;   /* the 0x14 bytes before c17_object in func_800C2824, addressed as c17_object[-1] */

typedef struct S_800C2824_12 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800C2824_12;   /* c17_object in func_800C2824 */

typedef struct S_800C2824_13 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800C2824_13;   /* (void *)c17_coord in func_800C2824 */

typedef struct S_800C2824_14_pre {
    u16 unk_00;
} S_800C2824_14_pre;   /* the 0x2 bytes before temp_v1_8 in func_800C2824, addressed as temp_v1_8[-1] */

typedef struct S_800C2824_15 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800C2824_15;   /* c17_final_ptr in func_800C2824 */

typedef struct S_800C2824_16 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C2824_16;   /* ((S_800C2824_0 *)arg0)->unk_00 in func_800C2824 */

extern void *D_8008938C[];
extern u8 D_80010000[];
s32 func_80042900();
s32 func_8004491C();
void func_80044A50();
M2C_UNK func_80099844();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
void *func_800A32A4();
M2C_UNK func_800A56E0();
s32 func_800A6620();
M2C_UNK func_800B8FC8();
s32 func_800BBA40(u8, u8, s16, void *, s32, s32, void *);
void func_800BC318();
extern M2C_UNK D_800814A0;
extern u8 D_80082E80[];
extern M2C_UNK D_800C0180;
extern M2C_UNK D_800C27F0;
extern M2C_UNK D_800CEF54;
extern M2C_UNK D_800DF45C;
extern M2C_UNK D_800DF4A4;
extern void *D_800DF55C;
extern void *D_800DF560;
extern M2C_UNK D_800E1640;
extern void *D_800E3D7C;

typedef struct {
    s32 sp20;
    s32 sp24;
    s16 sp28;
    s16 sp2A;
} StackArgs;

void func_800C2824(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c16, &&jt_c17 };
    StackArgs sp;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s16 temp_v0_4;
    s16 temp_v0_8;
    s32 temp_v1;
    register s16 var_v0 ASM_REG("$2"); /* MATCH: all state-update arms join with the value in v0. */
    register u8 *c3_page ASM_REG("$4"); /* MATCH: retain the shared flag page in retail a0. */
    void *temp_v0_5;
    s32 var_v1;
    s32 temp_v1_9;
    s32 temp_v0_9;
    register s32 bba_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_v1_4;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 temp_v1_3;
    void *temp_a1;
    void *temp_a1_2;
    void *temp_a1_3;
    void *temp_s0;
    register void *temp_v0_7 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *temp_v1_2;
    void *temp_v1_5;
    void *temp_v1_6;
    void *temp_v1_7;
    void *temp_v1_8;
    register u8 *temp_a1_4 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *c2_object;
    u32 c2_coord;
    s32 c2_status;
    s32 c2_x;
    void *c17_object;
    u32 c17_coord;
    s32 c17_status;
    s32 c17_x;
    void *c17_final_ptr;
    register s32 c17_flags ASM_REG("$3"); /* MATCH: both flag paths feed the shared tail in v1. */
    u16 c17_field;
    void *temp_t0;
    u8 *page_base;

    temp_v1 = ((S_800C2824_0 *)arg0)->unk_04;
    if ((u32) temp_v1 >= 0x12U) {
        goto block_27;
    }
    (void)jt_keep; goto *D_8008938C[(u32)(temp_v1)];
jt_c0:
    if (((S_800C2824_16 *)(((S_800C2824_0 *)arg0)->unk_00))->unk_14 & 0x4000) {
        goto block_4;
    }
    ((S_800C2824_0 *)arg0)->unk_04 = 0x10;
    return;
block_4:
    sp.sp20 = 0x01800340;
    sp.sp24 = 0x400040;
    sp.sp28 = 0x360;
    sp.sp2A = 0x1B8;
    func_800B8FC8(((S_800C2824_0 *)arg0)->unk_00, &sp.sp20, &sp.sp28, 1, 2);
    temp_s0 = ((S_800C2824_0 *)arg0)->unk_00 - 0x20;
    func_80044A50(temp_s0);
    func_800BC318(temp_s0);
    temp_v1_2 = ((S_800C2824_1 *)temp_s0)->unk_08;
    temp_v0 = ((S_800C2824_2 *)temp_v1_2)->unk_02;
    ((S_800C2824_3 *)arg1)->unk_02 = temp_v0;
    ((S_800C2824_3 *)arg1)->unk_0E = temp_v0;
    temp_v0_2 = ((S_800C2824_2 *)temp_v1_2)->unk_06;
    ((S_800C2824_3 *)arg1)->unk_06 = temp_v0_2;
    ((S_800C2824_3 *)arg1)->unk_12 = temp_v0_2;
    temp_v0_3 = ((S_800C2824_2 *)temp_v1_2)->unk_0A;
    ((S_800C2824_3 *)arg1)->unk_0A = temp_v0_3;
    ((S_800C2824_3 *)arg1)->unk_16 = temp_v0_3;
    func_8004491C(arg0 - 0x20, &D_800CEF54);
    ((S_800C2824_4 *)arg2)->unk_10 = 0x20;
    ((S_800C2824_4 *)arg2)->unk_08 = &D_800DF4A4;
    ((S_800C2824_4 *)arg2)->unk_0C.at00.v = 0x808080;
    ((S_800C2824_4 *)arg2)->unk_1E = 0x1000;
    ((S_800C2824_4 *)arg2)->unk_1C = 0x1000;
    ((S_800C2824_4 *)arg2)->unk_14 = (u16) (((S_800C2824_4 *)arg2)->unk_14 | 0xC);
    ((S_800C2824_0 *)arg0)->unk_06 = 0x10;
    func_800A56E0(1);
    ((S_800C2824_0 *)arg0)->unk_04 = (s16) ((u16) ((S_800C2824_0 *)arg0)->unk_04 + 1);
jt_c1:
    temp_v1_3 = (u8) ((S_800C2824_4 *)arg2)->unk_0C.at00.v;
    temp_v1_4 = temp_v1_3 - ((s32) temp_v1_3 / (s16) ((S_800C2824_0 *)arg0)->unk_06);
    ((S_800C2824_4 *)arg2)->unk_0C.at00u.v = temp_v1_4;
    ((S_800C2824_4 *)arg2)->unk_0C.at02.v = temp_v1_4;
    ((S_800C2824_4 *)arg2)->unk_0C.at01.v = temp_v1_4;
    temp_v0_4 = (u16) ((S_800C2824_0 *)arg0)->unk_06 - 1;
    ((S_800C2824_0 *)arg0)->unk_06 = temp_v0_4;
    if ((temp_v0_4 << 0x10) > 0) {
        goto block_27;
    }
    var_v0 = (u16) ((S_800C2824_0 *)arg0)->unk_04 + 1;
    goto block_20;
jt_c2:
    temp_v0_5 = func_800A32A4(((S_800C2824_0 *)arg0)->unk_00);
    if (temp_v0_5 == 0) {
        goto block_10;
    }
    var_a2 = func_800A6620(temp_v0_5, 0);
    if (var_a2 >= 0x40) {
        goto block_10;
    }
    page_base = (u8 *)0x80010000;
    ((S_800C2824_5 *)(page_base + (var_a2 * 0x54)))->unk_A93 = 0;
    ((s32 *)0x80010980)[var_a2] = 0;
block_10:
    if ((func_80042900(((S_800C2824_0 *)arg0)->unk_00, 0x1B) << 0x10) != 0) {
        goto block_14;
    }
    c2_object = ((S_800C2824_0 *)arg0)->unk_00;
    c2_status = ((S_800C2824_6 *)c2_object)->unk_1C;
    c2_coord = (u32)((S_800C2824_6_pre *)c2_object)[-1].unk_00;
    c2_status &= 0x2000;
    c2_x = ((S_800C2824_7 *)((void *)c2_coord))->unk_24;
    c2_coord = ((S_800C2824_7 *)((void *)c2_coord))->unk_25;
    var_a2 = 0x3000;
    if (!c2_status) {
        goto block_13;
    }
    var_a2 = 0x300;
block_13:
    func_8009A3D0(c2_x, c2_coord, var_a2);
block_14:
    func_8009A028(((S_800C2824_0 *)arg0)->unk_00);
    func_80099844(((S_800C2824_0 *)arg0)->unk_00, &D_800E1640);
    var_v0 = (u16) ((S_800C2824_0 *)arg0)->unk_04 + 1;
    goto block_20;
jt_c3: {
    register u8 *c3_82_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register void *c3_object ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 c3_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    c3_82_page = (u8 *)0x80080000;
    ASM_KEEP(c3_82_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    temp_a1_4 = c3_82_page + 0x2E80;
    temp_t0 = D_800E3D7C;
    D_800DF55C = temp_t0;
    bba_flags = 0x208020;
    if (func_800BBA40(temp_a1_4[0x24], temp_a1_4[0x25], ((S_800C2824_8 *)temp_t0)->unk_88, &D_800DF45C, 0x2800, bba_flags, &D_800C0180) == 0) {
        goto block_27;
    }
    c3_page = (u8 *)0x80080000;
    c3_object = ((S_800C2824_0 *)arg0)->unk_00;
    ((S_800C2824_9_pre *)c3_object)[-1].unk_00 = (u16) (((S_800C2824_9_pre *)c3_object)[-1].unk_00 | 0x8000);
    c17_flags = ((S_800C2824_10 *)c3_page)->unk_14A0 | 0x8000;
    ((S_800C2824_10 *)c3_page)->unk_14A0 = c17_flags;
    goto block_26;
}
jt_c16:
    temp_v0_7 = ((S_800C2824_0 *)arg0)->unk_00;
    temp_t0 = temp_v0_7;
    temp_a1_2 = (*(void **)((u8 *)temp_t0 + -0x14));
    temp_v0_9 = ((S_800C2824_8 *)temp_t0)->unk_88;
    D_800DF55C = temp_t0;
    bba_flags = 0x208020;
    if (func_800BBA40(((S_800C2824_11 *)temp_a1_2)->unk_24, ((S_800C2824_11 *)temp_a1_2)->unk_25, temp_v0_9, &D_800DF45C, 0x2800, bba_flags, &D_800C27F0) == 0) {
        goto block_27;
    }
    ((S_800C2824_0 *)arg0)->unk_06 = 0x3C;
    var_v0 = (u16) ((S_800C2824_0 *)arg0)->unk_04 + 1;
block_20:
    ASM_SCHED_BARRIER(); /* MATCH: keep the shared state store at its local landing. */
    ((S_800C2824_0 *)arg0)->unk_04 = var_v0;
    return;
jt_c17:
    temp_v0_8 = (u16) ((S_800C2824_0 *)arg0)->unk_06 - 1;
    ((S_800C2824_0 *)arg0)->unk_06 = temp_v0_8;
    if ((temp_v0_8 << 0x10) > 0) {
        goto block_27;
    }
    func_800A32A4(((S_800C2824_0 *)arg0)->unk_00);
    if ((func_80042900(((S_800C2824_0 *)arg0)->unk_00, 0x1B) << 0x10) != 0) {
        goto block_25;
    }
    c17_object = ((S_800C2824_0 *)arg0)->unk_00;
    c17_status = ((S_800C2824_12 *)c17_object)->unk_1C;
    c17_coord = (u32)((S_800C2824_12_pre *)c17_object)[-1].unk_00;
    c17_status &= 0x2000;
    c17_x = ((S_800C2824_13 *)((void *)c17_coord))->unk_24;
    c17_coord = ((S_800C2824_13 *)((void *)c17_coord))->unk_25;
    var_a2_2 = 0x3000;
    if (!c17_status) {
        goto block_24;
    }
    var_a2_2 = 0x300;
block_24:
    func_8009A3D0(c17_x, c17_coord, var_a2_2);
block_25:
    func_8009A028(((S_800C2824_0 *)arg0)->unk_00);
    temp_v1_8 = ((S_800C2824_0 *)arg0)->unk_00;
    (*(u16 *)((u8 *)temp_v1_8 + -2)) = (u16) (((S_800C2824_14_pre *)temp_v1_8)[-1].unk_00 | 0x8000);
    c17_final_ptr = D_800DF560;
    c3_page = (u8 *)0x80080000;
    c17_flags = ((S_800C2824_10 *)c3_page)->unk_14A0;
    c17_field = ((S_800C2824_15 *)c17_final_ptr)->unk_1E;
    c17_flags |= 0x8000;
    ((S_800C2824_10 *)c3_page)->unk_14A0 = c17_flags;
    ((S_800C2824_15 *)c17_final_ptr)->unk_1E = (u16)(c17_field | 0x8000);
block_26:
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) ((*(u16 *)((u8 *)arg0 + -2)) | 0x8000);
    ((S_800C2824_10 *)c3_page)->unk_14A0 = c17_flags;
block_27:
    return;
}
