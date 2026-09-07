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

typedef struct {
    s32 words[3];
} TableEntry;

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_80026680[3];
extern TableEntry D_80028820[];
extern s32 D_80083498[3];
extern s32 D_800CEEFC[3];
extern u8 D_800DDC40[9];

void *func_80026C88(u16 arg0, u16 arg1, s32 arg2, void *arg3)
{
    u16 position[3];
    s32 *callback;
    TableEntry *var_s2;
    s32 var_s1;
    register void *temp_a0 ASM_REG("$4");
    void *temp_a2;
    void *temp_v0;
    register void *var_a1 ASM_REG("$5");
    register void *callee_arg ASM_REG("$5");
    register u16 *position_arg ASM_REG("$6");
    register s32 held_arg2 ASM_REG("$21");
    register void *var_s6 ASM_REG("$22");

    held_arg2 = arg2;
    var_s6 = NULL;
    callee_arg = arg3;
    position_arg = position;
    ASM_KEEP(callee_arg);
    ASM_KEEP(position_arg);
    position[0] = position[1] = 0;
    if (func_8003DE58(M2C_FIELD(callee_arg, s32 *, 8), callee_arg, position_arg, 0) == 0) {
        position[2] = (0 - D_800DDC40[0]) + 0x10;
    }
    callback = D_80026680;
    var_s1 = 0;
    do { var_s2 = D_80028820; } while (0);
    do {
        temp_v0 = func_8003FD64(0x212, D_80083498);
        if (temp_v0 != NULL) {
            register s32 var_t0 ASM_REG("$8");
            register void *temp_a3 ASM_REG("$7");
            void *self_link;

            M2C_FIELD(temp_v0, s32 **, 0x10) = callback;
            func_8004491C(temp_v0, D_800CEEFC);
            temp_a3 = temp_v0 + 0x20;
            M2C_FIELD(temp_a3, s16 *, 0x1A) = (s16) (arg0 + position[0]);
            M2C_FIELD(temp_a3, s16 *, 0x1E) = (s16) (arg1 + position[1]);
            var_t0 = 0;
            M2C_FIELD(temp_a3, s16 *, 0x22) = (s16) (held_arg2 + position[2]);
            temp_a2 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_a2, u16 *, 2) = arg0;
            M2C_FIELD(temp_a2, u16 *, 0xE) = arg0;
            M2C_FIELD(temp_a2, u16 *, 6) = arg1;
            M2C_FIELD(temp_a2, u16 *, 0x12) = arg1;
            M2C_FIELD(temp_a2, u16 *, 0xA) = held_arg2 - 0x100;
            M2C_FIELD(temp_a2, u16 *, 0x16) = held_arg2 - 0x100;
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            var_a1 = temp_a3;
            M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
            self_link = temp_v0 + 0x38;
            M2C_FIELD(temp_a0, TableEntry **, 8) = var_s2;
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
            ASM_KEEP(temp_a0);
            M2C_FIELD(temp_v0, void **, 0x20) = self_link;
            M2C_FIELD(temp_a3, s16 *, 0x66) = 0x20;
            M2C_FIELD(temp_a3, s16 *, 0x6E) = var_s1;
            do {
                M2C_FIELD(var_a1, u16 *, 0x24) = (u16) M2C_FIELD(temp_a2, u16 *, 2);
                M2C_FIELD(var_a1, u16 *, 0x26) = (u16) M2C_FIELD(temp_a2, u16 *, 6);
                var_t0 += 1;
                M2C_FIELD(var_a1, u16 *, 0x28) = (u16) M2C_FIELD(temp_a2, u16 *, 0xA);
                var_a1 += 8;
            } while (var_t0 < 8);
            ASM_KEEP(var_a1);
            ASM_KEEP(var_t0);
            M2C_FIELD(temp_a3, void **, 8) = var_s6;
            ASM_KEEP(temp_a3);
            var_s6 = temp_v0;
        }
        var_s1 += 1;
        var_s2 += 1;
    } while (var_s1 < 6);
    ASM_KEEP(held_arg2);
    ASM_KEEP(var_s6);
    return temp_v0;
}

/* MECHANISM: position[3] owns the three halfword stack slots; s5/s6 hold arg2/list head.
   Guarded ABI/block pins preserve a1/a2 call setup and a3/t0/a0/a1 copy-loop roles.
   A split self_link computation and direct arg2-0x100 stores prevent unwanted hoisting. */
