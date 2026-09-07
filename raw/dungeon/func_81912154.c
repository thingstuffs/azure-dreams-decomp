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
extern void *D_80024028[];
s32 func_80024170(); /* extern */
M2C_UNK func_80025874();         /* extern */
s32 func_8003DE58();     /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s32 func_800A44E0();              /* extern */
s32 func_800A56E0();                     /* extern */
s16 func_800BCB04();                   /* extern */
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern u8 D_800DDC40[];

typedef struct LocalStack {
    u8 motion[0x18];
    u16 distance[4];
    u16 saved_y;
} LocalStack;

void func_80025954(void *arg0, void *arg1_in, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    LocalStack stack;
    s8 *var_a2;
    register s32 temp_a1_2 ASM_REG("$5");
    s16 temp_v0_4;
    s32 temp_v1;
    register s32 temp_v1_6 ASM_REG("$3");
    s32 var_a1;
    s16 var_a1_2;
    register s32 var_v0_4 ASM_REG("$2");
    s16 var_v1;
    s32 temp_v0_2;
    register s32 temp_v0_3 ASM_REG("$2");
    s32 temp_v0_6;
    register s32 temp_v1_5 ASM_REG("$3");
    s32 adjusted_z;
    s32 temp_z;
    register s32 var_s3 ASM_REG("$19");
    s32 var_v0_2;
    s32 var_v0_3;
    u32 temp_v1_3;
    register s32 temp_a0 ASM_REG("$4");
    s32 temp_v0_5;
    s32 var_fp;
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s5 ASM_REG("$21");
    void *temp_a1;
    void *temp_a3;
    register void *temp_s0 ASM_REG("$16");
    register void *temp_s7 ASM_REG("$23");
    register void *temp_v0 ASM_REG("$2");
    void *temp_v1_2;
    register void *temp_v1_4 ASM_REG("$3");
    register void *arg1 ASM_REG("$22") = arg1_in;
    register s16 *x_lookup_first ASM_REG("$3");
    register s16 *y_lookup_first ASM_REG("$2");
    register s16 *x_lookup_next ASM_REG("$2");
    register s16 *y_lookup_next ASM_REG("$3");
    register s32 height ASM_REG("$6");
    register s16 *final_base ASM_REG("$4");
    register s16 *final_ptr ASM_REG("$2");
    register u32 saved_t0 ASM_REG("$8");
    register void *call_a1 ASM_REG("$5");

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    temp_s7 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) (M2C_FIELD(arg0, u16 *, 0x10) + 1);
    if ((u32) temp_v1 >= 7U) {
        goto block_49;
    }
    (void)jt_keep; goto *D_80024028[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) (((u16) M2C_FIELD(temp_s7, u16 *, 0x2A) >> 9) & 7);
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
jt_c1:
    temp_s0 = temp_s7 - 0x20;
    temp_a1 = M2C_FIELD(temp_s0, void **, 0xC);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, stack.distance, 0) != 0) {
        goto block_5;
    }
    if (!(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x14) & 0x8000)) {
        goto block_49;
    }
block_5:
    temp_v1_2 = M2C_FIELD(temp_s0, void **, 8);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_v1_2, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_v1_2, u16 *, 6);
    temp_v1_3 = M2C_FIELD(temp_v1_2, u16 *, 0xA);
    M2C_FIELD(arg1, u16 *, 0xA) = temp_v1_3;
    if (M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x14) & 0x8000) {
        goto block_7;
    }
    M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + stack.distance[0]);
    M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + stack.distance[1]);
    ASM_MEM_BARRIER();
    var_v0_4 = M2C_FIELD(arg1, u16 *, 0xA);
    temp_v1_6 = stack.distance[2];
    var_v0_4 += temp_v1_6;
    goto block_8;
block_7:
    var_v0_4 = temp_v1_3 - 0x40;
block_8:
    M2C_FIELD(arg1, u16 *, 0xA) = var_v0_4;
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_49;
    }
    temp_v0 = M2C_FIELD(temp_s7, void **, 0x60);
    var_s3 = 1;
    if (temp_v0 == NULL) {
        goto block_23;
    }
    temp_a3 = M2C_FIELD(temp_v0, void **, -0x18);
    var_a1 = M2C_FIELD(temp_a3, s16 *, 2);
    var_a1 -= M2C_FIELD(arg1, s16 *, 2);
    if (var_a1 >= 0) {
        goto block_12;
    }
    var_a1 = 0 - var_a1;
block_12:
    stack.distance[0] = (u16) var_a1;
    var_v0_4 = M2C_FIELD(temp_a3, s16 *, 6);
    var_v0_2 = M2C_FIELD(arg1, s16 *, 6);
    ASM_CLOBBER("$6");
    var_a2 = (s8 *) &stack.motion[2];
    ASM_KEEP(var_a2);
    var_v0_4 -= var_v0_2;
    if (var_v0_4 >= 0) {
        goto block_14;
    }
    var_v0_4 = 0 - var_v0_4;
block_14:
    stack.distance[1] = (u16) var_v0_4;
    temp_v1_4 = M2C_FIELD(temp_s7, void **, 0x60);
    temp_v1_6 = D_800DDC40[M2C_FIELD(temp_v1_4, u8 *, 0x13)] << 0x10;
    var_v0_4 = M2C_FIELD(temp_a3, s16 *, 0xA) - temp_v1_6;
    temp_v1_6 = M2C_FIELD(arg1, s16 *, 0xA);
    ASM_KEEP(temp_v1_6);
    temp_v1_6 += 0x300000;
    var_v0_4 -= temp_v1_6;
    if (var_v0_4 >= 0) {
        goto block_16;
    }
    var_v0_4 = 0 - var_v0_4;
block_16:
    stack.distance[2] = (u16) var_v0_4;
    M2C_FIELD(arg0, s16 *, 0x12) = var_a1;
loop_17:
    if (M2C_FIELD(var_a2, s16 *, 0x18) <= M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_19;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) (u16) M2C_FIELD(var_a2, s16 *, 0x18);
block_19:
    var_s3 += 1;
    var_a2 += 2;
    if (var_s3 < 3) {
        goto loop_17;
    }
    temp_v0_2 = (s32) ((u16) M2C_FIELD(arg0, s16 *, 0x12) << 0x10) >> 0x14;
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) temp_v0_2;
    if (temp_v0_2 != 0) {
        goto block_22;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 1;
block_22:
    var_v0_4 = M2C_FIELD(temp_a3, s32 *, 0);
    temp_a0 = M2C_FIELD(arg1, s32 *, 0);
    var_v0_4 -= temp_a0;
    var_v0_4 /= M2C_FIELD(arg0, s16 *, 0x12);
    temp_a0 = M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 0xC) = var_v0_4;
    var_v0_4 = M2C_FIELD(temp_a3, s32 *, 4) - temp_a0;
    var_v0_4 /= M2C_FIELD(arg0, s16 *, 0x12);
    M2C_FIELD(arg1, s32 *, 0x10) = var_v0_4;
    ASM_MEM_BARRIER();
    temp_v1_4 = M2C_FIELD(temp_s7, void **, 0x60);
    var_v0_4 = D_800DDC40[M2C_FIELD(temp_v1_4, u8 *, 0x13)] << 0x10;
    temp_v1_6 = M2C_FIELD(temp_a3, s32 *, 8) - var_v0_4;
    var_v0_4 = M2C_FIELD(arg1, s32 *, 8);
    ASM_KEEP(var_v0_4);
    var_v0_4 += 0x300000;
    temp_v1_6 -= var_v0_4;
    temp_v1_6 /= M2C_FIELD(arg0, s16 *, 0x12);
    call_a1 = arg1;
    ASM_KEEP(call_a1);
    M2C_FIELD(call_a1, s32 *, 0x14) = temp_v1_6;
    ASM_JALDELAY_PIN(temp_v1_6);
    ASM_SCHED_BARRIER();
    func_80024170(arg0, call_a1, var_a2, temp_a3);
    var_v0_4 = (u16) M2C_FIELD(arg0, s16 *, 0xA) + 1;
    goto block_48;
block_23:
    ASM_CLOBBER("$2");
    var_s3 = 0;
    ASM_KEEP(var_s3);
    temp_v1_4 = M2C_FIELD(temp_s0, void **, 0xC);
    ASM_KEEP(temp_v1_4);
    var_v0_4 = 0x80070000;
    ASM_KEEP(var_v0_4);
    var_s4 = M2C_FIELD(temp_v1_4, u8 *, 0x24);
    var_s5 = M2C_FIELD(temp_v1_4, u8 *, 0x25);
    var_fp = var_s4;
    stack.saved_y = (u16) var_s5;
loop_24:
    ASM_SCHED_BARRIER();
    if ((func_800A44E0(((s16) var_s4 << 6) & 0xFFC0, ((s16) var_s5 << 6) & 0xFFC0, M2C_FIELD(temp_s7, s16 *, 0x88), (s16) (M2C_FIELD(arg0, u16 *, 0xE) << 9)) << 0x10) != 0) {
        goto block_28;
    }
    {
        register s16 *lookup_base ASM_REG("$8");
#ifdef NON_MATCHING
        lookup_base = D_8006CCD8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3328);
#endif
        ASM_KEEP_NV(lookup_base);
        temp_v0_3 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
        height = (u16) M2C_FIELD(temp_s7, s16 *, 0x88);
        x_lookup_first = (s16 *) ((temp_v0_3 << 1) + (u32) lookup_base);
        ASM_KEEP(x_lookup_first);
    }
    height = (s16) (height - 0x20);
    ASM_KEEP(height);
    {
        register s16 *lookup_base ASM_REG("$8");
#ifdef NON_MATCHING
        lookup_base = D_8006CCE8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3318);
#endif
        ASM_KEEP_NV(lookup_base);
        y_lookup_first = (s16 *) ((temp_v0_3 << 1) + (u32) lookup_base);
        ASM_KEEP(y_lookup_first);
    }
    temp_v0_4 = func_800BCB04(((((s16) var_s4 + *x_lookup_first) << 6) + 0x20) & 0xFFE0, ((((s16) var_s5 + *y_lookup_first) << 6) + 0x20) & 0xFFE0, height);
    ASM_CLOBBER("$16");
    ASM_CLOBBER("$18");
    ASM_CLOBBER("$7");
    temp_a3 = stack.motion;
    if (temp_v0_4 >= 0x201) {
        goto block_29;
    }
    if ((s16) (temp_v0_4 - (u16) M2C_FIELD(temp_s7, s16 *, 0x88)) < -0x3F) {
        goto block_29;
    }
    {
        register s16 *lookup_base ASM_REG("$8");
#ifdef NON_MATCHING
        lookup_base = D_8006CCD8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3328);
#endif
        ASM_KEEP_NV(lookup_base);
        temp_v1_5 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
        var_s3 += 1;
        x_lookup_next = (s16 *) ((temp_v1_5 << 1) + (u32) lookup_base);
        ASM_KEEP(x_lookup_next);
    }
    {
        register s16 *lookup_base ASM_REG("$8");
#ifdef NON_MATCHING
        lookup_base = D_8006CCE8;
#else
        lookup_base = (s16 *) 0x80070000U;
        ASM_KEEP(lookup_base);
        lookup_base = (s16 *) ((u8 *) lookup_base - 0x3318);
#endif
        ASM_KEEP_NV(lookup_base);
        y_lookup_next = (s16 *) ((temp_v1_5 << 1) + (u32) lookup_base);
        ASM_KEEP(y_lookup_next);
    }
    temp_a0 = var_s4 + (u16) *x_lookup_next;
    var_s4 = temp_a0;
    ASM_KEEP_NV(var_s4);
    var_v0_4 = var_s5 + (u16) *y_lookup_next;
    var_s5 = var_v0_4;
    stack.saved_y = (u16) var_v0_4;
    var_fp = temp_a0;
    if (var_s3 < 8) {
        goto loop_24;
    }
block_28:
    ASM_SCHED_BARRIER();
    temp_a3 = stack.motion;
block_29:
    ASM_SCHED_BARRIER();
    temp_v1_6 = (u32) var_fp << 0x10;
    final_base = D_8006CCD8;
    temp_v1_6 >>= 0xA;
    ASM_SCHED_BARRIER();
    var_v0_4 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    var_v0_4 <<= 1;
    final_ptr = (s16 *) ((u8 *) final_base + var_v0_4);
    final_base = D_8006CCE8;
    var_v0_4 = *final_ptr;
    var_v0_4 = (var_v0_4 + 1) << 5;
    temp_v1_6 += var_v0_4;
    M2C_FIELD(temp_a3, s16 *, 2) = temp_v1_6;
    temp_v1_6 = (u32) temp_v1_6 << 0x10;
    saved_t0 = stack.saved_y;
    var_v0_4 = (s16) M2C_FIELD(arg0, u16 *, 0xE);
    temp_a1_2 = (u32) saved_t0 << 0x10;
    var_v0_4 <<= 1;
    final_ptr = (s16 *) ((u8 *) final_base + var_v0_4);
    var_v0_4 = *final_ptr;
    temp_a1_2 >>= 0xA;
    var_v0_4 = (var_v0_4 + 1) << 5;
    temp_a1_2 += var_v0_4;
    M2C_FIELD(temp_a3, s16 *, 6) = temp_a1_2;
    var_v0_4 = M2C_FIELD(arg1, u16 *, 0xA);
    ASM_KEEP_DEP_NV(temp_v1_6, var_v0_4);
    temp_v1_6 >>= 0x10;
    M2C_FIELD(temp_a3, u16 *, 0xA) = var_v0_4;
    var_v0_4 = M2C_FIELD(arg1, s16 *, 2);
    ASM_KEEP_DEP_NV(temp_a1_2, var_v0_4);
    temp_a1_2 = (u32) temp_a1_2 << 0x10;
    ASM_KEEP(temp_a1_2);
    temp_v1_6 -= var_v0_4;
    if (temp_v1_6 >= 0) {
        goto block_31;
    }
    temp_v1_6 = 0 - temp_v1_6;
block_31:
    stack.distance[0] = temp_v1_6;
    var_v0_4 = M2C_FIELD(arg1, s16 *, 6);
    temp_a1_2 >>= 0x10;
    temp_a1_2 -= var_v0_4;
    if (temp_a1_2 >= 0) {
        goto block_33;
    }
    temp_a1_2 = 0 - temp_a1_2;
block_33:
    stack.distance[1] = temp_a1_2;
    M2C_FIELD(arg0, s16 *, 0x12) = temp_v1_6;
    if ((s16) stack.distance[1] <= (s16) temp_v1_6) {
        goto block_35;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) (u16) stack.distance[1];
block_35:
    var_v0_4 = (s32) ((u16) M2C_FIELD(arg0, s16 *, 0x12) << 0x10) >> 0x14;
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) var_v0_4;
    if (var_v0_4 != 0) {
        goto block_37;
    }
    M2C_FIELD(arg0, s16 *, 0x12) = 1;
block_37:
    var_v0_4 = M2C_FIELD(stack.motion, s32 *, 0);
    temp_a0 = M2C_FIELD(arg1, s32 *, 0);
    var_v0_4 -= temp_a0;
    var_v0_4 /= M2C_FIELD(arg0, s16 *, 0x12);
    temp_a0 = M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 0xC) = var_v0_4;
    var_v0_4 = M2C_FIELD(temp_a3, s32 *, 4) - temp_a0;
    var_v0_4 /= M2C_FIELD(arg0, s16 *, 0x12);
    call_a1 = arg1;
    ASM_KEEP(call_a1);
    M2C_FIELD(call_a1, s32 *, 0x14) = 0;
    M2C_FIELD(call_a1, s32 *, 0x10) = var_v0_4;
    ASM_JALDELAY_PIN(var_v0_4);
    ASM_SCHED_BARRIER();
    func_80024170(arg0, call_a1);
    var_v0_4 = 6;
    goto block_48;
jt_c2:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_49;
    }
    func_80025874(arg0, arg1, M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), s16 *, 0x88));
    func_800A56E0(0x300);
    goto block_44;
jt_c3:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) >= 8) {
        goto block_44;
    }
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    return;
jt_c4:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < 0x44) {
        goto block_49;
    }
    func_8009CE1C(M2C_FIELD(temp_s7, void **, 0x60), 0x18, M2C_FIELD(arg0, u8 *, 9), 1, (s32) (s16) (M2C_FIELD(arg0, u16 *, 0xE) << 9), temp_s7, 1);
block_44:
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    goto block_49;
jt_c5:
    if (M2C_FIELD(arg0, s16 *, 0x14) != 0) {
        goto block_49;
    }
    D_8008346C = 0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    goto block_49;
jt_c6:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x10) < M2C_FIELD(arg0, s16 *, 0x12)) {
        goto block_49;
    }
    var_v0_4 = 5;
block_48:
    M2C_FIELD(arg0, s16 *, 0xA) = var_v0_4;
    M2C_FIELD(arg0, u16 *, 0x10) = 0U;
block_49:
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    return;
}
