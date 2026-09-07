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
typedef struct {
    s32 value;
} __attribute__((packed)) Packed4;

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

M2C_UNK func_80047784();         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_8009929C();                    /* extern */
M2C_UNK func_80099368();                 /* extern */
s32 func_80099734();                     /* extern */
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
s32 func_800A6D30();                                /* extern */
void *func_80170908();                /* extern */
M2C_UNK func_8017437C();                   /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern M2C_UNK D_8017089C;
extern M2C_UNK D_801708AC;
extern M2C_UNK D_801708B8;
extern M2C_UNK D_801708BC;
extern u8 D_80174F58[];

void func_80174234(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_s2;
    s32 temp_v0;
    register s32 temp_field ASM_REG("$2");
    void *temp_v0_2;
    register void *temp_a0 ASM_REG("$4");
    u8 *end_base;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8) (M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
            temp_field = M2C_FIELD(arg3, s32 *, 0x14);
            ASM_KEEP(temp_field);
            if (temp_field >= 0) {
                M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_field | 0x80000000);
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16) (M2C_FIELD(arg3, u16 *, 0x2A) + ((func_800A6D30() & 7) << 9));
            }
        }
        temp_s2 = func_800990FC();
        if (M2C_FIELD(arg3, u8 *, 0x49) == 0) {
            temp_v0_2 = func_80170908(arg2, arg3);
            if (temp_v0_2 != NULL) {
                M2C_FIELD(arg3, Packed4 *, 0x48) = *(Packed4 *) temp_v0_2;
                temp_v0 = func_80099368(temp_v0_2, func_80099194(&D_801708AC, func_8009929C(0xA, func_80099194(&D_8017089C, func_80099734(arg3, temp_s2)))));
                temp_a0 = &D_801708B8;
            } else {
                temp_v0 = func_80099734(arg3, temp_s2);
                temp_a0 = &D_801708BC;
            }
        } else {
            temp_v0 = func_80099734(arg3, temp_s2);
            temp_a0 = &D_801708BC;
        }
        ASM_KEEP(temp_a0);
        func_80099290(func_80099194(temp_a0, temp_v0));
        func_800A5720(temp_s2);
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        M2C_FIELD(arg2, u8 **, 0x2C) = D_80174F58;
        func_80047784(arg2, D_80174F58[((D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        end_base = (u8 *) &D_80083460;
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        M2C_FIELD(end_base, u16 *, 0xA) = (u16) (M2C_FIELD(end_base, u16 *, 0xA) + 1);
    }
}

/* MECHANISM: The four-argument ABI and true-space merge preserve retail's s1/a3, s4/a2, s3/a0, s2/s0 roles.
   A packed four-byte assignment restores lwl/lwr/swl/swr; guarded v0-field and a0-merge pins close local roles.
   Byte-table indexing plus a held D_80083460 base fixes the tail and its one-word displacement cascade.
   The final packed-copy scratch is v0 only at 2.7.2-cdk-G0; 2.8.1-G0 leaves the four-word t0 residue. */
