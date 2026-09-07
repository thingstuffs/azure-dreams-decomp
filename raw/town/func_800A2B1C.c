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

void *func_8003FD64();            /* extern */
s32 func_8004A658();                          /* extern */
M2C_UNK func_8008F0D4();   /* extern */
M2C_UNK func_8009B218(); /* extern */
M2C_UNK func_800A022C(); /* extern */
void func_800A0390() __attribute__((noreturn));   /* extern */
void *func_800A03B8();                              /* extern */
extern M2C_UNK D_8006E240;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8009DEBC;
extern M2C_UNK D_800D073C;
extern M2C_UNK D_800D0754;
extern M2C_UNK D_800D076C;

void *func_800A027C(void *arg0, void *arg1) {
    u8 temp_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x136, &D_80083498);
    if (temp_v0 == NULL) {
        func_800A03B8();
        return NULL;
    }
    temp_s2 = M2C_FIELD(temp_v0, void **, 8);
    temp_s1 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_s2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_s2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
    temp_s0 = temp_v0 + 0x20;
    M2C_FIELD(temp_s2, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    M2C_FIELD(temp_s1, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s1, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s1, s32 *, 0xC) = 0x808080;
    M2C_FIELD(temp_s0, s32 *, 0x48) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x98) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x93) = 0;
    M2C_FIELD(temp_s0, u8 *, 0x4C) = (u8) M2C_FIELD(arg0, u8 *, 0);
    M2C_FIELD(temp_s0, u8 *, 0x4D) = (u8) M2C_FIELD(arg0, u8 *, 1);
    M2C_FIELD(temp_s0, u8 *, 0x4E) = (u8) M2C_FIELD(arg0, u8 *, 2);
    M2C_FIELD(temp_s0, u8 *, 0x4F) = (u8) M2C_FIELD(arg0, u8 *, 3);
    func_8008F0D4(temp_s0, temp_s2, &D_800D073C);
    func_8009B218(temp_s0, temp_s2, temp_s1, &D_800D076C);
    temp_a0 = M2C_FIELD(temp_s0, u8 *, 0x4D);
    if (temp_a0 == 0x12) {
        M2C_FIELD(temp_s0, M2C_UNK **, 0xC) = &D_800D0754;
        if (temp_a0 == M2C_FIELD(temp_s0, u8 *, 0x4D)) {
            void *tail_value;

            tail_value = &D_8006E240;
            ASM_TAILSLOT_PIN(tail_value);
            func_800A0390();
            return tail_value;
        }
    }
    M2C_FIELD(temp_s1, s32 *, 8) = func_8004A658(M2C_FIELD(temp_s0, u8 *, 0x4D), M2C_FIELD(temp_s0, u8 *, 0x4C));
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8009DEBC;
    ASM_SCHED_BARRIER();
    func_800A022C(temp_s0, temp_s0, temp_s2, temp_s1);
    
    return temp_v0;
}

/* MECHANISM: Explicit call-then-constant returns select the retail LEAD-22/18 tail shapes.
   Pinning only the +8 base to s2 lets the +0xC base fall naturally to s1 and preserves the load-delay fill.
   A distinct reload plus ASM_TAILSLOT_PIN retains the CSE compare and sinks D_8006E240's low half into the tail-j.
   ASM_SCHED_BARRIER after the callback store preserves retail's store-before-final-argument order. */
