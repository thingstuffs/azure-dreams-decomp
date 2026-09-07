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

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_80033AE8();                     /* extern */
s32 func_80033B2C();                         /* extern */
M2C_UNK func_80048D20();                            /* extern */
s32 func_80048D40();                                /* extern */
M2C_UNK func_800902C0();                            /* extern */
M2C_UNK func_800902F4();                            /* extern */
M2C_UNK func_80094984(); /* extern */
M2C_UNK func_80098868(); /* extern */
M2C_UNK func_80098928(); /* extern */
M2C_UNK func_80099764();                   /* extern */
extern s32 D_80080A80;
extern u8 D_80082E80[];
extern s32 D_800834B8;
extern s32 D_80083780;
extern u8 D_8008FFC0[];
extern M2C_UNK D_80097D54;
extern u8 D_800D0078[];
extern s32 D_800D0438;

void func_80090210(void) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;
    u8 *base_83780 = (u8 *)&D_80083780;
    u8 *base_82E80 = D_80082E80;
    u8 *base_834B8 = (u8 *)&D_800834B8;
    u8 *callback_page;
    M2C_UNK (*callback)();

    if (M2C_FIELD(base_834B8, s32 *, -0x10) != D_8008FFC0) {
        if (func_80033B2C(0x1202) == 0) {
            M2C_FIELD(base_834B8, s16 *, 0x16) = 0;
            temp_s0 = func_80033B2C(0x1202);
            if (temp_s0 != func_80033B2C(0x9D)) {
                register u32 dead_result_page ASM_REG("$3");

                func_80048D20();
                dead_result_page = 0x80080000;
                ASM_PAGEBASE_PIN(dead_result_page);
                func_800902C0();
                return;
            }
            goto block_7;
        }
        M2C_FIELD(base_834B8, s16 *, 0x16) = 1;
        temp_s0_2 = func_80033B2C(0x1202);
        if (temp_s0_2 != func_80033B2C(0x9D)) {
            temp_v0 = func_80048D40();
            D_80080A80 = temp_v0;
            M2C_FIELD(base_82E80, s32 *, 0x28) = temp_v0;
        }
block_7:
        if (func_80033B2C(0x1202) != 0) {
            register u32 dead_arg_page ASM_REG("$4");

            func_80033AA8(0x9D);
            dead_arg_page = 0x800D0000;
            ASM_PAGEBASE_PIN(dead_arg_page);
            func_800902F4();
            return;
        }
        func_80033AE8(0x9D);
        func_80094984(D_800D0078, base_834B8, base_82E80);
        func_80099764(base_834B8);
        func_80098868(base_834B8, base_83780, base_82E80);
        func_80098928(base_834B8, base_83780, base_82E80);
        {
            register u8 *handler_page ASM_REG("$2");

            handler_page = (u8 *)0x80090000;
            ASM_KEEP(handler_page);
            callback_page = (u8 *)0x800D0000;
            callback = M2C_FIELD(callback_page, M2C_UNK (**)(), 0x438);
            ASM_SCHED_BARRIER();
            M2C_FIELD(base_834B8, M2C_UNK **, 4) =
                (M2C_UNK *)(handler_page + 0x7D54);
            M2C_FIELD(base_834B8, s16 *, 0xA) = 0x10;
            if (callback != NULL) {
                callback();
                M2C_FIELD(callback_page, s32 *, 0x438) = 0;
            }
        }
    }
}

/* MECHANISM: Early pointer locals force the 0x28 frame and s3/s2/s1 held bases; s0 is reused for the callback page.
   LEAD-27 page pins supply the two dead lui fillers consumed by the LEAD-22 sibling-call jumps.
   A guarded v0 0x80090000 page plus a scheduling seam orders the callback load before the handler low-half/store. */
