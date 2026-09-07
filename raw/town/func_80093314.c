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

s32 func_80033B2C();                         /* extern */
M2C_UNK func_8008B158();                         /* extern */
M2C_UNK func_80090C44();                            /* extern */
M2C_UNK func_80093ED8();     /* extern */
M2C_UNK func_80094088();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_800943B8();     /* extern */
M2C_UNK func_800944BC();     /* extern */
M2C_UNK func_8009451C();     /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
s32 func_8009567C();            /* extern */
s32 func_80095840();               /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80098868();     /* extern */
extern u8 D_80083160[];
extern s32 D_800CFCB4;
extern M2C_UNK D_800CFCEF;
extern u8 D_800FE488[];

void func_80090A74(void *arg0, void *arg1, M2C_UNK arg2) {
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    register u8 *page_v0 ASM_REG("$2");
    register u8 *temp_s3 ASM_REG("$19");
    u8 *temp_s4 = D_80083160;

    func_80095C80(arg1);
    func_80095094(arg1);
    {
        register void *call_a0 ASM_REG("$4") = arg1;

        ASM_KEEP(call_a0);
        page_v0 = (u8 *)0x80100000;
        ASM_KEEP(page_v0);
        temp_s3 = page_v0 - 0x1B78;
        ASM_KEEP(temp_s3);
        temp_v0 = func_80095978(call_a0, temp_s3);
    }
    if ((temp_v0 - M2C_FIELD(arg1, s16 *, 0xA)) >= 4) {
        if (M2C_FIELD(&D_800CFCEF, u8 *, 0) == 0) {
            func_80094378(arg0, arg1, arg2);
            func_80090C44();
            return;
        }
        goto block_6;
    }
    if (M2C_FIELD(&D_800CFCEF, u8 *, 0) == 0) {
        func_80095A94(arg1, temp_v0, temp_s3);
    }
block_6:
    if (M2C_FIELD(temp_s4, s32 *, 0x10) & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        func_80090C44();
        return;
    }
    if (M2C_FIELD(temp_s4, s32 *, 0x10) & 0x40) {
        temp_v0_2 = func_80095840(arg0, &D_800CFCB4);
        if (temp_v0_2 != 0) {
            if (temp_v0_2 == 2) {
                func_8009451C(arg0, arg1, arg2);
                func_80090C44();
                return;
            }
            func_800944BC(arg0, arg1, arg2);
            func_80090C44();
            return;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(arg0, arg1, arg2);
            func_80090C44();
        }
    } else {
        page_v0 = (u8 *)0x800D0000;
        ASM_KEEP(page_v0);
        temp_s3 = page_v0 - 0x34C;
        ASM_KEEP(temp_s3);
        temp_v0_3 = func_8009567C(temp_s3);
        if (temp_v0_3 != 0) {
            if (temp_v0_3 == -1) {
                func_80094C1C(arg0);
                func_80098868(arg0, arg1, arg2);
                M2C_FIELD(arg0, s32 *, 0x2C) = 0;
                func_8008B158(M2C_FIELD(temp_s3, s32 *, 0x10));
                func_80090C44();
                return;
            }
            func_800943B8(arg0, arg1, arg2);
            func_80090C44();
            return;
        }
        if (M2C_FIELD(temp_s4, s32 *, 8) & 0xF000) {
            func_80093ED8(arg0, arg1, arg2);
        }
    }
}
/* MECHANISM: At 2.7.2-cdk-G0, s4 holds D_80083160 and s3 is reused for
   D_800FE488/D_800CFCB4 via pinned v0 page bases. The corrected one-argument
   func_8009567C ABI removes an extra move; a scoped a0 fence schedules the
   third-call argument before its page-base pair. */
