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

M2C_UNK func_80021120();   /* extern */
extern void func_80021CF0() __attribute__((noreturn));
extern void func_80021FA8() __attribute__((noreturn));
extern void func_80021FAC() __attribute__((noreturn));
extern void func_80021FB8() __attribute__((noreturn));
extern void func_80022014() __attribute__((noreturn));
extern void func_800223DC() __attribute__((noreturn));
s32 func_8002263C(); /* extern */
M2C_UNK func_80023E6C();   /* extern */
M2C_UNK func_80033B78();                     /* extern */
M2C_UNK func_80033B9C();                     /* extern */
short func_80053DA8(); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();           /* extern */
s32 rand();                      /* extern */
M2C_UNK func_800ABD74();                       /* extern */
s32 func_800B1BEC();       /* extern */
M2C_UNK func_800B1DBC();              /* extern */
extern s32 D_80012D5C[0xB58];
extern u8 D_80022514[0x100];
extern s32 D_80024338[3];
extern u8 D_800834B8[0x100];
extern u8 D_80083780[0x100];
extern s16 D_80113158[8];
extern s32 D_8011315C[0xC58];

typedef struct StackRecord {
    s16 sp10;
    s16 sp12;
    void *sp14;
    s32 sp18;
    s16 sp1C;
    s16 sp1E;
    s16 sp20;
    s16 sp22;
    s16 sp24;
    s16 sp26;
    u8 unused[0x10];
} StackRecord;

void func_800218E4(void *arg0_in, s32 arg1, void *arg2, M2C_UNK arg3) {
    StackRecord stack;
    M2C_UNK var_a3;
    register s32 temp_a1_2 ASM_REG("$5");
    register s32 temp_s2_2 ASM_REG("$18");
    register s32 case4_one ASM_REG("$6");
    register s32 temp_t0 ASM_REG("$8");
    register s32 temp_t1 ASM_REG("$9");
    s16 temp_v1;
    register s32 temp_v1_4 ASM_REG("$3");
    s32 transition_timer;
    register s32 transition_v0 ASM_REG("$2");
    s32 transition_a0;
    register s32 collision_a0 ASM_REG("$4");
    s32 case8_gold;
    s32 case8_score;
    s32 case8_handle;
    s32 case4_global;
    s32 var_a1_5;
    s32 var_a2_2;
    s32 var_a3_2;
    s16 var_s2_9;
    s32 **var_s0;
    s32 **var_s0_2;
    s32 *temp_a0_3;
    s32 *temp_v1_7;
    void *var_a0_6;
    s32 temp_a0;
    s32 payout_amount;
    s32 *payout_score;
    s32 payout_carry;
    s32 *payout_gold;
    s32 temp_a0_6;
    s32 temp_a3;
    s32 temp_ret;
    s32 temp_ret_2;
    register void *temp_v0_8 ASM_REG("$2");
    s32 var_a0_3;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_s2;
    s32 var_s2_10;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_s2_4;
    s32 var_s2_5;
    s32 var_s2_6;
    s32 var_s2_7;
    s32 var_s2_8;
    s32 var_s3;
    register s32 var_s3_2 ASM_REG("$19");
    s32 var_t2;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    u16 temp_a0_4;
    u16 temp_a0_5;
    u16 temp_a0_7;
    u16 temp_v0_10;
    u16 temp_v0_2;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_9;
    u16 temp_v1_10;
    u16 temp_v1_3;
    u16 temp_v1_9;
    void **var_a0_2;
    void *temp_a0_2;
    void *temp_a1;
    register void *temp_s0 ASM_REG("$16");
    void *temp_t3;
    void *temp_t3_2;
    void *temp_v0;
    void *case0_obj;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v1_2;
    register void *temp_v1_5 ASM_REG("$3");
    void *temp_v1_8;
    void *var_a0;
    void *var_a2;
    register void *var_s1 ASM_REG("$17");
    void *var_s1_2;
    void *var_s7;
    void *save_s5;
    register void *save_s6 ASM_REG("$22");
    void *var_v0;
    void *var_v1_6;
    void *var_v1_7;
    void *arg0 = arg0_in;
    u8 *base;

    var_a1 = arg1;
    var_a2 = arg2;
    var_a3 = arg3;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x2C);
    base = D_800834B8;
    switch (temp_v1) {
    case 0:
        var_s2_4 = 3;
        var_v0 = arg0 + 6;
        do {
            M2C_FIELD(var_v0, s16 *, 0x30) = 0;
            var_s2_4 -= 1;
            var_v0 -= 2;
        } while (var_s2_4 >= 0);
        var_s2_4 = 2;
        var_a1 = 1;
        var_a0 = arg0 + 8;
        M2C_FIELD(arg0, s16 *, 0x46) = -1;
        M2C_FIELD(arg0, s16 *, 0x44) = -1;
        M2C_FIELD(arg0, M2C_UNK **, 0) = &D_80083780;
        M2C_FIELD(arg0, void **, 0x10) = (void *) (base + 0x10);
        do {
            ASM_KEEP(var_a0);
            temp_v0 = M2C_FIELD(var_a0, void **, 0x20);
            var_s2_4 -= 1;
            case0_obj = temp_v0;
            ASM_KEEP(temp_v0);
            temp_s0 = case0_obj + 0x20;
            ASM_KEEP(temp_s0);
            M2C_FIELD(var_a0, s32 *, 4) = (s32) M2C_FIELD(temp_v0, s32 *, 8);
            M2C_FIELD(temp_s0, s16 *, 0x18) = var_a1;
            M2C_FIELD(temp_s0, s32 *, 4) = 0;
            M2C_FIELD(temp_s0, s16 *, 0x16) = 0;
            M2C_FIELD(temp_s0, s16 *, 0x14) = 0;
            M2C_FIELD(var_a0, void **, 0x14) = (void *) (case0_obj + 0x4A);
            var_a0 -= 4;
        } while (var_s2_4 >= 0);
        M2C_FIELD(base, s16 *, 8) = 0;
        var_s2_4 = 3;
        var_a3 = 0x10000000;
        var_a2 = arg0 + 6;
        var_a0 = arg0 + 0xC;
        var_a1 = 0x04A00000;
        do {
            M2C_FIELD(*(void **) var_a0, s32 *, 0) = var_a3;
            var_s2_4 -= 1;
            M2C_FIELD(*(void **) var_a0, s32 *, 4) = var_a1;
            temp_v1_2 = *(void **) var_a0;
            var_a0 -= 4;
            ASM_SCHED_BARRIER();
            transition_v0 = 0xFFC00000;
            var_a1 += transition_v0;
            M2C_FIELD(temp_v1_2, s32 *, 0x14) = 0;
            ASM_SCHED_BARRIER();
            M2C_FIELD(temp_v1_2, s32 *, 0x10) = 0;
            M2C_FIELD(temp_v1_2, s32 *, 0xC) = 0;
            M2C_FIELD(temp_v1_2, s32 *, 8) = 0;
            M2C_FIELD(var_a2, s16 *, 0x3C) = 0;
            var_a2 -= 2;
        } while (var_s2_4 >= 0);
        M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
        /* fallthrough */
    case 1:
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x2E) - 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(base, s16 *, 8) = 1;
            M2C_FIELD(arg0, u16 *, 0x2E) = 0x20U;
            M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
            func_80053DA8(0x521, var_a1, var_a2, var_a3);
            func_80021FB8();
            return;
        }
        goto block_67;
    case 2:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x2E) == 0x10) {
            func_80053DA8(0x700);
            func_80053DA8(0x702);
            var_s2_4 = 2;
            transition_a0 = 3;
            ASM_KEEP(transition_a0);
            var_v1_6 = arg0 + 8;
            do {
                temp_v0_5 = M2C_FIELD(var_v1_6, void **, 0x20);
                var_v1_6 -= 4;
                var_s2_4 -= 1;
                M2C_FIELD(temp_v0_5, s16 *, 0x38) = transition_a0;
            } while (var_s2_4 >= 0);
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 0x2E) < 0x10) {
            var_s2_4 = 3;
            var_s3 = 0xFFF00000;
            ASM_KEEP(var_s3);
            do {
                temp_a0_3 = ((s32 **) arg0)[var_s2_4];
                transition_v0 = M2C_FIELD(arg0, s16 *, 0x2E);
                temp_v1_4 = *temp_a0_3;
                transition_v0 <<= 0x10;
                temp_v1_4 += var_s3;
                temp_v1_4 += transition_v0;
                *temp_a0_3 = temp_v1_4;
                temp_ret = rand(temp_a0_3);
                if (temp_ret == ((temp_ret / 3) * 3)) {
                    func_800ABD74(((s32 **) arg0)[var_s2_4]);
                }
                var_s2_4 -= 1;
            } while (var_s2_4 >= 0);
        }
        temp_v0_6 = M2C_FIELD(arg0, u16 *, 0x2E) - 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_v0_6;
        if ((temp_v0_6 << 0x10) <= 0) {
            M2C_FIELD(base, s16 *, 8) = 2;
            (void) M2C_FIELD(arg0, volatile u16 *, 0x2C);
            transition_timer = 0x10;
            M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
            func_80021FAC();
            return;
        }
        goto block_67;
    case 3:
        var_s2_4 = 3;
        do {
            temp_v1_7 = ((s32 **) arg0)[var_s2_4];
            *temp_v1_7 += 0xFFF00000;
            temp_ret_2 = rand();
            if (temp_ret_2 == ((temp_ret_2 / 3) * 3)) {
                func_800ABD74(((s32 **) arg0)[var_s2_4]);
            }
            var_s2_4 -= 1;
        } while (var_s2_4 >= 0);
        temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x2E) - 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_v0_7;
        if ((temp_v0_7 << 0x10) <= 0) {
            M2C_FIELD(base, s16 *, 8) = 3;
            var_s2_4 = 2;
            var_a1_5 = 0x100;
            var_a0_6 = (void *)0xC0000;
            var_v1_7 = arg0 + 8;
            do {
                temp_v0_8 = M2C_FIELD(var_v1_7, void **, 0x20);
                var_v1_7 -= 4;
                temp_s0 = temp_v0_8 + 0x20;
                M2C_FIELD(temp_s0, s16 *, 0x22) = var_s2_4;
                var_s2_4 -= 1;
                M2C_FIELD(temp_s0, s16 *, 0x18) = var_a1_5;
                M2C_FIELD(temp_s0, s16 *, 0x1C) = 0;
                M2C_FIELD(temp_s0, void **, 4) = var_a0_6;
            } while (var_s2_4 >= 0);
            var_s2_4 = 0xA;
            do {
                var_s2_4 -= 1;
                transition_v0 = rand(var_a0_6, var_a1_5);
                var_s3 = transition_v0 / 3;
                ASM_KEEP(var_s3);
                var_s3 = transition_v0 - (var_s3 * 3);
                transition_v0 = rand();
                ASM_KEEP(var_s3);
                var_t2 = transition_v0 / 3;
                ASM_KEEP(var_t2);
                var_t2 = transition_v0 - (var_t2 * 3);
                transition_v0 = var_s3 * 4;
                ASM_KEEP(transition_v0);
                transition_v0 += (s32) arg0;
                temp_v1_4 = var_t2 * 4;
                ASM_KEEP(temp_v1_4);
                temp_v1_4 += (s32) arg0;
                ASM_KEEP(var_t2);
                var_a0_6 = M2C_FIELD(transition_v0, void **, 0x20);
                temp_v1_8 = temp_v1_4;
                var_a1_5 = M2C_FIELD(var_a0_6, s16 *, 0x42);
                M2C_FIELD(var_a0_6, s16 *, 0x42) = (s16) M2C_FIELD(M2C_FIELD(temp_v1_8, void **, 0x20), u16 *, 0x42);
                M2C_FIELD(M2C_FIELD(temp_v1_8, void **, 0x20), u16 *, 0x42) = (u16) var_a1_5;
            } while (var_s2_4 >= 0);
            func_80053DA8(0x1702, var_a1_5);
            func_80021FA8();
            return;
        }
        goto block_67;
    case 4:
        M2C_FIELD(arg0, u16 *, 0x2E) = (u16) (M2C_FIELD(arg0, u16 *, 0x2E) + 1);
        if (M2C_FIELD(arg0, s16 *, 0x46) >= 0) {
            if (M2C_FIELD(arg0, s16 *, 0x44) != 0) {
                func_80033B78(0x58F);
                func_80021CF0();
                return;
            }
            func_80033B9C(0x58F);
            temp_s2_2 = M2C_FIELD(arg0, s16 *, 0x44);
            ASM_KEEP(temp_s2_2);
            if (M2C_FIELD(arg0, s16 *, 0x46) < temp_s2_2) {
                M2C_FIELD(arg0, s16 *, 0x44) = (s16) (u16) M2C_FIELD(arg0, s16 *, 0x46);
                M2C_FIELD(arg0, s16 *, 0x46) = temp_s2_2;
            }
            case4_one = 1;
            collision_a0 = M2C_FIELD(arg0, s16 *, 0x44);
            temp_v1_4 = M2C_FIELD(arg0, s16 *, 0x46);
            case4_global = D_80113158[0];
            collision_a0 = case4_one << collision_a0;
            temp_v1_4 = case4_one << temp_v1_4;
            temp_s2_2 = collision_a0 + temp_v1_4;
            if (case4_global != temp_s2_2) {
                M2C_FIELD(&D_8011315C, s32 *, 0) = 0;
            }
            M2C_FIELD(arg0, u16 *, 0x2E) = 0x40U;
            M2C_FIELD(arg0, u16 *, 0x4A) = 0x400U;
            M2C_FIELD(arg0, u16 *, 0x48) = 0U;
            stack.sp1C = 0x28;
            stack.sp1E = 0x58;
            stack.sp20 = 0xF0;
            stack.sp22 = 0x50;
            stack.sp24 = 2;
            stack.sp26 = case4_one;
            stack.sp18 = 0;
            stack.sp10 = 0;
            stack.sp12 = 8;
            stack.sp14 = arg0;
            func_80021120(&D_80022514, &stack, 1);
            func_80021FA8();
            return;
        }
        goto block_67;
    case 5:
        transition_timer = M2C_FIELD(arg0, u16 *, 0x48);
        transition_v0 = M2C_FIELD(arg0, u16 *, 0x2E);
        transition_timer += 0x12C;
        transition_v0 <<= 1;
        transition_timer += transition_v0;
        transition_v0 = M2C_FIELD(arg0, u16 *, 0x4A);
        M2C_FIELD(arg0, u16 *, 0x48) = transition_timer;
        transition_timer = M2C_FIELD(arg0, u16 *, 0x2E);
        transition_v0 += 0x10;
        transition_timer -= 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
        transition_timer <<= 0x10;
        M2C_FIELD(arg0, u16 *, 0x4A) = transition_v0;
        if (transition_timer <= 0) {
            if (D_80113158[0] != 0) {
                D_80024338[0] = func_800B1BEC(0, -0x50, 0x40);
            }
            (void) M2C_FIELD(arg0, volatile u16 *, 0x2C);
            transition_timer = 0x10;
            M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
            func_80021FAC();
            return;
        }
        goto block_67;
    case 6:
        transition_v0 = 0x10;
        transition_timer = M2C_FIELD(arg0, u16 *, 0x48);
        transition_a0 = M2C_FIELD(arg0, u16 *, 0x2E);
        transition_timer += 0x12C;
        transition_v0 -= transition_a0;
        transition_v0 <<= 3;
        transition_timer -= transition_v0;
        M2C_FIELD(arg0, u16 *, 0x48) = transition_timer;
        transition_timer = transition_a0;
        ASM_KEEP(transition_timer);
        transition_v0 = M2C_FIELD(arg0, u16 *, 0x4A);
        transition_timer -= 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
        transition_timer <<= 0x10;
        transition_v0 += 0x15E;
        M2C_FIELD(arg0, u16 *, 0x4A) = transition_v0;
        if (transition_timer <= 0) {
            (void) M2C_FIELD(arg0, volatile u16 *, 0x2C);
            transition_timer = 0x21;
            M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
            func_80021FAC();
            return;
        }
        goto block_67;
    case 7:
        M2C_FIELD(arg0, u16 *, 0x48) = (u16) (M2C_FIELD(arg0, u16 *, 0x48) + 0xA0);
        temp_a0_5 = M2C_FIELD(arg0, u16 *, 0x2E) - 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_a0_5;
        temp_a0_6 = temp_a0_5 << 0x10;
        M2C_FIELD(arg0, u16 *, 0x4A) = (u16) (M2C_FIELD(arg0, u16 *, 0x4A) + ((s32) (0x1EDC - (s16) M2C_FIELD(arg0, u16 *, 0x4A)) >> 1));
        if (temp_a0_6 <= 0) {
            M2C_FIELD(arg0, u16 *, 0x48) = 0U;
            (void) M2C_FIELD(arg0, volatile u16 *, 0x2C);
            transition_timer = 0x10;
            M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
            func_80021FAC();
            return;
        }
        goto block_67;
    case 8:
        transition_timer = 0x2001;
        transition_v0 = M2C_FIELD(arg0, s16 *, 0x4A);
        transition_a0 = M2C_FIELD(arg0, u16 *, 0x2E);
        transition_timer -= transition_v0;
        transition_timer >>= 1;
        transition_v0 = M2C_FIELD(arg0, u16 *, 0x4A);
        transition_a0 -= 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = transition_a0;
        transition_a0 <<= 0x10;
        transition_v0 += transition_timer;
        M2C_FIELD(arg0, u16 *, 0x4A) = transition_v0;
        if (transition_a0 <= 0) {
            if (D_80113158[0] != 0) {
                case8_gold = D_80012D5C[0];
                case8_score = D_8011315C[0];
                case8_handle = D_80024338[0];
                case8_gold += case8_score;
                D_80012D5C[0] = case8_gold;
                func_800B1DBC(case8_handle);
            }
            (void) M2C_FIELD(arg0, volatile u16 *, 0x2C);
            transition_timer = 0x8F;
            M2C_FIELD(arg0, u16 *, 0x2E) = transition_timer;
            func_80021FAC();
            return;
        }
        goto block_67;
    case 9:
        if ((s16) M2C_FIELD(arg0, u16 *, 0x2E) == 0x64) {
            func_80053DA8(0x702);
        }
        temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x2E) - 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_v0_9;
        if ((temp_v0_9 << 0x10) <= 0) {
            func_80053DA8(0x72);
            M2C_FIELD(arg0, u16 *, 0x2E) = 0x1EU;
            M2C_FIELD(arg0, u16 *, 0x3A) = (u16) (M2C_FIELD(arg0, u16 *, 0x3A) | 0x8000);
            M2C_FIELD(arg0, u16 *, 0x2C) = (u16) (M2C_FIELD(arg0, u16 *, 0x2C) + 1);
            func_80021FB8();
            return;
        }
        goto block_67;
    case 10:
        temp_v0_10 = M2C_FIELD(arg0, u16 *, 0x2E) - 1;
        M2C_FIELD(arg0, u16 *, 0x2E) = temp_v0_10;
        if ((temp_v0_10 << 0x10) <= 0) {
            M2C_FIELD(base, s16 *, 8) = 4;
            M2C_FIELD(arg0, s16 *, 0x2C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) + 1);
        }
        goto block_67;
    default:
block_67:
        if ((u32) ((u16) M2C_FIELD(arg0, s16 *, 0x2C) - 6) < 3U) {
            payout_amount = D_8011315C[0];
            if (payout_amount >= 0x3E8) {
                payout_gold = D_80012D5C;
                payout_carry = *payout_gold;
                payout_amount -= 0x3E8;
                D_8011315C[0] = payout_amount;
                payout_carry += 0x3E8;
                /* gcc-2.7.x rejects the '+' read/write constraint.  The
                 * project-sanctioned tied spelling has identical dataflow
                 * semantics and preserves the tailslot marker. */
                ASM_TAILSLOT_PIN_TIED(payout_carry);
                func_80022014();
                return;
            }
            if (payout_amount >= 0x64) {
                payout_gold = D_80012D5C;
                payout_carry = *payout_gold;
                payout_amount -= 0x64;
                D_8011315C[0] = payout_amount;
                payout_carry += 0x64;
                *payout_gold = payout_carry;
            }
            goto block_73;
        }
block_73:
        temp_v1_3 = (u16) M2C_FIELD(arg0, s16 *, 0x2C);
        if ((u32) (temp_v1_3 - 5) < 5U) {
            transition_v0 = (s16) temp_v1_3;
            temp_s2_2 = transition_v0 < 9;
            ASM_KEEP(temp_s2_2);
            func_80023E6C(0x50, M2C_FIELD(arg0, s16 *, 0x44), arg0, temp_s2_2);
            func_80023E6C(-0xF0, M2C_FIELD(arg0, s16 *, 0x46), arg0, temp_s2_2);
            func_80023E6C(0xA0, 4, arg0, temp_s2_2);
            func_80023E6C(-0xA0, 4, arg0, temp_s2_2);
        }
        var_s2_4 = 0;
        if (M2C_FIELD(arg0, s16 *, 0x2C) >= 4) {
            var_s7 = arg0;
loop_77:
            var_s3 = var_s2_4 + 1;
            ASM_KEEP(var_s3);
            if (var_s3 < 4) {
                transition_v0 = var_s3 * 4;
                save_s5 = var_s7;
                save_s6 = var_s7;
                var_s1 = (void *)(transition_v0 + (s32) arg0);
loop_79:
                temp_a1 = M2C_FIELD(save_s5, void **, 0);
                temp_a0_2 = M2C_FIELD(var_s1, void **, 0);
                transition_v0 = M2C_FIELD(temp_a1, s16 *, 0xA);
                temp_v1_4 = M2C_FIELD(temp_a0_2, s16 *, 0xA);
                transition_v0 -= temp_v1_4;
                if (transition_v0 < 0) {
                    transition_v0 = 0 - transition_v0;
                }
                if (transition_v0 < 0x40) {
                    temp_v1_4 = M2C_FIELD(temp_a1, s16 *, 2);
                    transition_v0 = M2C_FIELD(temp_a0_2, s16 *, 2);
                    collision_a0 = M2C_FIELD(temp_a0_2, s16 *, 6);
                    temp_v1_4 -= transition_v0;
                    transition_v0 = M2C_FIELD(temp_a1, s16 *, 6);
                    if (temp_v1_4 < 0) {
                        temp_v1_4 = 0 - temp_v1_4;
                    }
                    transition_v0 -= collision_a0;
                    if (transition_v0 < 0) {
                        transition_v0 = 0 - transition_v0;
                    }
                    temp_v1_4 += transition_v0;
                    if (temp_v1_4 < 0x38) {
                        transition_v0 = 0x3FFFF;
                        ASM_KEEP(transition_v0);
                        temp_v1_4 = M2C_FIELD(temp_a1, s32 *, 0xC);
                        collision_a0 = M2C_FIELD(temp_a1, s32 *, 0x10);
                        if (temp_v1_4 < 0) {
                            temp_v1_4 = 0 - temp_v1_4;
                        }
                        if (collision_a0 < 0) {
                            collision_a0 = 0 - collision_a0;
                        }
                        temp_v1_4 += collision_a0;
                        if (temp_v1_4 <= transition_v0) {
                            M2C_FIELD(M2C_FIELD(save_s5, void **, 0), s32 *, 0xC) = (s32) (func_80064584(*M2C_FIELD(save_s5, s16 **, 0x10), temp_a1) << 6);
                            M2C_FIELD(M2C_FIELD(save_s5, void **, 0), s32 *, 0x10) = (s32) (func_800644B8(*M2C_FIELD(save_s5, s16 **, 0x10)) << 6);
                        }
                        temp_t3 = M2C_FIELD(save_s5, void **, 0);
                        temp_v0_3 = M2C_FIELD(var_s1, void **, 0);
                        temp_a1_2 = M2C_FIELD(temp_t3, s16 *, 2);
                        temp_t0 = M2C_FIELD(temp_t3, s16 *, 0x12);
                        temp_t1 = M2C_FIELD(temp_v0_3, s16 *, 2);
                        temp_v1_4 = M2C_FIELD(temp_t3, s16 *, 6);
                        var_a2_2 = M2C_FIELD(temp_t3, s16 *, 0xE);
                        var_a3_2 = M2C_FIELD(temp_v0_3, s16 *, 6);
                        collision_a0 = (temp_a1_2 + temp_t0) - temp_t1;
                        if (collision_a0 < 0) {
                            collision_a0 = 0 - collision_a0;
                        }
                        ASM_KEEP(collision_a0);
                        var_v0_4 = (temp_v1_4 - var_a2_2) - var_a3_2;
                        if (var_v0_4 < 0) {
                            var_v0_4 = 0 - var_v0_4;
                        }
                        ASM_KEEP(var_v0_4);
                        var_t2 = collision_a0 + var_v0_4;
                        ASM_KEEP(var_t2);
                        var_a1_2 = (temp_a1_2 - temp_t0) - temp_t1;
                        if (var_a1_2 < 0) {
                            var_a1_2 = 0 - var_a1_2;
                        }
                        ASM_KEEP(var_a1_2);
                        var_v1_3 = (temp_v1_4 + var_a2_2) - var_a3_2;
                        if (var_v1_3 < 0) {
                            var_v1_3 = 0 - var_v1_3;
                        }
                        ASM_KEEP(var_v1_3);
                        temp_a1_2 = var_a1_2 + var_v1_3;
                        transition_v0 = temp_a1_2 < var_t2;
                        if (transition_v0) {
                            transition_v0 = M2C_FIELD(temp_t3, s32 *, 0xC);
                            var_t2 = M2C_FIELD(temp_t3, s32 *, 0x10);
                            var_a1_3 = 0 - transition_v0;
                        } else {
                            transition_v0 = M2C_FIELD(temp_t3, s32 *, 0x10);
                            var_a1_3 = M2C_FIELD(temp_t3, s32 *, 0xC);
                            var_t2 = 0 - transition_v0;
                        }
                        collision_a0 = 0x30000;
                        if (var_s2_4 == 0) {
                            goto block_base_collision;
                        }
                            transition_v0 = M2C_FIELD(save_s6, s32 *, 0x1C);
                            temp_s0 = transition_v0 + 0x20;
                            M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_s0, s32 *, 0xC) + var_t2);
                            M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x10) + var_a1_3);
                            temp_v1_5 = M2C_FIELD(var_s1, void **, 0);
                            ASM_SCHED_BARRIER();
                            collision_a0 |= 0xFFFF;
                            ASM_SCHED_BARRIER();
                            var_v0_5 = M2C_FIELD(temp_v1_5, s32 *, 0xC);
                            var_v1_4 = M2C_FIELD(temp_v1_5, s32 *, 0x10);
                            if (var_v0_5 < 0) {
                                var_v0_5 = 0 - var_v0_5;
                            }
                            if (var_v1_4 < 0) {
                                var_v1_4 = 0 - var_v1_4;
                            }
                            if ((var_v0_5 + var_v1_4) <= collision_a0) {
                                M2C_FIELD(M2C_FIELD(var_s1, void **, 0), s32 *, 0xC) = (s32) (func_80064584(*M2C_FIELD(var_s1, s16 **, 0x10), (void *) var_a1_3, var_a2_2, var_a3_2) << 6);
                                M2C_FIELD(M2C_FIELD(var_s1, void **, 0), s32 *, 0x10) = (s32) (func_800644B8(*M2C_FIELD(var_s1, s16 **, 0x10)) << 6);
                            }
                            temp_t3_2 = M2C_FIELD(var_s1, void **, 0);
                            temp_v0_4 = M2C_FIELD(save_s6, void **, 0);
                            temp_a1_2 = M2C_FIELD(temp_t3_2, s16 *, 2);
                            temp_t0 = M2C_FIELD(temp_t3_2, s16 *, 0x12);
                            temp_t1 = M2C_FIELD(temp_v0_4, s16 *, 2);
                            temp_v1_4 = M2C_FIELD(temp_t3_2, s16 *, 6);
                            var_a2_2 = M2C_FIELD(temp_t3_2, s16 *, 0xE);
                            var_a3_2 = M2C_FIELD(temp_v0_4, s16 *, 6);
                            collision_a0 = (temp_a1_2 + temp_t0) - temp_t1;
                            if (collision_a0 < 0) {
                                collision_a0 = 0 - collision_a0;
                            }
                            ASM_KEEP(collision_a0);
                            var_v0_6 = (temp_v1_4 - var_a2_2) - var_a3_2;
                            if (var_v0_6 < 0) {
                                var_v0_6 = 0 - var_v0_6;
                            }
                            ASM_KEEP(var_v0_6);
                            var_t2 = collision_a0 + var_v0_6;
                            ASM_KEEP(var_t2);
                            var_a1_4 = (temp_a1_2 - temp_t0) - temp_t1;
                            if (var_a1_4 < 0) {
                                var_a1_4 = 0 - var_a1_4;
                            }
                            ASM_KEEP(var_a1_4);
                            var_v1_5 = (temp_v1_4 + var_a2_2) - var_a3_2;
                            if (var_v1_5 < 0) {
                                var_v1_5 = 0 - var_v1_5;
                            }
                            ASM_KEEP(var_v1_5);
                            temp_a1_2 = var_a1_4 + var_v1_5;
                            transition_v0 = temp_a1_2 < var_t2;
                            if (transition_v0) {
                                transition_v0 = M2C_FIELD(temp_t3_2, s32 *, 0xC);
                                var_t2 = M2C_FIELD(temp_t3_2, s32 *, 0x10);
                                var_a1_3 = 0 - transition_v0;
                            } else {
                                transition_v0 = M2C_FIELD(temp_t3_2, s32 *, 0x10);
                                var_a1_3 = M2C_FIELD(temp_t3_2, s32 *, 0xC);
                                var_t2 = 0 - transition_v0;
                            }
                            if (var_s3 != 0) {
                                goto block_object_collision;
                            }
block_base_collision:
                            M2C_FIELD(base, s32 *, 0x58) = (s32) (M2C_FIELD(base, s32 *, 0x58) + var_t2);
                            M2C_FIELD(base, s32 *, 0x5C) = (s32) (M2C_FIELD(base, s32 *, 0x5C) + var_a1_3);
                            func_800223DC(collision_a0, var_a1_3, var_a2_2, var_a3_2);
                            return;
block_object_collision:
                            transition_v0 = M2C_FIELD(var_s1, s32 *, 0x1C);
                            temp_s0 = transition_v0 + 0x20;
                            M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (M2C_FIELD(temp_s0, s32 *, 0xC) + var_t2);
                            M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x10) + var_a1_3);
                    }
                    goto block_126;
                }
block_126:
                var_s3 += 1;
                var_s1 += 4;
                if (var_s3 >= 4) {
                    goto block_127;
                }
                goto loop_79;
            }
block_127:
            var_s2_4 += 1;
            var_s7 += 4;
            if (var_s2_4 >= 3) {
                if (func_8002263C(M2C_FIELD(arg0, M2C_UNK **, 0), arg0 + 0x3C, base + 0x58, base + 0x5C) != 0) {
                    M2C_FIELD(base, s32 *, 0x48) = 0;
                }
                var_s2_5 = 1;
                var_s1_2 = arg0 + 4;
                var_s3_2 = 0x3E;
                do {
                    temp_a3 = M2C_FIELD(var_s1_2, s32 *, 0x1C);
                    temp_s0 = temp_a3 + 0x20;
                    if (func_8002263C(M2C_FIELD(var_s1_2, M2C_UNK **, 0), arg0 + var_s3_2, temp_a3 + 0x2C, temp_a3 + 0x30) != 0) {
                        M2C_FIELD(temp_s0, s32 *, 4) = 0;
                    }
                    var_s1_2 += 4;
                    var_s2_5 += 1;
                    var_s3_2 += 2;
                } while (var_s2_5 < 4);
            } else {
                goto loop_77;
            }
        } else {
            return;
        }
        break;

    }
}
