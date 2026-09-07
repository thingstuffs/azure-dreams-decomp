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
void func_800BD5A8(void);                          /* extern */
M2C_UNK func_800C4AFC();            /* extern */
extern M2C_UNK D_80082E80;
extern extern M2C_UNK D_80083460[3];
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E0E69;
extern void *D_800E3D7C[];

s32 func_800BD45C(void *arg0, s32 arg1, s16 arg2) {
    u16 *table;
    M2C_UNK *counter;

    if (arg0 == D_800E3D7C[0]) {
        M2C_FIELD(arg0, s32 *, 0x110) = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        func_800BD5A8();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        register void *call_obj ASM_REG("$4");
        register u8 *table_page ASM_REG("$3");
        u8 table_index;

        func_800A63B8(arg0, arg1, arg2);
        call_obj = arg0;
        ASM_USE(call_obj);
        table_page = (u8 *)0x800E0000;
        ASM_KEEP(table_page);
        table_index = M2C_FIELD(arg0, u8 *, 0x13);
        ASM_SCHED_BARRIER();
        table = (u16 *)(table_page - 0x217C);
        ASM_KEEP(table);
        if (func_800AD6FC(call_obj, (table[table_index] >> 6) & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BD5A8();
            return 1;
        }
        goto block_8;
    }
block_8:
    func_800C4AFC(M2C_FIELD(arg0, s32 *, -0x18), 0x802080, arg0);
    if ((M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) && !(M2C_FIELD(arg0, s32 *, 0x1C) & 0x40)) {
        register M2C_UNK *format_obj ASM_REG("$4");
        register s32 format_arg ASM_REG("$5");
        register s32 saved_result ASM_REG("$16");
        s32 raw_result;
        s32 format_result;

        raw_result = func_800990FC();
        format_obj = &D_800E0E69;
        ASM_USE(format_obj);
        format_arg = raw_result;
        ASM_USE(format_arg);
        saved_result = format_arg;
        format_result = func_80099194(format_obj, format_arg);
        func_80099290(format_result);
        func_800A5720(saved_result);
    }
    func_80042B68(arg0, 5);
    func_80098B38(arg1);
    counter = D_80083460;
    ASM_KEEP(counter);
    M2C_FIELD(counter, u16 *, 0xA) = (u16) (M2C_FIELD(counter, u16 *, 0xA) - 1);
    return 1;
}

/* MECHANISM: The natural 0x20 frame holds arg0/arg1 in s1/s2 and the saved formatter input in s0.
   LEAD-22 void calls plus explicit returns place 0/1 in both dispatcher jump delay slots.
   A held v1 page, fenced lbu, and low-half addiu reproduce the split table address sequence.
   Scoped a0/a1 carriers order the formatter result v0 -> a1 -> s0 exactly. */
