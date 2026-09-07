/* cfail-repair: tf7-phase1-cache-v3 */
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
typedef struct { u32 v; } __attribute__((packed)) UA32;
typedef struct { UA32 word[8]; } __attribute__((packed)) Table32;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define SP1_X(a) M2C_FIELD((u8 *)&sp18 + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP1_Y(a) M2C_FIELD((u8 *)&sp18 + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP2_X(a) M2C_FIELD((u8 *)&sp38 + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP2_Y(a) M2C_FIELD((u8 *)&sp38 + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP1_X_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP1_Y_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)
#define SP2_X_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), s16 *, 0)
#define SP2_Y_AT(base, a) M2C_FIELD((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C), u16 *, 2)


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

void func_80041094(); /* extern */
void func_80047738();              /* extern */
void func_80047784();         /* extern */
void func_800478B8();  /* extern */
s32 func_800644B8();                     /* extern */
void func_800945E8();                 /* extern */
void func_800948BC();                            /* extern */
void func_800A56E0();             /* extern */
s32 func_800F685C();                      /* extern */
void func_80166F3C();             /* extern */
void func_8016738C();                      /* extern */
void func_801676CC();                      /* extern */
void func_801677FC();                  /* extern */
void func_8016F5D8();      /* extern */
void func_8016F79C();      /* extern */
void func_801715D0();                            /* extern */
void func_80173008() __attribute__((noreturn));                            /* extern */
void func_80173018() __attribute__((noreturn));                  /* extern */
void func_8017301C() __attribute__((noreturn));              /* extern */
void func_80173074() __attribute__((noreturn));                 /* extern */
void func_80173080() __attribute__((noreturn));                  /* extern */
void func_80173084() __attribute__((noreturn));                            /* extern */
void func_80173110() __attribute__((noreturn));                            /* extern */
extern u8 D_8006CCF8[16];
extern u16 D_80082E76[8];
extern s16 D_80083228[8];
extern s32 D_8008333C[8192];
extern u16 D_80083460[8];
extern s32 D_80083780[8192];
extern s32 D_800E3D7C[3];
extern Table32 D_8016482C;
extern Table32 D_80164AC0;
extern void *D_80164AE0[];
extern u8 D_80173DA4[16];
extern u8 D_80173DAC[16];
extern u8 D_80173DB4[16];
extern void *D_80175D50[3];
extern void *D_80175D54[3];
extern void *D_80175DB8[16];

void func_80171D74(void *arg0_in, void *arg1_in, void *arg2_in) {
    Table32 sp18;
    Table32 sp38;
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13,
        &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20,
        &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c24, &&jt_c25, &&jt_c26, &&jt_c27,
        &&jt_c28, &&jt_c29, &&jt_c30, &&jt_c31, &&jt_c32, &&jt_c33, &&jt_c34,
        &&jt_c35, &&jt_c36, &&jt_c37, &&jt_c38, &&jt_c39, &&jt_c40, &&jt_c41,
        &&jt_c42, &&jt_c43, &&jt_c44, &&jt_c45, &&jt_c46, &&jt_c47, &&jt_c48
    };
    register M2C_UNK *var_v0_2 ASM_REG("$2");
    s16 temp_a0_11;
    s16 temp_a0_13;
    s16 temp_a0_5;
    s16 temp_s2_2;
    s16 temp_v1_2;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 var_v1_6;
    s16 var_v1_8;
    s32 temp_a1_4;
    s32 temp_a1_8;
    register void *arg0 ASM_REG("$17");
    register void *arg1 ASM_REG("$16");
    register void *arg2 ASM_REG("$22");
    register Table32 *copy_base ASM_REG("$6");
    register s32 *base833c ASM_REG("$21");
    register s32 temp_s2 ASM_REG("$18");
    register u8 tail_phase ASM_REG("$2");
    register void *tail_call_arg ASM_REG("$4");
    s32 temp_v1_3;
    u16 temp_a0_12;
    u16 temp_a0_14;
    u16 temp_a0_2;
    u16 temp_a0_4;
    u16 temp_a0_7;
    u16 temp_a0_8;
    u16 temp_v0;
    u16 temp_v0_10;
    u16 temp_v0_11;
    u16 temp_v0_21;
    u16 temp_v0_22;
    u16 temp_v0_23;
    u16 temp_v0_24;
    u16 temp_v0_25;
    u16 temp_v0_26;
    u16 temp_v0_27;
    u16 temp_v0_28;
    u16 temp_v0_29;
    u16 temp_v0_2;
    u16 temp_v0_30;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;
    u16 temp_v1;
    u16 var_v1;
    u16 var_v1_3;
    u16 var_v1_4;
    u16 var_v1_5;
    u16 var_v1_7;
    u16 var_v1_9;
    s32 temp_a0;
    s32 temp_a0_10;
    s32 temp_a0_9;
    void *temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_a1_7;
    void *temp_s3;
    register void *temp_s4 ASM_REG("$20");
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_14;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_17;
    void *temp_v0_18;
    void *temp_v0_19;
    void *temp_v0_20;
    s32 temp_v1_4;
    s32 temp_v1_5;

    arg0 = arg0_in;
    arg1 = arg1_in;
    arg2 = arg2_in;
    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg1);
    ASM_KEEP_NV(arg2);
    copy_base = &D_8016482C;
    sp18 = *copy_base;
    copy_base = &D_80164AC0;
    sp38 = *copy_base;
    base833c = D_8008333C;
    temp_s2 = M2C_FIELD(D_8008333C, s32 *, 0);
    temp_s3 = D_80175D54[0] + 0x20;
    func_800478B8(arg2);
    temp_a0 = M2C_FIELD(arg0, u8 *, 0x9A);
    temp_s4 = M2C_FIELD(D_80175D50[0], void **, 8);
    temp_a1_2 = D_80175D50[0] + 0x20;
    if ((u32)temp_a0 >= 49U) {
        goto block_152;
    }
    (void)jt_keep;
    goto *D_80164AE0[(u32)temp_a0];
jt_c0:
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0 + 1);
        if ((s16) temp_v0 >= 0x1E) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) 0xFFF80000;
            func_80173018();
            return;
        }
        goto block_147;
jt_c1:
        M2C_FIELD(arg1, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10);
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x38) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_8017301C();
            return;
        }
        goto block_147;
jt_c2:
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg0, u16 *, 0x96) = (u16) (temp_v0_3 + 1);
        if ((s16) temp_v0_3 >= 0x1E) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            func_80173018();
            return;
        }
        goto block_147;
jt_c3:
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
        if ((s16) temp_v0_4 == 3) {
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x200);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 4) {
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x200);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0x12) {
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x2A) - 0x200);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0x14) {
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x2A) - 0x200);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0x1E) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) 0xFFF80000;
            func_8017301C();
            return;
        }
        goto block_147;
jt_c4:
        M2C_FIELD(arg1, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10);
        temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_5;
        if ((s16) temp_v0_5 >= 0x10) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_8017301C();
            return;
        }
        goto block_147;
jt_c6:
        M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173DAC;
        func_80047784(arg2, D_80173DAC[((s32) (M2C_FIELD(D_80083228, s16 *, 0) + (s16) M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x100) >> 9) & 7], 3);
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) 0x00020000;
        func_80173080();
        return;
jt_c7:
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_6;
        if ((s16) temp_v0_6 >= 8) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
            M2C_FIELD(arg1, s16 *, 6) = 1;
            M2C_FIELD(arg1, u16 *, 2) = 1U;
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 3) {
            register u32 tail_page7 ASM_REG("$2");
            func_80166F3C(temp_s4, 0);
            func_80166F3C(temp_s4, 1);
            func_8016738C(temp_s4);
            func_801676CC(temp_s4);
            tail_page7 = 0x80170000;
            ASM_PAGEBASE_PIN(tail_page7);
            func_80173084();
            return;
        }
        goto block_152;
jt_c9:
        func_801677FC(temp_a0, temp_a1_2);
        tail_phase = M2C_FIELD(arg0, u8 *, 0x9A);
        ASM_KEEP(tail_phase);
        M2C_FIELD(arg0, u16 *, 0x96) = 0;
        func_80173074();
        return;
jt_c10:
        temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_7;
        if ((s16) temp_v0_7 >= 2) {
            u8 *sp1_base = (u8 *)&sp18;
            u8 *sp2_base;
            register s32 angle_input ASM_REG("$3");
            register s32 angle_tmp ASM_REG("$4");
            register s32 angle_result ASM_REG("$3");
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFF7F);
            M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(temp_s4, u16 *, 2) + (SP1_X_AT(sp1_base, M2C_FIELD(temp_a1_2, u16 *, 0x2A)) * 0x28));
            M2C_FIELD(arg1, s16 *, 6) = (s16) (M2C_FIELD(temp_s4, u16 *, 6) + ((s16) SP1_Y_AT(sp1_base, M2C_FIELD(temp_a1_2, u16 *, 0x2A)) * 0x28));
            M2C_FIELD(arg0, s16 *, 0x92) = -0x18;
            M2C_FIELD(arg0, s16 *, 0x9E) = 0;
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
            angle_input = M2C_FIELD(temp_a1_2, u16 *, 0x2A);
            ASM_KEEP(angle_input);
            angle_tmp = angle_input - 0x400;
            ASM_KEEP(angle_tmp);
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            ASM_KEEP(angle_result);
            M2C_FIELD(temp_s3, u16 *, 0x2A) = angle_result;
            M2C_FIELD(arg0, s16 *, 0x94) = 1;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173DB4;
            func_80047784(arg2, D_80173DB4[((s32) (M2C_FIELD(D_80083228, s16 *, 0) + (s16) M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            sp2_base = (u8 *)&sp38;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (0 - (SP2_X_AT(sp2_base, M2C_FIELD(temp_s3, u16 *, 0x2A)) << 0x10));
            M2C_FIELD(arg1, s32 *, 0x10) = (void *) (0 - (SP2_Y_AT(sp2_base, M2C_FIELD(temp_s3, u16 *, 0x2A)) << 0x10));
            func_801715D0();
            tail_call_arg = arg0;
            ASM_TAILSLOT_PIN(tail_call_arg);
            func_8017301C();
            return;
        }
        goto block_152;
jt_c11:
        {
            s32 pos_x = M2C_FIELD(arg1, s32 *, 0);
            s32 vel_x = M2C_FIELD(arg1, s32 *, 0xC);
            s32 pos_y = M2C_FIELD(arg1, s32 *, 4);
            s32 vel_y = M2C_FIELD(arg1, s32 *, 0x10);
            M2C_FIELD(arg1, s32 *, 0) = pos_x + vel_x;
            M2C_FIELD(arg1, s32 *, 4) = pos_y + vel_y;
        }
        temp_v0_8 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_8;
        if ((s16) temp_v0_8 >= 0x14) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            func_8017301C();
            return;
        }
        goto block_147;
jt_c13:
        temp_v1 = M2C_FIELD(temp_s3, u16 *, 0x2A);
        temp_v0_9 = temp_v1 + 0x200;
        M2C_FIELD(temp_s3, u16 *, 0x2A) = temp_v0_9;
        if ((s16) temp_v0_9 >= 0x1000) {
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) (temp_v1 - 0xE00);
        }
        M2C_FIELD(arg0, u16 *, 0x96) = 0U;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        M2C_FIELD(temp_a1_2, u8 *, 0x27) = 3;
        func_80173018();
        return;
jt_c15:
        M2C_FIELD(arg0, u16 *, 0x96) = 0x1EU;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        /* fallthrough */
jt_c16:
        {
            s32 target_x = M2C_FIELD(&D_80083780, volatile s32 *, 0);
            temp_a1_4 = M2C_FIELD(arg1, volatile s32 *, 0);
            M2C_FIELD(arg1, s32 *, 0xC) = (target_x - temp_a1_4) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
        }
        {
            s32 next_y = (M2C_FIELD(&D_80083780, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
            s32 vel_x = M2C_FIELD(arg1, volatile s32 *, 0xC);
            s32 pos_y = M2C_FIELD(arg1, volatile s32 *, 4);
            s32 next_x;
            M2C_FIELD(arg1, volatile s32 *, 0x10) = next_y;
            next_x = temp_a1_4;
            temp_a1_4 = M2C_FIELD(arg1, volatile s32 *, 0x10);
            M2C_FIELD(arg1, s32 *, 0) = next_x + vel_x;
            M2C_FIELD(arg1, s32 *, 4) = pos_y + temp_a1_4;
        }
        temp_v0_10 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_10;
        if ((temp_v0_10 << 0x10) <= 0) {
            register u8 *sp2_base16 ASM_REG("$3");
            register s32 angle_input16 ASM_REG("$3");
            register s32 angle_tmp16 ASM_REG("$4");
            register s32 angle_result16 ASM_REG("$3");
            register u32 angle_index16 ASM_REG("$2");
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(D_80175DB8[0], s16 *, 0x32) = 3;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173DA4;
            func_80047784(arg2, D_80173DA4[((s32) (M2C_FIELD(D_80083228, s16 *, 0) + (s16) M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            angle_input16 = M2C_FIELD(temp_s3, u16 *, 0x2A);
            ASM_KEEP_NV(angle_input16);
            angle_tmp16 = angle_input16 + 0x200;
            ASM_KEEP_NV(angle_tmp16);
            angle_result16 = angle_tmp16;
            if ((s16) angle_tmp16 >= 0x1000) {
                angle_result16 = angle_tmp16 - 0x1000;
            }
            ASM_KEEP_NV(angle_result16);
            angle_index16 = ((u16) angle_result16 >> 7) & 0x1C;
            ASM_KEEP_NV(angle_index16);
            sp2_base16 = (u8 *)&sp38;
            ASM_KEEP_NV(sp2_base16);
            sp2_base16 += angle_index16;
            ASM_KEEP_NV(sp2_base16);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(sp2_base16, s16 *, 0) << 0x10);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (M2C_FIELD(sp2_base16, u16 *, 2) << 0x10);
            func_80173018();
            return;
        }
        goto block_147;
jt_c17:
        {
            s32 pos_x = M2C_FIELD(arg1, s32 *, 0);
            s32 vel_x = M2C_FIELD(arg1, s32 *, 0xC);
            s32 pos_y = M2C_FIELD(arg1, s32 *, 4);
            s32 vel_y = M2C_FIELD(arg1, s32 *, 0x10);
            M2C_FIELD(arg1, s32 *, 0) = pos_x + vel_x;
            M2C_FIELD(arg1, s32 *, 4) = pos_y + vel_y;
        }
        {
            register u16 pitch17 ASM_REG("$3");
            register u16 phase17 ASM_REG("$2");
            pitch17 = M2C_FIELD(arg0, u16 *, 0x92);
            phase17 = M2C_FIELD(arg0, u16 *, 0x96);
            pitch17 = pitch17 - 2;
            ASM_KEEP_NV(pitch17);
            phase17 = phase17 + 1;
            temp_v0_11 = phase17;
            M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_11;
            M2C_FIELD(arg0, u16 *, 0x92) = pitch17;
        }
        if ((s16) temp_v0_11 >= 0x28) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0x10) = NULL;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
        }
        temp_v1_2 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
        if ((temp_v1_2 == 0xA) || (temp_v1_2 == 0x14) || (temp_v1_2 == 0x1E)) {
            register s32 angle_input ASM_REG("$3");
            register s32 angle_tmp ASM_REG("$4");
            register s32 angle_result ASM_REG("$3");
            angle_input = M2C_FIELD(temp_s3, u16 *, 0x2A);
            ASM_KEEP(angle_input);
            angle_tmp = angle_input - 0x200;
            ASM_KEEP(angle_tmp);
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            ASM_KEEP(angle_result);
            M2C_FIELD(temp_s3, u16 *, 0x2A) = angle_result;
            if ((s16) M2C_FIELD(arg0, u16 *, 0x96) == 0x1E) {
                func_800A56E0(0x81A);
                tail_call_arg = arg0;
                ASM_TAILSLOT_PIN(tail_call_arg);
                func_8017301C();
                return;
            }
            goto block_147;
        }
        goto block_147;
jt_c19:
        M2C_FIELD(arg0, u16 *, 0x96) = 0x14U;
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        temp_v0_12 = ((0x1F << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xBA;
        M2C_FIELD(temp_v0_12, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_12, u16 *, 4) & 0x7FFF);
        temp_v0_13 = ((0x1F << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xC0;
        M2C_FIELD(temp_v0_13, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_13, u16 *, 4) & 0x7FFF);
        temp_v0_14 = ((0x1F << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xC6;
        M2C_FIELD(temp_v0_14, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_14, u16 *, 4) & 0x7FFF);
        temp_v0_15 = ((0x20 << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xBA;
        M2C_FIELD(temp_v0_15, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_15, u16 *, 4) & 0x7FFF);
        temp_v0_16 = ((0x20 << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xC0;
        M2C_FIELD(temp_v0_16, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_16, u16 *, 4) & 0x7FFF);
        temp_v0_17 = ((0x20 << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xC6;
        M2C_FIELD(temp_v0_17, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_17, u16 *, 4) & 0x7FFF);
        temp_v0_18 = ((0x21 << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xBA;
        M2C_FIELD(temp_v0_18, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_18, u16 *, 4) & 0x7FFF);
        temp_v0_19 = ((0x21 << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xC0;
        M2C_FIELD(temp_v0_19, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_19, u16 *, 4) & 0x7FFF);
        temp_v0_20 = ((0x21 << M2C_FIELD(base833c, s16 *, 0x14)) * 6) + temp_s2 + 0xC6;
        M2C_FIELD(temp_v0_20, u16 *, 4) = (u16) (M2C_FIELD(temp_v0_20, u16 *, 4) & 0x7FFF);
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) M2C_FIELD(temp_s4, s32 *, 0);
        M2C_FIELD(arg1, s32 *, 0x10) = (void *) M2C_FIELD(temp_s4, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 0x14) = (void *) M2C_FIELD(temp_s4, s32 *, 8);
        /* fallthrough */
jt_c20:
        M2C_FIELD(arg1, s32 *, 0) += (M2C_FIELD(arg1, s32 *, 0xC) - M2C_FIELD(arg1, s32 *, 0)) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg1, s32 *, 4) += (M2C_FIELD(arg1, s32 *, 0x10) - M2C_FIELD(arg1, s32 *, 4)) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
        M2C_FIELD(arg1, s32 *, 8) += (M2C_FIELD(arg1, s32 *, 0x14) - M2C_FIELD(arg1, s32 *, 8)) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
        temp_v0_21 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_21;
        if ((temp_v0_21 << 0x10) <= 0) {
            tail_phase = M2C_FIELD(arg0, u8 *, 0x9A);
            ASM_KEEP(tail_phase);
            M2C_FIELD(arg0, u16 *, 0x96) = 0;
            func_80173074();
            return;
        }
        goto block_152;
jt_c21:
        if (M2C_FIELD(arg2, s8 *, 4) == 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
            func_80173080();
            return;
        }
        goto block_152;
jt_c22:
        {
            register u16 phase22 ASM_REG("$4");
        if (M2C_FIELD(arg2, s8 *, 4) == 0) {
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
        }
        temp_v0_22 = M2C_FIELD(arg0, u16 *, 0x96);
        phase22 = temp_v0_22 + 1;
        ASM_KEEP_NV(phase22);
        M2C_FIELD(arg0, u16 *, 0x96) = phase22;
        if ((u32) (temp_v0_22 - 0xA) < 8U) {
            M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (func_800644B8(((s32) (phase22 << 0x10) >> 8) - 0xA00) << 8);
            M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(temp_s3, u16 *, 0x88) - M2C_FIELD(arg0, u16 *, 0xA2));
        }
        }
        temp_v1_6 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
        if ((temp_v1_6 == 0x19) || (temp_v1_6 == 0x1E) || (temp_v1_6 == 0x23) || (temp_v1_6 == 0x28)) {
            register s32 angle_input ASM_REG("$3");
            register s32 angle_tmp ASM_REG("$4");
            register s32 angle_result ASM_REG("$3");
            angle_input = M2C_FIELD(temp_s3, u16 *, 0x2A);
            ASM_KEEP(angle_input);
            angle_tmp = angle_input - 0x200;
            ASM_KEEP(angle_tmp);
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            ASM_KEEP(angle_result);
            M2C_FIELD(temp_s3, u16 *, 0x2A) = angle_result;
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x2D) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, s16 *, 0x92) = -0x18;
            M2C_FIELD(arg0, s16 *, 0x9E) = 0;
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, u16 *, 0xA) = M2C_FIELD(temp_s3, u16 *, 0x88);
            func_80173080();
            return;
        }
        goto block_152;
jt_c24:
        temp_v0_23 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_23;
        if (((s16) temp_v0_23 == 5) || ((s16) temp_v0_23 == 0xA) || ((s16) temp_v0_23 == 0xF) || ((s16) temp_v0_23 == 0x14)) {
            register s32 angle_input ASM_REG("$3");
            register s32 angle_tmp ASM_REG("$4");
            register s32 angle_result ASM_REG("$3");
            angle_input = M2C_FIELD(temp_s3, u16 *, 0x2A);
            ASM_KEEP(angle_input);
            angle_tmp = angle_input - 0x200;
            ASM_KEEP(angle_tmp);
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            ASM_KEEP(angle_result);
            M2C_FIELD(temp_s3, u16 *, 0x2A) = angle_result;
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x18) {
            register u8 *sp2_base24 ASM_REG("$3");
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173DA4;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            func_80047784(arg2, D_80173DA4[((s32) (M2C_FIELD(D_80083228, s16 *, 0) + (s16) M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            sp2_base24 = (u8 *)&sp38;
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (SP2_X_AT(sp2_base24, M2C_FIELD(temp_s3, u16 *, 0x2A)) << 0x14);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (SP2_Y_AT(sp2_base24, M2C_FIELD(temp_s3, u16 *, 0x2A)) << 0x14);
            M2C_FIELD(arg1, s32 *, 0x14) = (void *)0xFFF00000;
            func_80173080();
            return;
        }
        goto block_152;
jt_c25:
        temp_a0_9 = M2C_FIELD(arg1, s32 *, 0x10);
        temp_a1_6 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (void *) (M2C_FIELD(arg1, s32 *, 4) + temp_a0_9);
        M2C_FIELD(arg1, s32 *, 8) = (void *) (M2C_FIELD(arg1, s32 *, 8) + temp_a1_6);
        temp_v0_24 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_24;
        if ((s16) temp_v0_24 >= 0x28) {
            tail_phase = M2C_FIELD(arg0, u8 *, 0x9A);
            ASM_KEEP(tail_phase);
            M2C_FIELD(arg0, u16 *, 0x96) = 0;
            func_80173074();
            return;
        }
        goto block_152;
jt_c30: {
        register u8 *sp2_base30 ASM_REG("$3");
        u16 angle30;
        u16 y30;
        angle30 = M2C_FIELD(temp_s3, volatile u16 *, 0x2A);
        sp2_base30 = (u8 *)&sp38;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) (SP2_X_AT(sp2_base30, angle30) << 0x13);
        y30 = SP2_Y_AT(sp2_base30, M2C_FIELD(temp_s3, u16 *, 0x2A));
        M2C_FIELD(arg1, s32 *, 0x14) = (void *)0xFFFB0000;
        M2C_FIELD(arg1, s32 *, 0x10) = (void *) (y30 << 0x13);
        tail_phase = M2C_FIELD(arg0, u8 *, 0x9A);
        ASM_KEEP(tail_phase);
        M2C_FIELD(arg0, u16 *, 0x96) = 0;
        func_80173074();
        return;
    }
jt_c31:
        temp_a0_10 = M2C_FIELD(arg1, s32 *, 0x10);
        temp_a1_7 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
        M2C_FIELD(arg1, s32 *, 4) = (void *) (M2C_FIELD(arg1, s32 *, 4) + temp_a0_10);
        M2C_FIELD(arg1, s32 *, 8) = (void *) (M2C_FIELD(arg1, s32 *, 8) + temp_a1_7);
        temp_v0_25 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_25;
        if ((s16) temp_v0_25 >= 5) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0x14) = NULL;
            M2C_FIELD(arg1, s32 *, 0x10) = NULL;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            func_80173080();
            return;
        }
        goto block_152;
jt_c32:
        temp_v0_26 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_26;
        if (((s16) temp_v0_26 == 2) || ((s16) temp_v0_26 == 8) || ((s16) temp_v0_26 == 0xA) || ((s16) temp_v0_26 == 0x10) || ((s16) temp_v0_26 == 0x12)) {
            var_v1_6 = M2C_FIELD(temp_s3, u16 *, 0x2A);
            temp_a0_11 = var_v1_6 + 0x200;
            var_v1_6 = temp_a0_11;
            if (temp_a0_11 >= 0x1000) {
                var_v1_6 = temp_a0_11 - 0x1000;
            }
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) var_v1_6;
        }
        var_v1_6 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
        if ((var_v1_6 == 4) || (var_v1_6 == 6) || (var_v1_6 == 0xC) || (var_v1_6 == 0xE) || (var_v1_6 == 0x14)) {
            var_v1_6 = M2C_FIELD(temp_s3, u16 *, 0x2A);
            temp_a0_12 = var_v1_6 - 0x200;
            var_v1_6 = temp_a0_12;
            if ((s16) temp_a0_12 < 0) {
                var_v1_6 = temp_a0_12 + 0x1000;
            }
            M2C_FIELD(temp_s3, u16 *, 0x2A) = var_v1_6;
        }
        var_v1_6 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
        if (var_v1_6 == 0x1A) {
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80173DA4;
            M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
            func_80047784(arg2, D_80173DA4[((s32) (M2C_FIELD(D_80083228, s16 *, 0) + (s16) M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x1E) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            M2C_FIELD(arg1, s32 *, 0x14) = (void *)0xFFF80000;
            func_80173080();
            return;
        }
        goto block_152;
jt_c33:
        M2C_FIELD(arg1, s32 *, 8) = (void *) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
        temp_v0_27 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_27;
        if ((s16) temp_v0_27 >= 0xA) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            temp_v0_27 = M2C_FIELD(arg1, u16 *, 0xA);
            M2C_FIELD(arg1, s32 *, 0x14) = NULL;
            M2C_FIELD(arg1, s32 *, 0x10) = NULL;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            temp_v1_7 = M2C_FIELD(temp_s3, u16 *, 0x88);
            M2C_FIELD(arg0, s16 *, 0x9E) = 0;
            M2C_FIELD(arg0, s32 *, 0xA0) = 0;
            M2C_FIELD(arg0, u16 *, 0x92) = (u16) (temp_v0_27 - temp_v1_7);
            var_v1_8 = M2C_FIELD(temp_s3, u16 *, 0x2A);
            temp_a0_13 = var_v1_8 + 0x400;
            var_v1_8 = temp_a0_13;
            if (temp_a0_13 >= 0x1000) {
                var_v1_8 = temp_a0_13 - 0x1000;
            }
            M2C_FIELD(temp_s3, u16 *, 0x2A) = (u16) var_v1_8;
            func_80047784(arg2, *(M2C_FIELD(arg2, u8 **, 0x2C) + (((s32) (M2C_FIELD(D_80083228, s16 *, 0) + var_v1_8 + 0x100) >> 9) & 7)), 0);
        }
        goto block_152;
jt_c34: {
        temp_v0_28 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_28;
        if ((temp_v0_28 & 3) == 3) {
            register s32 angle_input ASM_REG("$3");
            register s32 angle_tmp ASM_REG("$4");
            register s32 angle_result ASM_REG("$3");
            angle_input = M2C_FIELD(temp_s3, u16 *, 0x2A);
            ASM_KEEP(angle_input);
            angle_tmp = angle_input - 0x200;
            ASM_KEEP(angle_tmp);
            angle_result = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_result = angle_tmp + 0x1000;
            }
            ASM_KEEP(angle_result);
            M2C_FIELD(temp_s3, u16 *, 0x2A) = angle_result;
        }
        temp_a1_8 = ((0x61 - (s16) M2C_FIELD(arg0, u16 *, 0x96)) * 0x60000) / 97;
        {
            u8 *base34 = (u8 *)&sp38;
            s32 comp_x = SP2_X_AT(base34, M2C_FIELD(temp_s3, u16 *, 0x2A));
            M2C_FIELD(arg1, s32 *, 0xC) = temp_a1_8 * comp_x;
            base34 = (u8 *)&sp38;
            {
                s16 comp_y = (s16) SP2_Y_AT(base34, M2C_FIELD(temp_s3, u16 *, 0x2A));
                M2C_FIELD(arg1, s32 *, 0x10) = temp_a1_8 * comp_y;
            }
            M2C_FIELD(arg1, s32 *, 0) += M2C_FIELD(arg1, s32 *, 0xC);
            M2C_FIELD(arg1, s32 *, 4) += M2C_FIELD(arg1, s32 *, 0x10);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x96) >= 0x58) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            {
                u16 *reset_base = (u16 *)D_80083780;
                M2C_FIELD(arg1, u16 *, 2) = reset_base[1];
                M2C_FIELD(arg1, u16 *, 6) = reset_base[3];
            }
            func_8017301C(arg0);
            return;
        }
        goto block_147;
    }
jt_c40:
        if ((func_800F685C(temp_a0, temp_a1_2) << 0x10) != 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            D_80083460[5] = (u16) (D_80083460[5] + 1);
        }
        goto block_152;
jt_c41:
        temp_v0_29 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_29;
        if ((s16) temp_v0_29 >= 0x3C) {
            tail_phase = M2C_FIELD(arg0, u8 *, 0x9A);
            ASM_KEEP(tail_phase);
            M2C_FIELD(arg0, u16 *, 0x96) = 0;
            func_80173074();
            return;
        }
        goto block_152;
jt_c45:
        if ((func_800F685C(temp_a0, temp_a1_2) << 0x10) != 0) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
            D_80083460[5] = (u16) (D_80083460[5] + 1);
        }
        goto block_146;
jt_c46:
        temp_v0_30 = M2C_FIELD(arg0, u16 *, 0x96) + 1;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_30;
        if ((s16) temp_v0_30 >= 0x3C) {
            M2C_FIELD(arg0, u16 *, 0x96) = 0U;
            M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        }
        goto block_146;
jt_c35:
block_146:
        func_8016F79C(arg0, arg1, arg2);
        goto block_147;
jt_c5:
jt_c12:
jt_c14:
jt_c18:
block_147:
    func_8016F5D8(arg0, arg1, arg2);
    {
        register u32 tail_page147 ASM_REG("$2");
        tail_page147 = 0x80170000;
        ASM_PAGEBASE_PIN(tail_page147);
    }
    func_80173084();

jt_c42:
jt_c47:
        ASM_CLOBBER("$7");
        func_800945E8(D_800E3D7C[0], temp_a1_2);
        {
            register s32 fwd_a0 ASM_REG("$4");
            register s32 fwd_a1 ASM_REG("$5");
            register s32 fwd_a2 ASM_REG("$6");
            register s32 fwd_a3 ASM_REG("$7");
            ASM_SET(fwd_a0);
            ASM_SET(fwd_a1);
            ASM_SET(fwd_a2);
            ASM_SET(fwd_a3);
            func_800948BC(fwd_a0, fwd_a1, fwd_a2, fwd_a3);
        }
        D_80082E76[0] = 0x8000;
        func_80041094(6, 0, 0, 0, 0x8000);
        M2C_FIELD(arg0, u8 *, 0x9A) = (u8) (M2C_FIELD(arg0, u8 *, 0x9A) + 1);
        goto block_152;
jt_c8:
jt_c23:
jt_c26:
jt_c27:
jt_c28:
jt_c29:
jt_c36:
jt_c37:
jt_c38:
jt_c39:
jt_c43:
jt_c44:
jt_c48:
block_152:
    if (D_80175D54[0] != 0) {
        temp_s2_2 = ((s32) (M2C_FIELD(D_80083228, s16 *, 0) + (s16) M2C_FIELD(temp_s3, u16 *, 0x2A) + 0x100) >> 9) & 7;
        if (M2C_FIELD(arg0, s16 *, 0x94) != temp_s2_2) {
            func_80047738(arg2, *(M2C_FIELD(arg2, u8 **, 0x2C) + temp_s2_2), M2C_FIELD(arg2, s8 *, 4));
            M2C_FIELD(arg0, s16 *, 0x94) = temp_s2_2;
        }
        if (M2C_FIELD(D_8006CCF8, u8 *, temp_s2_2) != 0) {
            register u16 tail_flag ASM_REG("$2");
            tail_flag = M2C_FIELD(arg2, u16 *, 0x14) | 1;
            ASM_TAILSLOT_PIN(tail_flag);
            func_80173110();
            return;
        }
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE);
    }
    return;

}
