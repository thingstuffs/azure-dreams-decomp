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

typedef struct { u8 bytes[8]; } Packed8 __attribute__((packed));
typedef struct { u8 bytes[12]; } Packed12 __attribute__((packed));
typedef struct { u8 bytes[32]; } Packed32 __attribute__((packed));
typedef union {
    Packed8 packed;
    s16 half[6];
} Local28;
typedef union {
    Packed32 packed;
    struct {
        s16 first;
        u16 second;
    } pair[8];
} Local38;

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
extern void *D_80024058[];
M2C_UNK func_8002407C();          /* extern */
M2C_UNK func_800244CC(); /* extern */
M2C_UNK func_80024DB8(); /* extern */
extern void func_80025158(void) __attribute__((noreturn));
extern void func_800252B4(void) __attribute__((noreturn));
extern void func_80025DF4(void) __attribute__((noreturn));
s32 func_8003DE58();     /* extern */
void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
s16 func_80066460(); /* extern */
s32 func_80069EF8();                                /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800B8FC8(); /* extern */
extern Packed8 D_80024028;
extern Packed32 D_80024038;
extern M2C_UNK D_800245EC;
extern M2C_UNK D_800246F8;
extern M2C_UNK D_80024780;
extern M2C_UNK D_8002499C;
extern Packed12 D_80025E28;
extern Packed12 D_80025E34;
extern Packed12 D_80025E40;
extern Packed12 D_80025E58;
extern Packed12 D_80025E70;
extern M2C_UNK D_80025E80;
extern M2C_UNK D_80045340;
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern M2C_UNK D_800814A0;
extern s32 D_8008346C;
extern u8 D_800DDC40[];
extern u8 D_800E3D68;

void func_818FF710(void *arg0, void *arg1, void *arg2) {
    u16 sp20[3];
    Local28 sp28;
    Local38 sp38;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c8 };
    s32 temp_v0_15;
    s32 temp_v1;
    s32 e80;
    void *tmp30;
    void *tmp30b;
    s32 copyw;
    s16 temp_v1_17;
    s32 temp_a3_2;
    M2C_UNK temp_v1_6;
    M2C_UNK temp_v1_7;
    M2C_UNK temp_v1_8;
    s32 var_s0;
    s32 var_s0_2;
    register s32 var_v0_2 ASM_REG("$2");
    register s32 temp_v0 ASM_REG("$2");
    register void *p32 ASM_REG("$2");
    s8 temp_v0_4;
    u16 temp_v0_10;
    u16 temp_v0_12;
    u16 temp_v0_14;
    u16 temp_v0_16;
    u16 temp_v0_17;
    u16 temp_v0_18;
    u16 temp_v0_3;
    u16 tsp20;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_8;
    u16 temp_v1_11;
    u16 temp_v1_16;
    u16 temp_v1_19;
    u16 temp_v1_2;
    u16 temp_v1_5;
    u16 temp_parent_flags;
    u16 var_v0;
    u8 temp_v0_2;
    register s32 temp_v1_4 ASM_REG("$3");
    register u16 flagrl ASM_REG("$3");
    s32 var_a1;
    register void *temp_a0 ASM_REG("$4");
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a1;
    register void *temp_a3 ASM_REG("$7");
    register void *a0v4 ASM_REG("$4");
    register void *a1v4 ASM_REG("$5");
    register void *temp_a3_case1 ASM_REG("$7");
    register void *temp_a3_3 ASM_REG("$7");
    register void *temp_a3_4 ASM_REG("$7");
    register void *temp_a3_5 ASM_REG("$7");
    register void *temp_a3_6 ASM_REG("$7");
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_4;
    register void *temp_s0_6 ASM_REG("$16");
    register void *temp_s0_8 ASM_REG("$16");
    void *temp_s1;
    void *temp_s2;
    register void *temp_s7 ASM_REG("$23");
    register void *temp_v0_11 ASM_REG("$19");
    register void *temp_v0_13 ASM_REG("$18");
    register void *temp_v0_7 ASM_REG("$22");
    register void *temp_v0_9 ASM_REG("$20");
    void *temp_v1_10;
    void *temp_v1_12;
    void *temp_v1_13;
    void *temp_v1_14;
    void *temp_v1_15;
    void *temp_v1_18;
    register void *temp_v1_3 ASM_REG("$3");
    void *temp_v1_9;

    register void *arg0_reg ASM_REG("$21") = arg0;
    register void *arg1_reg ASM_REG("$19") = arg1;
    register void *arg2_reg ASM_REG("$17") = arg2;
    ASM_KEEP_NV(arg0_reg);
    ASM_KEEP_NV(arg1_reg);
    ASM_KEEP_NV(arg2_reg);
#define arg0 arg0_reg
#define arg1 arg1_reg
#define arg2 arg2_reg

    temp_s7 = M2C_FIELD(arg0, void **, 0);
    sp28.packed = D_80024028;
    sp38.packed = D_80024038;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    temp_s0 = temp_s7 - 0x20;
    temp_s2 = M2C_FIELD(temp_s0, void **, 8);
    if ((u32) temp_v1 >= 9U) {
        goto block_66;
    }
    (void)jt_keep; goto *D_80024058[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
    M2C_FIELD(arg0, Packed12 *, 0x96) = D_80025E70;
    M2C_FIELD(arg2, void **, 8) = (void *) (arg0 + 0x96);
    temp_parent_flags = M2C_FIELD(temp_s7, u16 *, 0x2A);
    M2C_FIELD(&D_80025E80, s16 *, 0) = 1;
    M2C_FIELD(arg0, s16 *, 0x7E) = (s16) ((temp_parent_flags >> 9) & 7);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
jt_c1:
    temp_a1 = M2C_FIELD(temp_s0, void **, 0xC);
    if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &sp20[0], 0) != 0) {
        goto block_5;
    }
    if (!(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x14) & 0x8000)) {
        goto block_66;
    }
block_5:
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_s2, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_s2, u16 *, 6);
    temp_v1_2 = M2C_FIELD(temp_s2, u16 *, 0xA);
    M2C_FIELD(arg1, u16 *, 0xA) = temp_v1_2;
    if (!(M2C_FIELD(M2C_FIELD(temp_s0, void **, 0xC), u16 *, 0x14) & 0x8000)) {
        M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + sp20[0]);
        M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + sp20[1]);
        var_v0 = (u16) (M2C_FIELD(arg1, u16 *, 0xA) + sp20[2]);
        ASM_TAILSLOT_PIN(var_v0);
        func_80025158();
    }
    ASM_SCHED_BARRIER();
    var_v0 = (u16) (temp_v1_2 - 0x40);
    M2C_FIELD(arg1, u16 *, 0xA) = var_v0;
    if (M2C_FIELD(arg0, u8 *, 0x7A) & 4) {
        goto block_10;
    }
    func_8004491C(arg0 - 0x20, &D_80045340);
    M2C_FIELD(arg2, s16 *, 0x10) = 0x60;
    M2C_FIELD(arg2, s8 *, 0xE) = 0x14;
    M2C_FIELD(arg2, s8 *, 0xD) = 0x14;
    M2C_FIELD(arg2, s8 *, 0xC) = 0x14;
    M2C_FIELD(arg2, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(arg2, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0xC);
    M2C_FIELD(arg0, u8 *, 0x7A) = (u8) (M2C_FIELD(arg0, u8 *, 0x7A) | 4);
block_10:
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_66;
    }
    temp_v1_3 = M2C_FIELD(temp_s7, void **, 0x60);
    ASM_KEEP_NV(temp_v1_3);
    if (temp_v1_3 == NULL) {
        goto block_17;
    }
    temp_a3_case1 = M2C_FIELD(temp_v1_3, void **, -0x18);
    M2C_FIELD(arg0, s16 *, 0x78) = (s16) (M2C_FIELD(temp_a3_case1, u16 *, 0xA) - (D_800DDC40[M2C_FIELD(temp_v1_3, u8 *, 0x13)] + 0x40));
    temp_a0 = M2C_FIELD(temp_s7, void **, -0x14);
    M2C_FIELD(arg0, s8 *, 0xA2) = (s8) (M2C_FIELD(temp_a0, u8 *, 0x24) + D_8006CCD8[M2C_FIELD(arg0, s16 *, 0x7E) * 2]);
    M2C_FIELD(arg0, s8 *, 0xA3) = (s8) (M2C_FIELD(temp_a0, u8 *, 0x25) + D_8006CCE8[M2C_FIELD(arg0, s16 *, 0x7E) * 2]);
    temp_v0 = M2C_FIELD(temp_s7, s8 *, 0x72);
    temp_v1_4 = M2C_FIELD(temp_a0, u8 *, 0x24);
    if (temp_v0 != temp_v1_4) {
        var_v0_2 = temp_v0 - temp_v1_4;
        goto block_14;
    }
    temp_v0 = M2C_FIELD(temp_s7, s8 *, 0x73);
    temp_v1_4 = M2C_FIELD(temp_a0, u8 *, 0x25);
    var_v0_2 = temp_v0 - temp_v1_4;
block_14:
    if (var_v0_2 >= 0) {
        goto block_16;
    }
    var_v0_2 = 0 - var_v0_2;
block_16:
    M2C_FIELD(arg0, s8 *, 0x7B) = (s8) ((var_v0_2 * 2) - 1);
    func_800252B4();
block_17:
    M2C_FIELD(arg0, s16 *, 0x78) = (s16) (M2C_FIELD(temp_s7, u16 *, 0x88) - 0x50);
    M2C_FIELD(arg0, s8 *, 0x7B) = 0x20;
    ASM_SCHED_BARRIER();
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (sp38.pair[M2C_FIELD(arg0, s16 *, 0x7E)].first << 0x10);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (sp38.pair[M2C_FIELD(arg0, s16 *, 0x7E)].second << 0x10);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) ((M2C_FIELD(arg0, s16 *, 0x78) << 0x10) - M2C_FIELD(arg1, s32 *, 8)) / (s8) M2C_FIELD(arg0, s8 *, 0x7B));
    temp_v0_2 = (u8) M2C_FIELD(arg0, s8 *, 0x7B);
    M2C_FIELD(arg0, u16 *, 0x82) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    M2C_FIELD(arg0, s16 *, 0x88) = (s16) (s8) (u8) M2C_FIELD(arg0, s8 *, 0x7B);
    M2C_FIELD(arg0, s16 *, 0x8A) = (s16) ((s8) temp_v0_2 * (s8) temp_v0_2);
    func_80024DB8(arg0, arg1, arg2);
    func_80025DF4();
    return;
jt_c2:
    var_s0 = 0;
loop_20:
    var_s0 += 1;
    {
        register void *a0v ASM_REG("$4");
        register s32 a1v ASM_REG("$5");
        register s32 a2v ASM_REG("$6");
        register s32 a3v ASM_REG("$7");
        s32 rv;
        rv = func_80069EF8();
        a0v = arg0 - 0x20;
        a2v = 0x2020E0;
        ASM_KEEP_NV(a2v);
        a3v = (rv & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);
        a1v = M2C_FIELD(arg0, s16 *, 0x7E);
        func_800244CC(a0v, a1v, a2v, a3v, 0, 0, 0);
    }
    if (var_s0 < 4) {
        goto loop_20;
    }
    temp_v1_5 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_v0_3 = temp_v1_5 + 0x190;
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v0_3;
    if ((u32) (temp_v0_3 & 0xFFFF) < 0x1001U) {
        goto block_23;
    }
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (temp_v1_5 - 0xE70);
block_23:
    temp_v1_6 = (M2C_FIELD(arg0, s16 *, 0x88) - M2C_FIELD(arg0, s8 *, 0x7B)) + 1;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) (((s32) (temp_v1_6 * temp_v1_6 * 0x6C) / (s16) M2C_FIELD(arg0, s16 *, 0x8A)) + 0x14);
    temp_v1_7 = (M2C_FIELD(arg0, s16 *, 0x88) - M2C_FIELD(arg0, s8 *, 0x7B)) + 1;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) (((s32) (temp_v1_7 * temp_v1_7 * 0x6C) / (s16) M2C_FIELD(arg0, s16 *, 0x8A)) + 0x14);
    temp_v1_8 = (M2C_FIELD(arg0, s16 *, 0x88) - M2C_FIELD(arg0, s8 *, 0x7B)) + 1;
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) (((s32) (temp_v1_8 * temp_v1_8 * 0x6C) / (s16) M2C_FIELD(arg0, s16 *, 0x8A)) + 0x14);
    if ((func_800A4778(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA), M2C_FIELD(temp_s7, void **, 0x60)) << 0x10) == 0) {
        goto block_25;
    }
    M2C_FIELD(arg0, s16 *, 0xA) = 8;
    M2C_FIELD(arg0, u16 *, 0x82) = 0U;
    M2C_FIELD(arg2, s8 *, 0xE) = 0;
    M2C_FIELD(arg2, s8 *, 0xD) = 0;
    M2C_FIELD(arg2, s8 *, 0xC) = 0;
    func_80025DF4();
    return;
block_25:
    temp_v0_4 = (u8) M2C_FIELD(arg0, s8 *, 0x7B) - 1;
    M2C_FIELD(arg0, s8 *, 0x7B) = temp_v0_4;
    if ((temp_v0_4 << 0x18) > 0) {
        goto block_31;
    }
    if (M2C_FIELD(temp_s7, void **, 0x60) == NULL) {
        goto block_30;
    }
    M2C_FIELD(arg0, s16 *, 0xA) = 3;
    M2C_FIELD(arg0, u16 *, 0x82) = 0U;
    func_800A56E0(0x300);
    temp_v1_9 = M2C_FIELD(temp_s7, void **, 0x60);
    temp_v1_10 = M2C_FIELD(temp_v1_9, void **, -0x14);
    if ((u32) (M2C_FIELD(temp_v1_9, u8 *, 0x13) - 0x33) < 4U) {
        goto block_29;
    }
    M2C_FIELD(temp_v1_10, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1_10, u16 *, 0x14) | 0x800);
    temp_a0_2 = M2C_FIELD(temp_s7, void **, 0x60);
    M2C_FIELD(temp_a0_2, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 0x14) | 0x100000);
block_29:
    temp_a3 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x18);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_a3, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_a3, u16 *, 6);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, s16 *, 0x78);
    func_80024DB8(arg0, arg1, arg2, temp_a3);
    func_80025DF4();
    return;
block_30:
    M2C_FIELD(arg0, s16 *, 0xA) = 8;
    M2C_FIELD(arg0, u16 *, 0x82) = 0U;
    M2C_FIELD(arg2, s8 *, 0xE) = 0;
    M2C_FIELD(arg2, s8 *, 0xD) = 0;
    M2C_FIELD(arg2, s8 *, 0xC) = 0;
    func_80024DB8(arg0, arg1, arg2);
    func_80025DF4();
    return;
block_31:
    temp_a3 = M2C_FIELD(arg1, void **, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + (s32) temp_a3);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    func_80024DB8(arg0, arg1, arg2, temp_a3);
    func_80025DF4();
    return;
jt_c3: {
    s32 temp_fp;
    register s32 cv ASM_REG("$2");
    register s16 *sp28_0 ASM_REG("$20");
    register s16 *sp28_4 ASM_REG("$19");
    register s16 *b1 ASM_REG("$5");
    register s16 *b2 ASM_REG("$6");
    s32 c880;
    s32 c84;
    s32 c832;
    temp_v1_11 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_v0_5 = temp_v1_11 + 0x190;
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v0_5;
    if ((u32) (temp_v0_5 & 0xFFFF) < 0x1001U) {
        goto block_34;
    }
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (temp_v1_11 - 0xE70);
block_34:
    func_80024DB8(arg0, arg1, arg2);
    temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x82) + 1;
    M2C_FIELD(arg0, u16 *, 0x82) = temp_v0_6;
    if ((s16) temp_v0_6 != 1) {
        goto block_36;
    }
    sp28_0 = &sp28.half[0];
    b1 = sp28_0;
    sp28_4 = &sp28.half[4];
    b2 = sp28_4;
    ASM_KEEP_NV(b1);
    ASM_KEEP_NV(b2);
    ASM_SET(c832);
    ASM_SET(c84);
    ASM_SET(c880);
    c832 = 0x340;
    cv = 0x154;
    sp28.half[1] = (s16) cv;
    cv = 0x60;
    sp28.half[2] = (s16) cv;
    c84 = 0x54;
    c880 = 0x370;
    sp28.half[0] = (s16) c832;
    sp28.half[3] = (s16) c84;
    sp28.half[4] = (s16) c880;
    cv = 0x19A;
    sp28.half[5] = (s16) cv;
    func_800B8FC8(M2C_FIELD(temp_s7, void **, 0x60), b1, b2, 1, (s32) (s16) temp_v0_6);
    b1 = sp28_0;
    b2 = sp28_4;
    ASM_KEEP_NV(b1);
    ASM_KEEP_NV(b2);
    cv = 0x1A8;
    sp28.half[1] = (s16) cv;
    cv = 0x60;
    sp28.half[2] = (s16) cv;
    sp28.half[0] = (s16) c832;
    sp28.half[3] = (s16) c84;
    sp28.half[4] = (s16) c880;
    cv = 0x1EF;
    sp28.half[5] = (s16) cv;
    func_800B8FC8(M2C_FIELD(temp_s7, void **, 0x60), b1, b2, 1, (s32) (s16) temp_v0_6);
block_36:
    temp_fp = (s16) M2C_FIELD(arg0, u16 *, 0x82);
    ASM_KEEP_NV(temp_fp);
    if (temp_fp != 4) {
        goto block_66;
    }
    temp_v0_7 = func_8003FC64(0x212);
    temp_s1 = temp_v0_7 + 0x20;
    if (temp_v0_7 == NULL) {
        goto block_39;
    }
    M2C_FIELD(temp_s1, s16 *, 2) = 0x78;
    M2C_FIELD(temp_v0_7, M2C_UNK **, 0x10) = &D_800246F8;
    func_8004491C(temp_v0_7, &D_80045340);
    temp_s0_2 = M2C_FIELD(temp_v0_7, void **, 0xC);
    M2C_FIELD(temp_s0_2, s16 *, 6) = 0;
    M2C_FIELD(temp_s0_2, u16 *, 0x14) |= 0xC;
    M2C_FIELD(temp_s0_2, s16 *, 0x10) = 0x40;
    flagrl = M2C_FIELD(temp_s0_2, u16 *, 0x14);
    M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (flagrl | 0x80);
    temp_v1_12 = M2C_FIELD(temp_v0_7, void **, 8);
    M2C_FIELD(temp_s1, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s1, s16 *, 0xC) = 0;
    temp_a3_3 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x18);
    M2C_FIELD(temp_v1_12, s32 *, 0) = (s32) M2C_FIELD(temp_a3_3, s32 *, 0);
    M2C_FIELD(temp_v1_12, s32 *, 4) = (s32) M2C_FIELD(temp_a3_3, s32 *, 4);
    M2C_FIELD(temp_v1_12, s32 *, 8) = (s32) M2C_FIELD(temp_a3_3, s32 *, 8);
    temp_s0_2 = M2C_FIELD(temp_v0_7, void **, 0xC);
    M2C_FIELD(temp_s0_2, s16 *, 0x1C) = 0x1004;
    M2C_FIELD(temp_s0_2, s16 *, 0x1E) = 0x1004;
    M2C_FIELD(temp_s0_2, s16 *, 0x22) = (s16) ((s32) (0 - D_800DDC40[M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), u8 *, 0x13)]) / 2);
    M2C_FIELD(temp_s0_2, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0_2, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0_2, u8 *, 0xC) = 0x80;
    M2C_FIELD(temp_v0_7, Packed12 *, 0x40) = D_80025E34;
    M2C_FIELD(temp_s0_2, void **, 8) = (void *) (temp_v0_7 + 0x40);
    M2C_FIELD(M2C_FIELD(temp_s0_2, void **, 8), s16 *, 4) = func_80066460(2, 2, 0x340, 0x154);
block_39:
    temp_v0_9 = func_8003FC64(0x212);
    temp_s1 = temp_v0_9 + 0x20;
    if (temp_v0_9 == NULL) {
        goto block_41;
    }
    M2C_FIELD(temp_s1, s16 *, 2) = 0x78;
    M2C_FIELD(temp_v0_9, M2C_UNK **, 0x10) = &D_80024780;
    func_8004491C(temp_v0_9, &D_80045340);
    temp_s0_4 = M2C_FIELD(temp_v0_9, void **, 0xC);
    M2C_FIELD(temp_s0_4, u16 *, 0x14) &= 0xFFF3;
    M2C_FIELD(temp_s0_4, s16 *, 0x10) = 0x20;
    M2C_FIELD(temp_s0_4, u16 *, 0x14) |= 0x80;
    M2C_FIELD(temp_s1, void **, 0x2C) = temp_s7;
    tmp30 = M2C_FIELD(temp_s7, void **, 0x60);
    M2C_FIELD(temp_s1, void **, 0x34) = arg0;
    M2C_FIELD(temp_s1, void **, 0x30) = tmp30;
    M2C_FIELD(temp_s0_4, s16 *, 6) = 0;
    temp_v1_13 = M2C_FIELD(temp_v0_9, void **, 8);
    M2C_FIELD(temp_s1, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s1, s16 *, 0xC) = 0;
    temp_a3_4 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x18);
    M2C_FIELD(temp_v1_13, s32 *, 0) = (s32) M2C_FIELD(temp_a3_4, s32 *, 0);
    M2C_FIELD(temp_v1_13, s32 *, 4) = (s32) M2C_FIELD(temp_a3_4, s32 *, 4);
    M2C_FIELD(temp_v1_13, s32 *, 8) = (s32) M2C_FIELD(temp_a3_4, s32 *, 8);
    temp_s0_4 = M2C_FIELD(temp_v0_9, void **, 0xC);
    M2C_FIELD(temp_s0_4, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0_4, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s0_4, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0_4, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0_4, u8 *, 0xC) = 0x80;
    M2C_FIELD(temp_v0_9, Packed12 *, 0x40) = D_80025E40;
    M2C_FIELD(temp_s0_4, void **, 8) = (void *) (temp_v0_9 + 0x40);
    M2C_FIELD(M2C_FIELD(temp_s0_4, void **, 8), s16 *, 4) = func_80066460(2, 1, 0x340, 0x1A8);
block_41:
    temp_v0_11 = func_8003FC64(0x212);
    temp_s1 = temp_v0_11 + 0x20;
    if (temp_v0_11 == NULL) {
        goto block_43;
    }
    M2C_FIELD(temp_s1, s16 *, 2) = 0x78;
    M2C_FIELD(temp_v0_11, M2C_UNK **, 0x10) = &D_800245EC;
    func_8004491C(temp_v0_11, &D_80045340);
    temp_s0_6 = M2C_FIELD(temp_v0_11, void **, 0xC);
    M2C_FIELD(temp_s0_6, s16 *, 6) = 0;
    M2C_FIELD(temp_s0_6, u16 *, 0x14) &= 0xFFF3;
    M2C_FIELD(temp_s0_6, s16 *, 0x10) = 0x20;
    flagrl = M2C_FIELD(temp_s0_6, u16 *, 0x14);
    M2C_FIELD(temp_s0_6, u16 *, 0x14) = (u16) (flagrl | 0x80);
    temp_v1_14 = M2C_FIELD(temp_v0_11, void **, 8);
    M2C_FIELD(temp_s1, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s1, s16 *, 0xC) = 0;
    temp_a3_5 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x18);
    M2C_FIELD(temp_v1_14, s32 *, 0) = (s32) M2C_FIELD(temp_a3_5, s32 *, 0);
    M2C_FIELD(temp_v1_14, s32 *, 4) = (s32) M2C_FIELD(temp_a3_5, s32 *, 4);
    M2C_FIELD(temp_v1_14, s32 *, 8) = (s32) M2C_FIELD(temp_a3_5, s32 *, 8);
    temp_s0_6 = M2C_FIELD(temp_v0_11, void **, 0xC);
    M2C_FIELD(temp_s0_6, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0_6, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0_6, u8 *, 0xC) = 0x80;
    M2C_FIELD(temp_s0_6, s16 *, 0x1E) = 0;
    M2C_FIELD(temp_s0_6, s16 *, 0x1C) = 0;
    M2C_FIELD(temp_v0_11, Packed12 *, 0x40) = D_80025E58;
    M2C_FIELD(temp_s0_6, void **, 8) = (void *) (temp_v0_11 + 0x40);
block_43:
    temp_v0_13 = func_8003FC64(0x212);
    temp_s1 = temp_v0_13 + 0x20;
    if (temp_v0_13 == NULL) {
        goto block_45;
    }
    a0v4 = temp_v0_13;
    a1v4 = (void *) &D_80045340;
    ASM_KEEP_NV(a1v4);
    M2C_FIELD(temp_s1, void **, 0x2C) = temp_s7;
    tmp30b = M2C_FIELD(temp_s7, void **, 0x60);
    p32 = (void *) (temp_v0_7 + 0x20);
    M2C_FIELD(temp_s1, void **, 0x38) = p32;
    p32 = (void *) (temp_v0_11 + 0x20);
    M2C_FIELD(temp_s1, void **, 0x3C) = p32;
    p32 = (void *) (temp_v0_9 + 0x20);
    M2C_FIELD(temp_s1, void **, 0x40) = p32;
    M2C_FIELD(temp_s1, void **, 0x34) = arg0;
    M2C_FIELD(temp_s1, void **, 0x30) = tmp30b;
    M2C_FIELD(temp_v0_13, M2C_UNK **, 0x10) = &D_8002499C;
    func_8004491C(a0v4, a1v4);
    temp_s0_8 = M2C_FIELD(temp_v0_13, void **, 0xC);
    M2C_FIELD(temp_s0_8, s16 *, 6) = 0;
    M2C_FIELD(temp_s0_8, u16 *, 0x14) |= 0xC;
    M2C_FIELD(temp_s0_8, s16 *, 0x10) = 0x20;
    flagrl = M2C_FIELD(temp_s0_8, u16 *, 0x14);
    M2C_FIELD(temp_s0_8, u16 *, 0x14) = (u16) (flagrl | 0x80);
    temp_v1_15 = M2C_FIELD(temp_v0_13, void **, 8);
    M2C_FIELD(temp_s1, s16 *, 0xA) = 0;
    M2C_FIELD(temp_s1, s16 *, 0xC) = 0;
    temp_a3_6 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x18);
    M2C_FIELD(temp_v1_15, s32 *, 0) = (s32) M2C_FIELD(temp_a3_6, s32 *, 0);
    M2C_FIELD(temp_v1_15, s32 *, 4) = (s32) M2C_FIELD(temp_a3_6, s32 *, 4);
    M2C_FIELD(temp_v1_15, s32 *, 8) = (s32) M2C_FIELD(temp_a3_6, s32 *, 8);
    temp_s0_8 = M2C_FIELD(temp_v0_13, void **, 0xC);
    M2C_FIELD(temp_s0_8, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0_8, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s0_8, u8 *, 0xE) = 0x80;
    M2C_FIELD(temp_s0_8, u8 *, 0xD) = 0x80;
    M2C_FIELD(temp_s0_8, u8 *, 0xC) = 0x80;
    M2C_FIELD(temp_v0_13, Packed12 *, 0x40) = D_80025E28;
    M2C_FIELD(temp_s0_8, void **, 8) = (void *) (temp_v0_13 + 0x40);
    ASM_KEEP(temp_v0_13);
block_45:
    temp_v0_15 = (s16) M2C_FIELD(arg0, u16 *, 0x82);
    if (temp_v0_15 != temp_fp) {
        goto block_66;
    }
    M2C_FIELD(arg0, s16 *, 0xA) = temp_v0_15;
    M2C_FIELD(arg0, u16 *, 0x82) = 0U;
    M2C_FIELD(arg0, s16 *, 0x90) = 0;
    func_80025DF4();
    return;
}
jt_c4:
    var_s0_2 = 0;
    M2C_FIELD(arg0, u16 *, 0x82) = (u16) (M2C_FIELD(arg0, u16 *, 0x82) + 1);
loop_48:
    var_s0_2 += 1;
    {
        register void *a0v ASM_REG("$4");
        register s32 a1v ASM_REG("$5");
        register s32 a2v ASM_REG("$6");
        register s32 a3v ASM_REG("$7");
        s32 rv;
        rv = func_80069EF8();
        a0v = arg0 - 0x20;
        a2v = 0x2020E0;
        ASM_KEEP_NV(a2v);
        a3v = (rv & 0xFF) | 0x80;
        ASM_KEEP_NV(a3v);
        a1v = M2C_FIELD(arg0, s16 *, 0x7E);
        func_800244CC(a0v, a1v, a2v, a3v, 0, 0, 0);
    }
    if (var_s0_2 < 3) {
        goto loop_48;
    }
    temp_v1_16 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_v0_16 = temp_v1_16 + 0x190;
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v0_16;
    if ((u32) (temp_v0_16 & 0xFFFF) < 0x1001U) {
        goto block_51;
    }
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (temp_v1_16 - 0xE70);
block_51:
    temp_v1_17 = (s16) M2C_FIELD(arg0, u16 *, 0x82);
    if (temp_v1_17 < 0x51) {
        goto block_53;
    }
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) (((0x64 - temp_v1_17) << 7) / 20);
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) (((0x64 - (s16) M2C_FIELD(arg0, u16 *, 0x82)) << 7) / 20);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) (((0x64 - (s16) M2C_FIELD(arg0, u16 *, 0x82)) << 7) / 20);
block_53:
    func_80024DB8(arg0, arg1, arg2);
    if ((s16) M2C_FIELD(arg0, u16 *, 0x82) >= 0x64) {
        goto block_59;
    }
    func_80025DF4();
    return;
jt_c5:
    if (M2C_FIELD(arg0, s16 *, 0x90) == 0) {
        goto block_66;
    }
    var_a1 = 0xFF;
    if (D_800E3D68 == 0xFF) {
        goto block_58;
    }
    var_a1 = M2C_FIELD(arg0, u8 *, 9);
block_58:
    func_8002407C(M2C_FIELD(temp_s7, void **, 0x60), var_a1, temp_s7);
block_59:
    M2C_FIELD(arg0, u16 *, 0x82) = 0U;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
    func_80025DF4();
    return;
jt_c6:
    temp_v0_17 = M2C_FIELD(arg0, u16 *, 0x82) + 1;
    M2C_FIELD(arg0, u16 *, 0x82) = temp_v0_17;
    if ((s16) temp_v0_17 < 0x1F) {
        goto block_66;
    }
    temp_v1_18 = M2C_FIELD(M2C_FIELD(temp_s7, void **, 0x60), void **, -0x14);
    M2C_FIELD(temp_v1_18, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1_18, u16 *, 0x14) & 0xF7FF);
    temp_a0_3 = M2C_FIELD(temp_s7, void **, 0x60);
    M2C_FIELD(temp_a0_3, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a0_3, s32 *, 0x14) & 0xFFEFFFFF);
    M2C_FIELD(arg0, s16 *, 0xA) = 8;
    M2C_FIELD(arg0, u16 *, 0x82) = 0x1EU;
    func_80025DF4();
    return;
jt_c8:
    temp_v1_19 = M2C_FIELD(arg0, u16 *, 0x82);
    temp_v0_18 = temp_v1_19 + 1;
    M2C_FIELD(arg0, u16 *, 0x82) = temp_v0_18;
    if ((s16) temp_v0_18 < 0x1F) {
        goto block_66;
    }
    e80 = (s32) M2C_FIELD(&D_80025E80, s16 *, 0);
    M2C_FIELD(arg0, u16 *, 0x82) = temp_v1_19;
    if (e80 != 0) {
        goto block_65;
    }
    D_8008346C = 0;
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    func_80025DF4();
    return;
block_65:
    (*(s16 *)&D_80025E80) = 0;
block_66:
    return;
}
