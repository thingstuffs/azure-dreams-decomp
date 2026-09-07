#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

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
    register void *arg1 ASM_REG("$21") = arg1_in;
    LocalFrame frame;
    register u16 *var_a1 ASM_REG("$5");
    register u16 *var_a2 ASM_REG("$6");
    register s32 temp_a0 ASM_REG("$4");
    register s16 temp_a0_2 ASM_REG("$4");
    register s16 temp_a1_2 ASM_REG("$5");
    register u16 temp_block_z ASM_REG("$2");
    register u16 temp_block_dz ASM_REG("$3");
    s16 temp_v0_4;
    register s16 temp_v0_6 ASM_REG("$2");
    s32 temp_v1;
    register s32 var_a0 ASM_REG("$4");
    register s32 var_a0_2 ASM_REG("$4");
    register s32 var_a1_2 ASM_REG("$5");
    register s16 var_v0_4 ASM_REG("$2");
    register s32 var_v0_5 ASM_REG("$2");
    register s32 temp_a0_3 ASM_REG("$4");
    register s32 temp_a1_3 ASM_REG("$5");
    s32 temp_v0_2;
    register s32 temp_v0_3 ASM_REG("$2");
    s32 temp_v0_7;
    register s32 temp_v1_5 ASM_REG("$3");
    register s32 temp_a0_pre ASM_REG("$4");
    register s32 temp_a1_pre ASM_REG("$5");
    register s32 out_idx ASM_REG("$2");
    register s32 signed_a1 ASM_REG("$5");
    register s32 signed_a0 ASM_REG("$4");
    register s32 offset_x ASM_REG("$2");
    register s32 offset_y ASM_REG("$2");
    register s32 temp_t0 ASM_REG("$8");
    register s16 *table_x_entry ASM_REG("$3");
    register s16 *table_y_entry ASM_REG("$2");
    register u16 *update_x_entry ASM_REG("$2");
    register u16 *update_y_entry ASM_REG("$3");
    register s32 temp_a1_loop ASM_REG("$5");
    register s32 temp_a2_loop ASM_REG("$6");
    register s32 signed_v0 ASM_REG("$2");
    register s32 current_x ASM_REG("$3");
    register s32 current_y ASM_REG("$3");
    register s32 current_z ASM_REG("$3");
    register s32 case_v0 ASM_REG("$2");
    register s32 case_v1 ASM_REG("$3");
    register s16 *off_x ASM_REG("$3");
    register s16 *off_y ASM_REG("$3");
    register s32 var_s0 ASM_REG("$16");
    register s32 var_v0_2 ASM_REG("$2");
    register s32 var_v0_3 ASM_REG("$2");
    u16 temp_v1_3;
    register u16 var_v0 ASM_REG("$2");
    register s32 temp_v0_5 ASM_REG("$2");
    register s32 var_fp;
    register u32 dead_page ASM_REG("$2");
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s6 ASM_REG("$22");
    register s32 signed_s2 ASM_REG("$18");
    register s32 signed_s3 ASM_REG("$19");
    register s32 sign_temp ASM_REG("$2");
    void *temp_a1;
    register void *temp_a3 ASM_REG("$7");
    register void *temp_s2 ASM_REG("$18");
    register void *temp_s7 ASM_REG("$23");
    void *temp_v0;
    void *temp_v1_2;
    register void *temp_v1_4 ASM_REG("$3");

    temp_v1 = (s32) M2C_FIELD(arg0, s16 *, 0xA);
    temp_s7 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) (M2C_FIELD(arg0, u16 *, 0x10) + 1);
    if ((u32) temp_v1 >= 7U) {
        goto block_53;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) (((u16) M2C_FIELD(temp_s7, u16 *, 0x2A) >> 9) & 7);
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
jt_c1:
    temp_s2 = temp_s7 - 0x20;
    temp_a1 = M2C_FIELD(temp_s2, void **, 0xC);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, frame.delta, 0) != 0) {
        goto block_5;
    }
    if (!(M2C_FIELD(M2C_FIELD(temp_s2, void **, 0xC), u16 *, 0x14) & 0x8000)) {
        goto block_53;
    }
block_5:
    temp_v1_2 = M2C_FIELD(temp_s2, void **, 8);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_v1_2, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_v1_2, u16 *, 6);
    temp_v1_3 = M2C_FIELD(temp_v1_2, u16 *, 0xA);
    M2C_FIELD(arg1, u16 *, 0xA) = temp_v1_3;
    if (M2C_FIELD(M2C_FIELD(temp_s2, void **, 0xC), u16 *, 0x14) & 0x8000) {
        goto block_7;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + frame.delta[0]);
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + frame.delta[1]);
    ASM_MEM_BARRIER();
    temp_block_z = M2C_FIELD(arg1, u16 *, 0xA);
    temp_block_dz = frame.delta[2];
    var_v0 = temp_block_z + temp_block_dz;
    goto block_8;
block_7:
    var_v0 = temp_v1_3 - 0x40;
block_8:
    M2C_FIELD(arg1, u16 *, 0xA) = var_v0;
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_53;
    }
    temp_v0 = M2C_FIELD(temp_s7, void **, 0x60);
    var_s0 = 1;
    if (temp_v0 == NULL) {
        goto block_23;
    }
    M2C_FIELD(arg0, void **, 0x18) = temp_v0;
    temp_a3 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x18);
    var_a0 = M2C_FIELD(temp_a3, s16 *, 2);
    var_a0 -= M2C_FIELD(arg1, s16 *, 2);
    if (var_a0 >= 0) {
        goto block_12;
    }
    var_a0 = 0 - var_a0;
block_12:
    frame.delta[0] = (u16) var_a0;
    var_v0_2 = M2C_FIELD(temp_a3, s16 *, 6);
    var_v0_2 -= M2C_FIELD(arg1, s16 *, 6);
    if (var_v0_2 >= 0) {
        goto block_14;
    }
    var_v0_2 = 0 - var_v0_2;
block_14:
    frame.delta[1] = (u16) var_v0_2;
    temp_v0 = M2C_FIELD(temp_s7, void **, 0x60);
    current_z = M2C_FIELD(arg1, s16 *, 0xA);
    var_v0_3 = M2C_FIELD(temp_v0, s16 *, 0x88);
    ASM_SCHED_BARRIER();
    var_a1 = (u16 *)((u8 *)&frame.out_x + 2);
    ASM_KEEP(var_a1);
    var_v0_3 -= current_z;
    if (var_v0_3 >= 0) {
        goto block_16;
    }
    var_v0_3 = 0 - var_v0_3;
block_16:
    frame.delta[2] = (u16) var_v0_3;
    M2C_FIELD(arg0, s16 *, 0x12) = var_a0;
loop_17:
    if (M2C_FIELD(var_a1, s16 *, 0x18) > M2C_FIELD(arg0, s16 *, 0x12)) {
        M2C_FIELD(arg0, s16 *, 0x12) = M2C_FIELD(var_a1, u16 *, 0x18);
    }
block_19:
    var_s0 += 1;
    var_a1 += 1;
    if (var_s0 < 3) {
        goto loop_17;
    }
    temp_v0_2 = (s32) ((u16) M2C_FIELD(arg0, s16 *, 0x12) << 0x10) >> 0x14;
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) temp_v0_2;
    if (temp_v0_2 != 0) {
        goto block_22;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 1;
block_22:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (M2C_FIELD(temp_a3, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(temp_a3, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) ((M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), s16 *, 0x88) << 0x10) - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    func_800253D0(arg0, arg1);
    var_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0xA) + 1;
    goto block_52;
block_23:
    var_s0 = 0;
    ASM_SCHED_BARRIER();
    temp_v1_4 = M2C_FIELD(temp_s2, void **, 0xC);
    ASM_SCHED_BARRIER();
    dead_page = 0x80070000;
    ASM_KEEP(dead_page);
    var_s4 = M2C_FIELD(temp_v1_4, u8 *, 0x24);
    ASM_SCHED_BARRIER();
    var_s6 = M2C_FIELD(temp_v1_4, u8 *, 0x25);
    ASM_SCHED_BARRIER();
    var_fp = var_s4;
    ASM_SCHED_BARRIER();
    frame.raw_y = (u16) var_s6;
loop_24:
    sign_temp = var_s4 << 0x10;
    signed_s2 = sign_temp >> 0x10;
    temp_a0 = (signed_s2 << 6) & 0xFFC0;
    sign_temp = var_s6 << 0x10;
    signed_s3 = sign_temp >> 0x10;
    if ((func_800A44E0(temp_a0, (signed_s3 << 6) & 0xFFC0, M2C_FIELD(temp_s7, s16 *, 0x88), (s16) (M2C_FIELD(arg0, u16 *, 0xE) << 9)) << 0x10) != 0) {
        goto block_28;
    }
    LOAD_TABLE_X_BASE(temp_t0);
    ASM_KEEP(temp_t0);
    temp_v0_3 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    temp_a2_loop = (u16) M2C_FIELD(temp_s7, s16 *, 0x88);
    temp_v0_3 *= 2;
    table_x_entry = (s16 *)((s32)temp_v0_3 + temp_t0);
    ASM_KEEP(table_x_entry);
    temp_a2_loop -= 0x20;
    temp_a2_loop = (s16) temp_a2_loop;
    LOAD_TABLE_Y_BASE(temp_t0);
    ASM_KEEP(temp_t0);
    table_y_entry = (s16 *)((s32)temp_v0_3 + temp_t0);
    ASM_KEEP(table_y_entry);
    ASM_USE(var_fp);
    temp_a0 = signed_s2 + *table_x_entry;
    temp_a0 = ((temp_a0 << 6) + 0x20) & 0xFFE0;
    temp_a1_loop = signed_s3 + *table_y_entry;
    temp_a1_loop = ((temp_a1_loop << 6) + 0x20) & 0xFFE0;
    temp_v0_4 = func_800BCB04(temp_a0, temp_a1_loop, temp_a2_loop);
    temp_a3 = &frame.out_x;
    if (temp_v0_4 >= 0x201) {
        goto block_29;
    }
    if ((s16) (temp_v0_4 - (u16) M2C_FIELD(temp_s7, s16 *, 0x88)) < -0x3F) {
        goto block_29;
    }
    LOAD_TABLE_X_BASE(temp_t0);
    ASM_KEEP(temp_t0);
    var_s0 += 1;
    temp_v1_5 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    temp_v1_5 *= 2;
    update_x_entry = (u16 *)((s32)temp_v1_5 + temp_t0);
    ASM_KEEP(update_x_entry);
    LOAD_TABLE_Y_BASE(temp_t0);
    ASM_KEEP(temp_t0);
    update_y_entry = (u16 *)((s32)temp_v1_5 + temp_t0);
    ASM_KEEP(update_y_entry);
    temp_a0 = var_s4 + *update_x_entry;
    var_s4 = temp_a0;
    temp_v0_5 = var_s6 + *update_y_entry;
    var_s6 = temp_v0_5;
    frame.raw_y = (u16) temp_v0_5;
    ASM_KEEP4_NV(temp_a0, temp_v0_5, var_s4, var_s6);
    var_fp = temp_a0;
    if (var_s0 < 8) {
        goto loop_24;
    }
block_28:
    ASM_SCHED_BARRIER();
    temp_a3 = &frame.out_x;
block_29:
    var_s0 = 1;
    ASM_KEEP(var_s0);
    temp_a1_pre = var_fp << 0x10;
    off_x = (s16 *)D_8006CCD8;
    ASM_KEEP(off_x);
    temp_a1_pre >>= 0xA;
    out_idx = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    ASM_KEEP(out_idx);
    var_a2 = (u16 *)((u8 *)&frame.out_x + 2);
    ASM_KEEP(var_a2);
    offset_x = off_x[out_idx];
    off_y = (s16 *)D_8006CCE8;
    temp_a1_2 = temp_a1_pre + ((offset_x + 1) << 5);
    M2C_FIELD(temp_a3, s16 *, 2) = temp_a1_2;
    signed_a1 = temp_a1_2;
    ASM_KEEP(signed_a1);
    temp_t0 = frame.raw_y;
    out_idx = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    temp_a0_pre = temp_t0 << 0x10;
    ASM_KEEP(out_idx);
    offset_y = off_y[out_idx];
    temp_a0_pre >>= 0xA;
    temp_a0_2 = temp_a0_pre + ((offset_y + 1) << 5);
    M2C_FIELD(temp_a3, s16 *, 6) = temp_a0_2;
    signed_a0 = (s32) ((u16) temp_a0_2 << 0x10);
    temp_v0_6 = M2C_FIELD(arg1, u16 *, 0xA) + 0x20;
    M2C_FIELD(temp_a3, s16 *, 0xA) = temp_v0_6;
    current_x = M2C_FIELD(arg1, s16 *, 2);
    ASM_SCHED_BARRIER();
    signed_a0 >>= 0x10;
    ASM_SCHED_BARRIER();
    var_a1_2 = signed_a1;
    var_a1_2 -= current_x;
    if (var_a1_2 >= 0) {
        goto block_31;
    }
    var_a1_2 = 0 - var_a1_2;
block_31:
    frame.delta[0] = var_a1_2;
    current_y = M2C_FIELD(arg1, s16 *, 6);
    ASM_SCHED_BARRIER();
    signed_v0 = (s32) ((u16) temp_v0_6 << 0x10);
    ASM_SCHED_BARRIER();
    var_a0_2 = signed_a0;
    var_a0_2 -= current_y;
    if (var_a0_2 >= 0) {
        goto block_33;
    }
    var_a0_2 = 0 - var_a0_2;
block_33:
    frame.delta[1] = var_a0_2;
    current_z = M2C_FIELD(arg1, s16 *, 0xA);
    signed_v0 >>= 0x10;
    var_v0_5 = signed_v0;
    var_v0_5 -= current_z;
    if (var_v0_5 >= 0) {
        goto block_35;
    }
    var_v0_5 = 0 - var_v0_5;
block_35:
    frame.delta[2] = var_v0_5;
    M2C_FIELD(arg0, s16 *, 0x12) = var_a1_2;
loop_36:
    if (M2C_FIELD(var_a2, s16 *, 0x18) > M2C_FIELD(arg0, s16 *, 0x12)) {
        M2C_FIELD(arg0, s16 *, 0x12) = M2C_FIELD(var_a2, u16 *, 0x18);
    }
block_38:
    var_s0 += 1;
    var_a2 += 1;
    if (var_s0 < 3) {
        goto loop_36;
    }
    temp_v0_7 = (s32) ((u16) M2C_FIELD(arg0, s16 *, 0x12) << 0x10) >> 0x14;
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) temp_v0_7;
    if (temp_v0_7 != 0) {
        goto block_41;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 1;
block_41:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (M2C_FIELD(temp_a3, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (M2C_FIELD(temp_a3, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) (M2C_FIELD(temp_a3, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, s16 *, 0x12));
    func_80025614(arg0, arg1);
    var_v0_4 = 6;
    goto block_52;
jt_c2:
    case_v0 = M2C_FIELD(arg1, s32 *, 0);
    case_v1 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_a0_3 = M2C_FIELD(arg1, s32 *, 0x10);
    temp_a1_3 = M2C_FIELD(arg1, s32 *, 0x14);
    case_v0 += case_v1;
    M2C_FIELD(arg1, s32 *, 0) = case_v0;
    case_v0 = M2C_FIELD(arg1, s32 *, 4);
    case_v1 = M2C_FIELD(arg1, s32 *, 8);
    case_v0 += temp_a0_3;
    case_v1 += temp_a1_3;
    M2C_FIELD(arg1, s32 *, 4) = case_v0;
    M2C_FIELD(arg1, s32 *, 8) = case_v1;
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_53;
    }
    func_800A56E0(0x300, temp_a1_3);
    goto block_48;
jt_c3:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) >= 0x10) {
        goto block_48;
    }
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    return;
jt_c4:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < 0x30) {
        goto block_53;
    }
    func_80024024(M2C_FIELD(temp_s7, void **, 0x60), M2C_FIELD(arg0, u8 *, 9), temp_s7);
block_48:
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    goto block_53;
jt_c5:
    if (M2C_FIELD(arg0, s16 *, 0x14) != 0) {
        goto block_53;
    }
    D_8008346C = 0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    goto block_53;
jt_c6:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_53;
    }
    var_v0_4 = 5;
block_52:
    M2C_FIELD(arg0, s16 *, 0xA) = var_v0_4;
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
block_53:
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    return;
}
