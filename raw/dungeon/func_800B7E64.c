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

M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_8008D330(); /* extern */
M2C_UNK func_80098B38();                         /* extern */
s32 func_800990FC(void);                          /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
M2C_UNK func_800A5720();                         /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
void func_800BD710();                                /* extern */
M2C_UNK func_800C4AFC();            /* extern */
typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;
extern M2C_UNK D_80082E80;
extern D_80083460_t D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0E82;
extern void *D_800E3D7C[];

s32 func_800BD5C4(void *arg0, s32 arg1, s16 arg2) {
    register u16 *table ASM_REG("$3");
    register void *call_arg ASM_REG("$4");
    register s32 pass_value ASM_REG("$5");
    register s32 saved_value ASM_REG("$16");
    D_80083460_t *state;
    s32 table_index;
    s32 temp_v0;
    s32 result;

    if (arg0 == D_800E3D7C[0]) {
        M2C_FIELD(arg0, s32 *, 0x110) = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        func_800BD710();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        call_arg = arg0;
        ASM_KEEP(call_arg);
        table = (u16 *)0x800E0000;
        ASM_KEEP(table);
        table_index = M2C_FIELD(arg0, u8 *, 0x13);
        ASM_KEEP(table_index);
        table = (u16 *)((u8 *)table - 0x217C);
        ASM_KEEP(table);
        if (func_800AD6FC(call_arg, (table[table_index] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BD710();
            return 1;
        }
        goto block_8;
    }
block_8:
    func_800C4AFC(M2C_FIELD(arg0, s32 *, -0x18), 0xC02020, arg0);
    if ((M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) && !(M2C_FIELD(arg0, s32 *, 0x1C) & 0x400)) {
        temp_v0 = func_800990FC();
        call_arg = &D_800E0E82;
        ASM_KEEP(call_arg);
        pass_value = temp_v0;
        saved_value = pass_value;
        result = func_80099194(call_arg, pass_value);
        func_80099290(result);
        func_800A5720(saved_value);
    }
    func_80042B68(arg0, 2);
    func_80098B38(arg1);
    state = &D_80083460;
    state->fieldA = (u16) (state->fieldA - 1);
    return 1;
}

/* MECHANISM: The measured pins retain the exact 0x20 frame, s1/s2 argument holds, and s0 call result.
   A short-lived state=&D_80083460 makes cdk-G0 hold the symbol base and use lhu/sh 10(a0).
   Plain 2.7.2 folds to D_80083460+10 with offset 0; rerouting to 2.7.2-cdk-G0 closes all 3 tail subs. */
