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

M2C_UNK strcat(); /* extern */
M2C_UNK *func_800A652C();                        /* extern */
M2C_UNK func_800B5264(); /* extern */
extern s32 D_800814A8;
extern M2C_UNK D_800892C0;
extern M2C_UNK D_800892C8;
extern M2C_UNK D_800892CC;
extern M2C_UNK D_800892D8;

typedef struct {
    s32 unk0;
    s8 unk4;
    u8 pad5[0x3B];
} StackData;

void func_800B52F4(s32 arg0, void *arg1) {
    StackData sp18;
    StackData *data;
    M2C_UNK *source;
    register u32 page ASM_REG("$2");
    register s32 word ASM_REG("$3");
    register s32 byte ASM_REG("$4");
    register s32 fifth ASM_REG("$2");
    register StackData *call_data ASM_REG("$5");

    page = 0x80090000;
    ASM_KEEP(page);
    source = (M2C_UNK *)(page - 0x6D40);
    ASM_KEEP(source);
    word = M2C_FIELD(source, s32 *, 0);
    ASM_USE(word);
    byte = M2C_FIELD(source, s8 *, 4);
    ASM_USE(byte);
    sp18.unk0 = word;
    sp18.unk4 = byte;
    ASM_SCHED_BARRIER();
    data = &sp18;
    ASM_KEEP(data);
    strcat(data, D_800814A8 + 0x34, source);
    strcat(data, &D_800892C8);
    strcat(data, &D_800892CC);
    strcat(data, &D_800892D8);
    strcat(data, func_800A652C(arg0));
    call_data = data;
    ASM_KEEP(call_data);
    fifth = 0x88;
    ASM_KEEP(fifth);
    func_800B5264(M2C_FIELD(arg1, s32 *, 0xC), call_data, 0, 0x47, fifth);
}

/* MECHANISM: A 64-byte stack object forces the 0x68 frame; s1/s2 hold args and s0 holds its address.
   A pinned page/base split plus separately fenced v1/a0 copy temps emits the retail lw/lb/sw/sb order.
   Held a1/v0 final-call arguments preserve the closing move/li/move ABI sequence. */
