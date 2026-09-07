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

M2C_UNK func_8006658C();                 /* extern */
M2C_UNK func_800666F4();                      /* extern */
void *func_800B0C64();                              /* extern */
void func_800B0D10(void) __attribute__((noreturn)); /* extern */

void *func_800B0BE0(s32 arg0, void *arg1, void **arg2, void *arg3) {
    s32 call_arg0;
    u32 tail_value;
    s8 temp_v0_2;
    s8 temp_v0_4;
    u8 temp_v0;
    u8 temp_v0_3;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    u16 temp_v1_4;

    M2C_FIELD(arg3, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
    func_800666F4(arg3);
    M2C_FIELD(arg3, u16 *, 0xE) = (u16) M2C_FIELD(*arg2, u16 *, 6);
    temp_v1_4 = M2C_FIELD(arg1, u16 *, 0x10);
    if (temp_v1_4 != 0) {
        tail_value = temp_v1_4 + (M2C_FIELD(*arg2, u16 *, 4) & 0xFF9F);
        ASM_TAILSLOT_PIN_TIED(tail_value);
        return func_800B0C64();
    }
    M2C_FIELD(arg3, u16 *, 0x16) = (u16) M2C_FIELD(*arg2, u16 *, 4);
    temp_v0 = M2C_FIELD(*arg2, u8 *, 8);
    M2C_FIELD(arg3, u8 *, 0x1C) = temp_v0;
    M2C_FIELD(arg3, u8 *, 0xC) = temp_v0;
    temp_v1 = *arg2;
    temp_v0_2 = (M2C_FIELD(temp_v1, u8 *, 8) + M2C_FIELD(temp_v1, u8 *, 0xA)) - 1;
    M2C_FIELD(arg3, s8 *, 0x24) = temp_v0_2;
    M2C_FIELD(arg3, s8 *, 0x14) = temp_v0_2;
    temp_v0_3 = M2C_FIELD(*arg2, u8 *, 9);
    M2C_FIELD(arg3, u8 *, 0x15) = temp_v0_3;
    M2C_FIELD(arg3, u8 *, 0xD) = temp_v0_3;
    temp_v1_2 = *arg2;
    ASM_SCHED_BARRIER();
    call_arg0 = arg0;
    
    temp_v0_4 = (M2C_FIELD(temp_v1_2, u8 *, 9) + M2C_FIELD(temp_v1_2, u8 *, 0xB)) - 1;
    M2C_FIELD(arg3, s8 *, 0x25) = temp_v0_4;
    M2C_FIELD(arg3, s8 *, 0x1D) = temp_v0_4;
    func_8006658C(call_arg0, arg3);
    temp_v1_3 = *arg2;
    arg3 += 0x28;
    if (M2C_FIELD(temp_v1_3, s8 *, 0) < 0) {
        *arg2 = NULL;
        func_800B0D10();
    }
    *arg2 = temp_v1_3 + 0xC;
    return arg3;
}

/* MECHANISM: Four live arguments naturally force the retail 0x28 frame and s3/s0/s2/s1 roles.
   A tied v0 tail-slot pin carries the masked size sum into the first dispatcher jump.
   The second dispatcher is noreturn; a scoped barrier holds its a0 setup in the retail load slot. */
