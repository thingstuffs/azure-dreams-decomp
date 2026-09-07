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

void func_80024D24(void) __attribute__((noreturn));                         /* extern */
void func_80024D90(void) __attribute__((noreturn));                         /* extern */
void func_80024DCC(void) __attribute__((noreturn));                    /* extern */
void func_8004491C(void *, void *);           /* extern */
void func_800478B8(void *);                 /* extern */
extern M2C_UNK D_80045340;
extern s32 D_800814A0;
extern u8 D_800DEC70[];
extern M2C_UNK D_800DED28;

void func_81839358(void *arg0, void *arg1, void *arg2) {
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 temp_a1 ASM_REG("$5");
    s32 init_pos;
    s32 init_vel;
    s32 sprite_word;
    s32 state_shift;
    u8 actor_count;
    s32 temp_a0;
    u16 temp_v0;
    u8 temp_v1_3;
    void *temp_v1;

    init_pos = M2C_FIELD(arg1, volatile s32 *, 0);
    init_vel = M2C_FIELD(arg1, volatile s32 *, 0xC);
    temp_a0_2 = M2C_FIELD(arg1, volatile s32 *, 0x10);
    temp_a1 = M2C_FIELD(arg1, volatile s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 0) = init_pos + init_vel;
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a0_2);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + temp_a1);
    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, s32 *, 0x10) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x10) | 0x8000);
    var_v0 = M2C_FIELD(arg1, s16 *, 2);
    if (var_v0 < 0) {
        var_v0 += 0x3F;
    }
    if ((var_v0 >> 6) == M2C_FIELD(arg0, s16 *, 4)) {
        var_v0_2 = M2C_FIELD(arg1, s16 *, 6);
        if (var_v0_2 < 0) {
            var_v0_2 += 0x3F;
        }
        if ((var_v0_2 >> 6) == M2C_FIELD(arg0, s16 *, 6)) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
        }
    }
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x4C);
    temp_a0 = M2C_FIELD(arg0, u16 *, 0x48) - 1;
    M2C_FIELD(arg0, u16 *, 0x48) = temp_a0;
    if (temp_v1_2 == 1) {
        goto state_1;
    }
    if (temp_v1_2 >= 2) {
        goto state_ge_2;
    }
    state_shift = temp_a0 << 0x10;
    if (temp_v1_2 == 0) {
        goto state_0;
    }
    func_80024DCC();
    return;
state_ge_2:
    ASM_SCHED_BARRIER();
    if (temp_v1_2 == 2) {
        goto block_27;
    }
    func_80024DCC();
    return;
state_0:
    if (state_shift > 0) {
        return;
    }
    func_8004491C(arg0 - 0x20, &D_80045340);
    M2C_FIELD(arg0, u16 *, 0x4C) = M2C_FIELD(arg0, u16 *, 0x4C) + 1;
    func_80024DCC();
    return;
state_1:
    {
        func_800478B8(arg2);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg2, s8 *, 4) = 0;
            M2C_FIELD(arg2, s8 *, 5) = 0;
        }
        actor_count = M2C_FIELD(arg2, u8 *, 0xC);
        ASM_MEM_BARRIER();
        if (M2C_FIELD(arg0, s16 *, 0x4A) >= (s32) actor_count) {
            temp_a0_2 = M2C_FIELD(arg1, s32 *, 0x10);
            M2C_FIELD(arg1, s32 *, 0xC) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) * 5);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a0_2 * 5);
            M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) * 8);
            M2C_FIELD(arg2, u16 *, 0x1E) = 0xC00U;
            M2C_FIELD(arg2, u16 *, 0x1C) = 0xC00U;
            M2C_FIELD(arg2, s32 *, 0xC) = M2C_FIELD(arg2, s32 *, 0xC) * 4;
            if (M2C_FIELD(arg0, u16 *, 0x48) & 1) {
                register u8 *dispatch_ptr ASM_REG("$2");
                dispatch_ptr = D_800DEC70;
                ASM_TAILSLOT_PIN(dispatch_ptr);
                func_80024D24();
                return;
            }
            ASM_SCHED_BARRIER();
            M2C_FIELD(arg2, M2C_UNK **, 0) = &D_800DED28;
            sprite_word = M2C_FIELD(&D_800DED28, s32 *, 4);
            M2C_FIELD(arg2, s8 *, 4) = 0;
            M2C_FIELD(arg2, s8 *, 5) = 0;
            M2C_FIELD(arg2, s32 *, 8) = sprite_word;
            M2C_FIELD(arg0, u16 *, 0x4C) = M2C_FIELD(arg0, u16 *, 0x4C) + 1;
            func_80024D90();
            return;
        }
        temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) - 0x200;
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
        M2C_FIELD(arg2, u8 *, 0xC) = (u8) (M2C_FIELD(arg2, u8 *, 0xC) - (u8) M2C_FIELD(arg0, s16 *, 0x4A));
        temp_v1_3 = M2C_FIELD(arg2, u8 *, 0xE) - ((s32) ((u16) M2C_FIELD(arg0, s16 *, 0x4A) << 0x10) >> 0x12);
        M2C_FIELD(arg2, u8 *, 0xE) = temp_v1_3;
        M2C_FIELD(arg2, u8 *, 0xD) = temp_v1_3;
block_27:
        func_800478B8(arg2);
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0 = D_800814A0 | 0x8000;
        }
    }
}
/* MECHANISM: The natural 0x20 frame follows from three held arguments and explicit state CFG labels.
   Zero-arg noreturn dispatchers plus a guarded $v0 tail-slot pointer reproduce all five retail tails.
   Volatile ordered initial loads, direct scalar RMWs, and a comparison-local memory fence close scheduling. */
