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
typedef struct StackPair {
    s32 first;
    s32 second;
} StackPair;

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
extern int D_800814A8[4];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s16 D_800269F8[5];
extern s32 D_80083460[3];
extern s32 D_800814A0[3];
extern void *D_80024008[];
void func_80024238(void) __attribute__((noreturn)); /* extern */
void func_8002423C(void) __attribute__((noreturn)); /* extern */
void func_80024294(void) __attribute__((noreturn)); /* extern */
s32 func_800244EC();                     /* extern */
M2C_UNK func_800263F0();                         /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern s32 D_800269D0;
extern M2C_UNK D_80027750;
extern M2C_UNK D_80027C74;
extern s16 D_80027C94;
extern u8 D_80027C96;
extern void *D_80027C98;

void func_80024064(void *arg0) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    StackPair stack_args;
    s16 temp_a0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_v1;
    s32 temp_v0;
    u8 temp_u8;
    void *temp_a1;
    S_8003E2D8 *global_base;
    void *state_base;
    void *arg_value;
    s32 *base_83460;

    global_base = &D_80083160;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    if ((u32) temp_v1 >= 5U) {
        goto block_15;
    }
    (void)jt_keep; goto *D_80024008[(u32)(temp_v1)];
jt_c0:
    stack_args.first = 0x010003A0;
    stack_args.second = 0x400020;
    func_80040490(&D_80027750, &stack_args);
    func_8003F80C(&D_80027C74, 0x7AC0, 1, 2);
    D_80027C94 = 1;
    temp_u8 = M2C_FIELD(arg0, u8 *, 9);
    state_base = M2C_FIELD(D_800814A8, void **, 0);
    D_800269D0 = 0;
    D_80027C96 = temp_u8;
    arg_value = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(state_base, s32 *, 0xF4) = 0;
    D_80027C98 = arg_value;
    M2C_FIELD(state_base, u8 *, 0xA8) = (u8) M2C_FIELD(arg0, u8 *, 8);
    func_800263F0(state_base);
    M2C_FIELD(M2C_FIELD(D_800814A8, void **, 0), s16 *, 0x96) = 0x14;
    M2C_FIELD(M2C_FIELD(D_800814A8, void **, 0), s8 *, 0x102) = 1;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
jt_c1:
    if (!(*M2C_FIELD(arg0, u16 **, 4) & 0x80)) {
        goto block_15;
    }
    temp_a1 = M2C_FIELD(arg0, void **, 0);
    temp_v0 = func_800244EC(M2C_FIELD(temp_a1, s32 *, -0x18), temp_a1);
    M2C_FIELD(arg0, s32 *, 0xC) = temp_v0;
    if (temp_v0 == 0) {
        goto block_15;
    }
    M2C_FIELD(arg0, s16 *, 0x20) = -1;
    M2C_FIELD(arg0, s16 *, 0x22) = 0x20;
    func_800A56E0(0x300);
    func_80024238();
    return;
jt_c2:
    temp_v1 = 0x10;
    if (D_80027C94 != 0) {
        goto block_15;
    }
    M2C_FIELD(arg0, s16 *, 0x1A) = (s16) temp_v1;
    (void) M2C_FIELD(arg0, volatile u16 *, 0xA);
    func_8002423C();
    return;
jt_c3:
    M2C_FIELD(global_base, u8 *, 0xA9) = (u8) (M2C_FIELD(global_base, u8 *, 0xA9) + ((s32) (0x80 - M2C_FIELD(global_base, u8 *, 0xA9)) / (s16) M2C_FIELD(arg0, s16 *, 0x1A)));
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x1A);
    M2C_FIELD(global_base, u8 *, 0xA8) = (u8) (M2C_FIELD(global_base, u8 *, 0xA8) + ((s32) (0x80 - M2C_FIELD(global_base, u8 *, 0xA8)) / temp_a0));
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x1A) - 1;
    M2C_FIELD(arg0, s16 *, 0x1A) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_15;
    }
    M2C_FIELD(global_base, u8 *, 0xA9) = 0x80U;
    M2C_FIELD(global_base, u8 *, 0xA8) = 0x80U;
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0xA) + 1;
    func_80024294();
    return;
jt_c4:
    if ((s16) *D_800269F8 != 0) {
        goto block_15;
    }
    base_83460 = D_80083460;
    M2C_FIELD(base_83460, s32 *, 0xC) = 0;
    M2C_FIELD(base_83460, u16 *, 0xA) = (u16) (M2C_FIELD(base_83460, u16 *, 0xA) - 1);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
block_15:
    if (M2C_FIELD(arg0, s16 *, 0x20) >= 0) {
        goto block_18;
    }
    M2C_FIELD(global_base, u8 *, 0xA9) = (u8) (M2C_FIELD(global_base, u8 *, 0xA9) + ((s32) (0x20 - M2C_FIELD(global_base, u8 *, 0xA9)) / (s16) M2C_FIELD(arg0, s16 *, 0x22)));
    M2C_FIELD(global_base, u8 *, 0xA8) = (u8) (M2C_FIELD(global_base, u8 *, 0xA8) + ((s32) (0x20 - M2C_FIELD(global_base, u8 *, 0xA8)) / (s16) M2C_FIELD(arg0, s16 *, 0x22)));
    temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 0x22) - 1;
    M2C_FIELD(arg0, s16 *, 0x22) = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_18;
    }
    M2C_FIELD(arg0, s16 *, 0x20) = 0;
block_18:
    *D_800269F8 = 0;
    return;
}
/* Warning: struct S_8003E2D8 is not defined (only forward-declared) */
