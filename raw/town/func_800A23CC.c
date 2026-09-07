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

void *func_8003C06C();        /* extern */
M2C_UNK func_800422DC();            /* extern */
M2C_UNK func_800423C0();      /* extern */
M2C_UNK func_80042640();               /* extern */
M2C_UNK memset(); /* extern */
s32 func_8009F970();              /* extern */
void *func_800B2344();                              /* extern */
extern M2C_UNK D_800102F0;
extern M2C_UNK D_80010324;
extern M2C_UNK D_80100A10;
typedef struct {
    s32 words[0x15];
} Record84;
extern Record84 D_80100AF8;

typedef struct Copy16 {
    s32 words[4];
} Copy16;

typedef struct Copy10 {
    s8 bytes[10];
} __attribute__((packed)) Copy10;

void func_8009FB2C(s32 arg0, void *arg1) {
    u8 *var_a2;
    u8 *var_s1;
    s32 temp_a1;
    s32 temp_v0_2;
    u8 *temp_a3;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v1;
    void *temp_a0;
    register void *result ASM_REG("$2");

    temp_v0 = func_800B2344();
    M2C_FIELD(temp_v0, u8 *, 0) = (u8) M2C_FIELD(arg1, u8 *, 0);
    M2C_FIELD(temp_v0, u8 *, 1) = (u8) M2C_FIELD(arg1, u8 *, 1);
    M2C_FIELD(temp_v0, u8 *, 2) = (u8) M2C_FIELD(arg1, u8 *, 2);
    M2C_FIELD(temp_v0, u8 *, 3) = (u8) M2C_FIELD(arg1, u8 *, 3);
    if (M2C_FIELD(temp_v0, u8 *, 1) == 0x13) {
        memset(&D_80100A10, 0, 0x54);
        func_80042640(&D_80100A10, M2C_FIELD(temp_v0, u8 *, 0));
        func_800423C0(&D_80100A10, M2C_FIELD(temp_v0, u8 *, 0), 0);
        {
            register u8 *addr ASM_REG("$17");
            addr = (u8 *)&D_80100AF8;
            ASM_KEEP(addr);
            var_s1 = addr;
            func_800422DC(addr, &D_80100A10);
        }
        temp_v0_2 = func_8009F970((void *)0x800102F0, 0x14);
        var_a2 = (temp_v0_2 * 0x54) + (u8 *)0x800102F0;
        temp_a3 = var_s1 + 0x50;
        do {
            *(Copy16 *)var_a2 = *(Copy16 *)var_s1;
            var_s1 += 0x10;
            var_a2 += 0x10;
        } while (var_s1 != temp_a3);
        *(s32 *)var_a2 = *(s32 *)var_s1;
        ASM_MEM_BARRIER();
        temp_s0 = (temp_v0_2 * 0x54) + (u8 *)0x80010324;
        temp_v0_3 = func_8003C06C(M2C_FIELD(temp_v0, u8 *, 0));
        *(Copy10 *)temp_s0 = *(Copy10 *)temp_v0_3;
        M2C_FIELD(temp_v0, u8 *, 3) = (u8) ((M2C_FIELD(temp_v0, u8 *, 3) & 0xC0) | temp_v0_2);
        ASM_KEEP(temp_v0);
        result = temp_v0;
    } else {
        result = temp_v0;
    }
    ASM_KEEP(result);
    temp_a0 = (void *)0x80010000;
    temp_v1 = (arg0 * 4) + temp_a0;
    M2C_FIELD(temp_v1, void **, 0x29C) = result;
    M2C_FIELD(temp_v1, s32 *, 0x2A0) = 0;
}
