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

void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80077854;
extern M2C_UNK D_801714AC;
extern s16 D_80173AFC[];
extern void *D_80175D54;
extern void *D_80175DB8;

void func_801715D0(void) {
    register s32 temp_a0_2 ASM_REG("$4");
    register s32 temp_a0_3 ASM_REG("$4");
    register s32 var_v0 ASM_REG("$2");
    register s32 var_v0_2 ASM_REG("$2");
    register void *temp_a0 ASM_REG("$4");
    void *temp_s1;
    void *temp_s2;
    u8 *entry;
    u8 *table;
    register void *temp_s3 ASM_REG("$19");
    void *temp_v0;
    void *temp_v1;
    register void *temp_v1_2 ASM_REG("$3");

    temp_s2 = M2C_FIELD(D_80175D54, void **, 8);
    temp_s1 = D_80175D54 + 0x20;
    temp_v0 = func_8003FD64(0x12, D_80175D54);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_801714AC;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_s3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) ((M2C_FIELD(temp_v1, u16 *, 0x14) & 0xFFF3) | 0x80);
        M2C_FIELD(temp_s3, void **, 0x24) = temp_s1;
        temp_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_a0, u16 *, 2) = (u16) M2C_FIELD(temp_s2, u16 *, 2);
        M2C_FIELD(temp_a0, u16 *, 6) = (u16) M2C_FIELD(temp_s2, u16 *, 6);
        M2C_FIELD(temp_a0, u16 *, 0xA) = (u16) M2C_FIELD(temp_s2, u16 *, 0xA);
        table = (u8 *) 0x80170000;
        ASM_KEEP(table);
        table += 0x3AFC;
        entry = (u8 *) ((u32) (((u16) M2C_FIELD(temp_s1, u16 *, 0x2A) >> 7) & 0x1C) + (u32) table);
        M2C_FIELD(temp_a0, u16 *, 2) = (u16) (M2C_FIELD(temp_a0, u16 *, 2) + (M2C_FIELD(entry, s16 *, 0) * 6));
        entry = (u8 *) ((u32) (((u16) M2C_FIELD(temp_s1, u16 *, 0x2A) >> 7) & 0x1C) + (u32) table);
        M2C_FIELD(temp_a0, u16 *, 6) = (u16) (M2C_FIELD(temp_a0, u16 *, 6) + (M2C_FIELD(entry, s16 *, 2) * 6));
        ASM_KEEP(table);
        ASM_KEEP(temp_a0);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
        temp_a0_2 = (s16) M2C_FIELD(temp_s2, u16 *, 2);
        var_v0 = temp_a0_2 - 0x20;
        if (var_v0 < 0) {
            var_v0 = (s32) (temp_a0_2 + 0x1F) >> 6;
        } else {
            var_v0 >>= 6;
        }
        ASM_KEEP(temp_a0_2);
        M2C_FIELD(temp_s3, s8 *, 0x58) = (s8) var_v0;
        ASM_KEEP(var_v0);
        temp_a0_3 = (s16) M2C_FIELD(temp_s2, u16 *, 6);
        var_v0_2 = temp_a0_3 - 0x20;
        if (var_v0_2 < 0) {
            var_v0_2 = (s32) (temp_a0_3 + 0x1F) >> 6;
        } else {
            var_v0_2 >>= 6;
        }
        ASM_KEEP(temp_a0_3);
        M2C_FIELD(temp_s3, s8 *, 0x59) = (s8) var_v0_2;
        ASM_KEEP(var_v0_2);
        ASM_KEEP(temp_s3);
        M2C_FIELD(temp_v1_2, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_v1_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_v1_2, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_v1_2, M2C_UNK **, 8) = &D_80077854;
        ASM_KEEP(temp_v1_2);
        D_80175DB8 = temp_v0;
    }
}

/* MECHANISM: Last-use pins hold the object+0x20 base in s3 and the a0/v0/v1 live-range roles, yielding the retail 0x28 frame.
   A held 0x80170000 page plus addiu 0x3AFC prevents the table low half from folding into its signed halfword loads.
   Named integer-form index+base sums preserve addu v0,v0,a1; shared v0 normalization and u8 color stores close the tail. */
