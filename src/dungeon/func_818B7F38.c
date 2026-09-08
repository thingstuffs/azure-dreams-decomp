#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025738_0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    void * unk_18;
} S_80025738_0;   /* arg0 in func_80025738 */

typedef struct S_80025738_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x24];
    s16 unk_88;
} S_80025738_1;   /* temp_s7 in func_80025738 */

typedef struct S_80025738_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80025738_2;   /* arg2 in func_80025738 */

typedef struct S_80025738_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80025738_3;   /* temp_s2 in func_80025738 */

typedef struct S_80025738_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80025738_4;   /* temp_a1 in func_80025738 */

typedef struct S_80025738_5 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80025738_5;   /* arg1 in func_80025738 */

typedef struct S_80025738_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80025738_6;   /* temp_v1_2 in func_80025738 */

typedef struct S_80025738_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80025738_7;   /* temp_a3 in func_80025738 */

typedef struct S_80025738_8 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80025738_8;   /* temp_v0 in func_80025738 */

typedef struct S_80025738_9 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
} S_80025738_9;   /* var_a1 in func_80025738 */

typedef struct S_80025738_10 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80025738_10;   /* temp_v1_4 in func_80025738 */

typedef struct S_80025738_11 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
} S_80025738_11;   /* var_a2 in func_80025738 */

typedef struct S_80025738_12 {
    s32 unk_00;
} S_80025738_12;   /* &D_800814A0 in func_80025738 */

typedef struct S_80025738_13 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80025738_13;   /* ((S_80025738_3 *)temp_s2)->unk_0C in func_80025738 */

typedef struct S_80025738_14_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_80025738_14_pre;   /* the 0x18 bytes before ((S_80025738_1 *)temp_s7)->unk_60 in func_80025738, addressed as ((S_80025738_1 *)temp_s7)->unk_60[-1] */

typedef struct S_80025738_14 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_80025738_14;   /* ((S_80025738_1 *)temp_s7)->unk_60 in func_80025738 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024008[];
M2C_UNK func_80024024();          /* extern */
M2C_UNK func_800253D0();              /* extern */
M2C_UNK func_80025614(); /* extern */
s32 func_8003DE58();     /* extern */
s32 func_800A44E0();              /* extern */
M2C_UNK func_800A56E0();                /* extern */
s16 func_800BCB04();                   /* extern */
extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;

#ifdef NON_MATCHING
#define LOAD_TABLE_X_BASE(v) ((v) = (s32)D_8006CCD8)
#define LOAD_TABLE_Y_BASE(v) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0)
#endif

typedef struct LocalFrame {
    s32 out_x;
    s32 out_y;
    s32 out_z;
    u8 pad_C[12];
    u16 delta[3];
    u16 pad_1E;
    u16 raw_y;
} LocalFrame;

void func_80025738(void *arg0, void *arg1_in, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    register void *arg1 ASM_REG("$21") = arg1_in;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    LocalFrame frame;
    u16 *var_a1;
    u16 *var_a2;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s16 temp_a0_2;
    s16 temp_a1_2;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 temp_block_z ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u16 temp_block_dz ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 temp_v0_4;
    s16 temp_v0_6;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1_2;
    s16 var_v0_4;
    s32 var_v0_5;
    register s32 temp_a0_3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 temp_a1_3;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_7;
    s32 temp_v1_5;
    s32 temp_a0_pre;
    s32 temp_a1_pre;
    s32 out_idx;
    s32 signed_a1;
    register s32 signed_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 offset_x;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 offset_y;
    register s32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 *table_x_entry;
    s16 *table_y_entry;
    u16 *update_x_entry;
    register u16 *update_y_entry ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_a1_loop ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_a2_loop ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 signed_v0;
    register s32 current_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 current_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 current_z;
    s32 case_v0;
    s32 case_v1;
    s16 *off_x;
    s16 *off_y;
    register s32 var_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 var_v0_2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 var_v0_3;
    u16 temp_v1_3;
    u16 var_v0;
    s32 temp_v0_5;
    register s32 var_fp;
    u32 dead_page;
    register s32 var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 var_s6 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 signed_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 signed_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 sign_temp ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *temp_a1;
    register void *temp_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *temp_s2;
    void *temp_s7;
    void *temp_v0;
    void *temp_v1_2;
    void *temp_v1_4;

    temp_v1 = (s32) ((S_80025738_0 *)arg0)->unk_0A;
    temp_s7 = ((S_80025738_0 *)arg0)->unk_00;
    ((S_80025738_0 *)arg0)->unk_10 = (u16) (((S_80025738_0 *)arg0)->unk_10 + 1);
    if ((u32) temp_v1 >= 7U) {
        goto block_53;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
    ((S_80025738_0 *)arg0)->unk_10 = 0U;
    ((S_80025738_0 *)arg0)->unk_0A = (s16) ((u16) ((S_80025738_0 *)arg0)->unk_0A + 1);
    ((S_80025738_0 *)arg0)->unk_0E = (u16) (((u16) ((S_80025738_1 *)temp_s7)->unk_2A >> 9) & 7);
    ((S_80025738_2 *)arg2)->unk_0C = 0x808080;
jt_c1:
    temp_s2 = temp_s7 - 0x20;
    temp_a1 = ((S_80025738_3 *)temp_s2)->unk_0C;
    if (func_8003DE58(((S_80025738_4 *)temp_a1)->unk_08, temp_a1, frame.delta, 0) != 0) {
        goto block_5;
    }
    if (!(((S_80025738_13 *)(((S_80025738_3 *)temp_s2)->unk_0C))->unk_14 & 0x8000)) {
        goto block_53;
    }
block_5:
    temp_v1_2 = ((S_80025738_3 *)temp_s2)->unk_08;
    ((S_80025738_5 *)arg1)->unk_00.at02.v = (u16) ((S_80025738_6 *)temp_v1_2)->unk_02;
    ((S_80025738_5 *)arg1)->unk_04.at02.v = (u16) ((S_80025738_6 *)temp_v1_2)->unk_06;
    temp_v1_3 = ((S_80025738_6 *)temp_v1_2)->unk_0A;
    ((S_80025738_5 *)arg1)->unk_08.at02.v = temp_v1_3;
    if (((S_80025738_13 *)(((S_80025738_3 *)temp_s2)->unk_0C))->unk_14 & 0x8000) {
        goto block_7;
    }
    ((S_80025738_5 *)arg1)->unk_00.at02.v = (u16) (((S_80025738_5 *)arg1)->unk_00.at02.v + frame.delta[0]);
    ((S_80025738_5 *)arg1)->unk_04.at02.v = (u16) (((S_80025738_5 *)arg1)->unk_04.at02.v + frame.delta[1]);
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    temp_block_z = ((S_80025738_5 *)arg1)->unk_08.at02.v;
    temp_block_dz = frame.delta[2];
    var_v0 = temp_block_z + temp_block_dz;
    goto block_8;
block_7:
    var_v0 = temp_v1_3 - 0x40;
block_8:
    ((S_80025738_5 *)arg1)->unk_08.at02.v = var_v0;
    if (!(*((S_80025738_0 *)arg0)->unk_04 & 0x80)) {
        goto block_53;
    }
    temp_v0 = ((S_80025738_1 *)temp_s7)->unk_60;
    var_s0 = 1;
    if (temp_v0 == NULL) {
        goto block_23;
    }
    ((S_80025738_0 *)arg0)->unk_18 = temp_v0;
    temp_a3 = ((S_80025738_14_pre *)(((S_80025738_1 *)temp_s7)->unk_60))[-1].unk_00;
    var_a0 = ((S_80025738_7 *)temp_a3)->unk_00.at02.v;
    var_a0 -= ((S_80025738_5 *)arg1)->unk_00.at02u.v;
    if (var_a0 >= 0) {
        goto block_12;
    }
    var_a0 = 0 - var_a0;
block_12:
    frame.delta[0] = (u16) var_a0;
    var_v0_2 = ((S_80025738_7 *)temp_a3)->unk_04.at02.v;
    var_v0_2 -= ((S_80025738_5 *)arg1)->unk_04.at02u.v;
    if (var_v0_2 >= 0) {
        goto block_14;
    }
    var_v0_2 = 0 - var_v0_2;
block_14:
    frame.delta[1] = (u16) var_v0_2;
    temp_v0 = ((S_80025738_1 *)temp_s7)->unk_60;
    current_z = ((S_80025738_5 *)arg1)->unk_08.at02u.v;
    var_v0_3 = ((S_80025738_8 *)temp_v0)->unk_88;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a1 = (u16 *)((u8 *)&frame.out_x + 2);
    ASM_KEEP(var_a1);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    var_v0_3 -= current_z;
    if (var_v0_3 >= 0) {
        goto block_16;
    }
    var_v0_3 = 0 - var_v0_3;
block_16:
    frame.delta[2] = (u16) var_v0_3;
    ((S_80025738_0 *)arg0)->unk_12 = var_a0;
loop_17:
    if (((S_80025738_9 *)var_a1)->unk_18.s > ((S_80025738_0 *)arg0)->unk_12) {
        ((S_80025738_0 *)arg0)->unk_12 = ((S_80025738_9 *)var_a1)->unk_18.u;
    }
block_19:
    var_s0 += 1;
    var_a1 += 1;
    if (var_s0 < 3) {
        goto loop_17;
    }
    temp_v0_2 = (s32) ((u16) ((S_80025738_0 *)arg0)->unk_12 << 0x10) >> 0x14;
    ((S_80025738_0 *)arg0)->unk_12 = (s16) temp_v0_2;
    if (temp_v0_2 != 0) {
        goto block_22;
    }
    ((S_80025738_0 *)arg0)->unk_12 = 1;
block_22:
    ((S_80025738_5 *)arg1)->unk_0C = (s32) ((s32) (((S_80025738_7 *)temp_a3)->unk_00.at00.v - ((S_80025738_5 *)arg1)->unk_00.at00.v) / (s16) ((S_80025738_0 *)arg0)->unk_12);
    ((S_80025738_5 *)arg1)->unk_10 = (s32) ((s32) (((S_80025738_7 *)temp_a3)->unk_04.at00.v - ((S_80025738_5 *)arg1)->unk_04.at00.v) / (s16) ((S_80025738_0 *)arg0)->unk_12);
    ((S_80025738_5 *)arg1)->unk_14 = (s32) ((s32) ((((S_80025738_14 *)(((S_80025738_1 *)temp_s7)->unk_60))->unk_88 << 0x10) - ((S_80025738_5 *)arg1)->unk_08.at00.v) / (s16) ((S_80025738_0 *)arg0)->unk_12);
    func_800253D0(arg0, arg1);
    var_v0_4 = (u16) ((S_80025738_0 *)arg0)->unk_0A + 1;
    goto block_52;
block_23:
    var_s0 = 0;
    temp_v1_4 = ((S_80025738_3 *)temp_s2)->unk_0C;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    dead_page = 0x80070000;
    ASM_KEEP(dead_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_s4 = ((S_80025738_10 *)temp_v1_4)->unk_24;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_s6 = ((S_80025738_10 *)temp_v1_4)->unk_25;
    var_fp = var_s4;
    frame.raw_y = (u16) var_s6;
loop_24:
    sign_temp = var_s4 << 0x10;
    signed_s2 = sign_temp >> 0x10;
    temp_a0 = (signed_s2 << 6) & 0xFFC0;
    sign_temp = var_s6 << 0x10;
    signed_s3 = sign_temp >> 0x10;
    if ((func_800A44E0(temp_a0, (signed_s3 << 6) & 0xFFC0, ((S_80025738_1 *)temp_s7)->unk_88, (s16) (((S_80025738_0 *)arg0)->unk_0E << 9)) << 0x10) != 0) {
        goto block_28;
    }
    LOAD_TABLE_X_BASE(temp_t0);
    ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    temp_v0_3 = (s16) ((S_80025738_0 *)arg0)->unk_0E;
    temp_a2_loop = (u16) ((S_80025738_1 *)temp_s7)->unk_88;
    temp_v0_3 *= 2;
    table_x_entry = (s16 *)((s32)temp_v0_3 + temp_t0);
    ASM_KEEP(table_x_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_a2_loop -= 0x20;
    temp_a2_loop = (s16) temp_a2_loop;
    LOAD_TABLE_Y_BASE(temp_t0);
    table_y_entry = (s16 *)((s32)temp_v0_3 + temp_t0);
    ASM_USE(var_fp);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    temp_a0 = signed_s2 + *table_x_entry;
    temp_a0 = ((temp_a0 << 6) + 0x20) & 0xFFE0;
    temp_a1_loop = signed_s3 + *table_y_entry;
    temp_a1_loop = ((temp_a1_loop << 6) + 0x20) & 0xFFE0;
    temp_v0_4 = func_800BCB04(temp_a0, temp_a1_loop, temp_a2_loop);
    temp_a3 = &frame.out_x;
    if (temp_v0_4 >= 0x201) {
        goto block_29;
    }
    if ((s16) (temp_v0_4 - (u16) ((S_80025738_1 *)temp_s7)->unk_88) < -0x3F) {
        goto block_29;
    }
    LOAD_TABLE_X_BASE(temp_t0);
    ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    var_s0 += 1;
    temp_v1_5 = (s16) ((S_80025738_0 *)arg0)->unk_0E;
    temp_v1_5 *= 2;
    update_x_entry = (u16 *)((s32)temp_v1_5 + temp_t0);
    LOAD_TABLE_Y_BASE(temp_t0);
    update_y_entry = (u16 *)((s32)temp_v1_5 + temp_t0);
    ASM_KEEP(update_y_entry);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    temp_a0 = var_s4 + *update_x_entry;
    var_s4 = temp_a0;
    temp_v0_5 = var_s6 + *update_y_entry;
    var_s6 = temp_v0_5;
    frame.raw_y = (u16) temp_v0_5;
    ASM_KEEP4_NV(temp_a0, temp_v0_5, var_s4, var_s6);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    var_fp = temp_a0;
    if (var_s0 < 8) {
        goto loop_24;
    }
block_28:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_a3 = &frame.out_x;
block_29:
    var_s0 = 1;
    ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    temp_a1_pre = var_fp << 0x10;
    off_x = (s16 *)D_8006CCD8;
    ASM_KEEP(off_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_a1_pre >>= 0xA;
    out_idx = (s16) ((S_80025738_0 *)arg0)->unk_0E;
    ASM_KEEP(out_idx);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    var_a2 = (u16 *)((u8 *)&frame.out_x + 2);
    ASM_KEEP(var_a2);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    offset_x = off_x[out_idx];
    off_y = (s16 *)D_8006CCE8;
    temp_a1_2 = temp_a1_pre + ((offset_x + 1) << 5);
    ((S_80025738_7 *)temp_a3)->unk_00.at02.v = temp_a1_2;
    signed_a1 = temp_a1_2;
    temp_t0 = frame.raw_y;
    out_idx = (s16) ((S_80025738_0 *)arg0)->unk_0E;
    temp_a0_pre = temp_t0 << 0x10;
    ASM_KEEP(out_idx);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    offset_y = off_y[out_idx];
    temp_a0_pre >>= 0xA;
    temp_a0_2 = temp_a0_pre + ((offset_y + 1) << 5);
    ((S_80025738_7 *)temp_a3)->unk_04.at02.v = temp_a0_2;
    signed_a0 = (s32) ((u16) temp_a0_2 << 0x10);
    temp_v0_6 = ((S_80025738_5 *)arg1)->unk_08.at02.v + 0x20;
    ((S_80025738_7 *)temp_a3)->unk_08.at02.v = temp_v0_6;
    current_x = ((S_80025738_5 *)arg1)->unk_00.at02u.v;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    signed_a0 >>= 0x10;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a1_2 = signed_a1;
    var_a1_2 -= current_x;
    if (var_a1_2 >= 0) {
        goto block_31;
    }
    var_a1_2 = 0 - var_a1_2;
block_31:
    frame.delta[0] = var_a1_2;
    current_y = ((S_80025738_5 *)arg1)->unk_04.at02u.v;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    signed_v0 = (s32) ((u16) temp_v0_6 << 0x10);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_a0_2 = signed_a0;
    var_a0_2 -= current_y;
    if (var_a0_2 >= 0) {
        goto block_33;
    }
    var_a0_2 = 0 - var_a0_2;
block_33:
    frame.delta[1] = var_a0_2;
    current_z = ((S_80025738_5 *)arg1)->unk_08.at02u.v;
    signed_v0 >>= 0x10;
    var_v0_5 = signed_v0;
    var_v0_5 -= current_z;
    if (var_v0_5 >= 0) {
        goto block_35;
    }
    var_v0_5 = 0 - var_v0_5;
block_35:
    frame.delta[2] = var_v0_5;
    ((S_80025738_0 *)arg0)->unk_12 = var_a1_2;
loop_36:
    if (((S_80025738_11 *)var_a2)->unk_18.s > ((S_80025738_0 *)arg0)->unk_12) {
        ((S_80025738_0 *)arg0)->unk_12 = ((S_80025738_11 *)var_a2)->unk_18.u;
    }
block_38:
    var_s0 += 1;
    var_a2 += 1;
    if (var_s0 < 3) {
        goto loop_36;
    }
    temp_v0_7 = (s32) ((u16) ((S_80025738_0 *)arg0)->unk_12 << 0x10) >> 0x14;
    ((S_80025738_0 *)arg0)->unk_12 = (s16) temp_v0_7;
    if (temp_v0_7 != 0) {
        goto block_41;
    }
    ((S_80025738_0 *)arg0)->unk_12 = 1;
block_41:
    ((S_80025738_5 *)arg1)->unk_0C = (s32) ((s32) (((S_80025738_7 *)temp_a3)->unk_00.at00.v - ((S_80025738_5 *)arg1)->unk_00.at00.v) / (s16) ((S_80025738_0 *)arg0)->unk_12);
    ((S_80025738_5 *)arg1)->unk_10 = (s32) ((s32) (((S_80025738_7 *)temp_a3)->unk_04.at00.v - ((S_80025738_5 *)arg1)->unk_04.at00.v) / (s16) ((S_80025738_0 *)arg0)->unk_12);
    ((S_80025738_5 *)arg1)->unk_14 = (s32) ((s32) (((S_80025738_7 *)temp_a3)->unk_08.at00.v - ((S_80025738_5 *)arg1)->unk_08.at00.v) / (s16) ((S_80025738_0 *)arg0)->unk_12);
    func_80025614(arg0, arg1);
    var_v0_4 = 6;
    goto block_52;
jt_c2:
    case_v0 = ((S_80025738_5 *)arg1)->unk_00.at00.v;
    case_v1 = ((S_80025738_5 *)arg1)->unk_0C;
    temp_a0_3 = ((S_80025738_5 *)arg1)->unk_10;
    temp_a1_3 = ((S_80025738_5 *)arg1)->unk_14;
    case_v0 += case_v1;
    ((S_80025738_5 *)arg1)->unk_00.at00.v = case_v0;
    case_v0 = ((S_80025738_5 *)arg1)->unk_04.at00.v;
    case_v1 = ((S_80025738_5 *)arg1)->unk_08.at00.v;
    case_v0 += temp_a0_3;
    case_v1 += temp_a1_3;
    ((S_80025738_5 *)arg1)->unk_04.at00.v = case_v0;
    ((S_80025738_5 *)arg1)->unk_08.at00.v = case_v1;
    if ((s16) ((S_80025738_0 *)arg0)->unk_10 < ((S_80025738_0 *)arg0)->unk_12) {
        goto block_53;
    }
    func_800A56E0(0x300, temp_a1_3);
    goto block_48;
jt_c3:
    if ((s16) ((S_80025738_0 *)arg0)->unk_10 >= 0x10) {
        goto block_48;
    }
    ((S_80025738_0 *)arg0)->unk_14 = 0;
    return;
jt_c4:
    if ((s16) ((S_80025738_0 *)arg0)->unk_10 < 0x30) {
        goto block_53;
    }
    func_80024024(((S_80025738_1 *)temp_s7)->unk_60, ((S_80025738_0 *)arg0)->unk_09, temp_s7);
block_48:
    ((S_80025738_0 *)arg0)->unk_10 = 0U;
    ((S_80025738_0 *)arg0)->unk_0A = (s16) ((u16) ((S_80025738_0 *)arg0)->unk_0A + 1);
    goto block_53;
jt_c5:
    if (((S_80025738_0 *)arg0)->unk_14 != 0) {
        goto block_53;
    }
    D_8008346C = 0;
    (*(u16 *)((u8 *)arg0 + -2)) = (u16) ((*(u16 *)((u8 *)arg0 + -2)) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_80025738_12 *)(&D_800814A0))->unk_00 | 0x8000);
    goto block_53;
jt_c6:
    ((S_80025738_5 *)arg1)->unk_00.at00.v = (s32) (((S_80025738_5 *)arg1)->unk_00.at00.v + ((S_80025738_5 *)arg1)->unk_0C);
    ((S_80025738_5 *)arg1)->unk_04.at00.v = (s32) (((S_80025738_5 *)arg1)->unk_04.at00.v + ((S_80025738_5 *)arg1)->unk_10);
    ((S_80025738_5 *)arg1)->unk_08.at00.v = (s32) (((S_80025738_5 *)arg1)->unk_08.at00.v + ((S_80025738_5 *)arg1)->unk_14);
    if ((s16) ((S_80025738_0 *)arg0)->unk_10 < ((S_80025738_0 *)arg0)->unk_12) {
        goto block_53;
    }
    var_v0_4 = 5;
block_52:
    ((S_80025738_0 *)arg0)->unk_0A = var_v0_4;
    ((S_80025738_0 *)arg0)->unk_10 = 0U;
block_53:
    ((S_80025738_0 *)arg0)->unk_14 = 0;
    return;
}
