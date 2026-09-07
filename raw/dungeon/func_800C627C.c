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

M2C_UNK func_80040AA0();               /* extern */
M2C_UNK func_800478B8();                      /* extern */
M2C_UNK func_800481E0();                            /* extern */
M2C_UNK func_800945E8();           /* extern */
M2C_UNK func_800948BC();                            /* extern */
M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800A32A4();                      /* extern */
M2C_UNK func_800A6780();                            /* extern */
M2C_UNK func_800CBB58();                            /* extern */
extern s32 D_80010234;
extern M2C_UNK D_80013714;
extern s16 D_80081468[3];
extern M2C_UNK D_800814A0;
extern u8 D_80082E6B;
extern M2C_UNK D_80083460;
extern u8 *D_800E3D7C;

void func_800CB9DC(void *arg0_in, void *arg1_in, void *arg2_in) {
    register void *arg0 ASM_REG("$19") = arg0_in;
    register void *arg1 ASM_REG("$16") = arg1_in;
    register void *arg2 ASM_REG("$18") = arg2_in;
    M2C_UNK *temp_a1;
    M2C_UNK var_a2;
    s32 temp_v1;
    u16 temp_v0;
    void *temp_a0;
    void *temp_s1;

    func_800478B8(arg2);
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    temp_s1 = M2C_FIELD(arg0, void **, 0);
    temp_a1 = M2C_FIELD(temp_s1, M2C_UNK **, -0x14);
    temp_a0 = M2C_FIELD(temp_s1, void **, -0x18);
    temp_v1 = M2C_FIELD(arg1, s32 *, 0x14) + 0xFFFA0000;
    M2C_FIELD(arg1, s32 *, 0x14) = temp_v1;
    M2C_FIELD(temp_a0, s32 *, 8) = (s32) (M2C_FIELD(temp_a0, s32 *, 8) + temp_v1);
    temp_v0 = M2C_FIELD(arg0, u16 *, 6) + 1;
    M2C_FIELD(arg0, u16 *, 6) = temp_v0;
    if (((s16) temp_v0 >= 0x41) || ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) != 0)) {
        if (temp_s1 == D_800E3D7C) {
            register s16 *counts ASM_REG("$5");
            register u8 call_a0 ASM_REG("$4");
            register u8 *page8 ASM_REG("$2");
            register s32 count32 ASM_REG("$2");
            register u16 count16 ASM_REG("$3");

            arg1 = (void *)0x80010000;
            ASM_KEEP(arg1);
            if (M2C_FIELD(arg1, u16 *, 0x3714) & 4) {
                func_80040AA0(3U, temp_a1);
                func_800CBB58();
                return;
            }
            func_800945E8(temp_s1, temp_a1);
            func_800948BC();
            func_800A6780();
            page8 = (u8 *)0x80080000;
            ASM_KEEP(page8);
            counts = D_80081468;
            call_a0 = page8[0x2E6B];
            count32 = M2C_FIELD(arg1, s32 *, 0x234);
            count16 = M2C_FIELD(counts, u16 *, 4);
            count32++;
            count16++;
            M2C_FIELD(arg1, s32 *, 0x234) = count32;
            M2C_FIELD(counts, u16 *, 4) = count16;
            func_80040AA0(call_a0, counts);
            func_800481E0();
            func_800CBB58();
            return;
        }
        {
            register s32 call2_a0 ASM_REG("$4");
            register s32 call2_a1 ASM_REG("$5");
            register s32 flags ASM_REG("$2");

            flags = M2C_FIELD(temp_s1, s32 *, 0x1C);
            call2_a0 = M2C_FIELD(temp_a1, u8 *, 0x24);
            call2_a1 = M2C_FIELD(temp_a1, u8 *, 0x25);
            var_a2 = 0x3000;
            if (flags & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(call2_a0, call2_a1, var_a2);
        }
        func_800A32A4(temp_s1);
        func_8009A028(temp_s1);
        {
            register u8 *page14 ASM_REG("$5");
            register u8 *base34 ASM_REG("$4");
            register s32 global_value ASM_REG("$2");
            register u16 dec_value ASM_REG("$3");
            register u8 *page14_again ASM_REG("$3");
            u16 halfword;

            page14 = (u8 *)0x80080000;
            base34 = (u8 *)&D_80083460;
            halfword = M2C_FIELD(temp_s1, u16 *, -2);
            M2C_FIELD(temp_s1, u16 *, -2) = halfword | 0x8000;
            global_value = M2C_FIELD(page14, s32 *, 0x14A0);
            dec_value = M2C_FIELD(base34, u16 *, 0xA);
            global_value |= 0x8000;
            dec_value--;
            M2C_FIELD(page14, s32 *, 0x14A0) = global_value;
            M2C_FIELD(base34, u16 *, 0xA) = dec_value;
            ASM_CLOBBER("$5");
            halfword = M2C_FIELD(arg0, u16 *, -2);
            page14_again = (u8 *)0x80080000;
            M2C_FIELD(arg0, u16 *, -2) = halfword | 0x8000;
            global_value = M2C_FIELD(page14_again, volatile s32 *, 0x14A0);
            global_value |= 0x8000;
            M2C_FIELD(page14_again, s32 *, 0x14A0) = global_value;
        }
    }
}
/* MECHANISM: Pinned long-lived args reproduce the s3/s0/s2 prologue, with keeps after the first call.
   Split RMW locals and ABI-pinned call args recover both interleaved load/store schedules.
   Held page bases plus a symbolic D_80083460 base and dead-$a1 clobber force the final rematerialization. */
