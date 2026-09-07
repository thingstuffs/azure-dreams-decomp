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

s32 func_8001D280();                   /* extern */
s32 func_8001E7E4();                         /* extern */
extern void *D_80016000;
extern s16 D_8001902C[];

void func_8001D048(void) {
    s32 result;
    s32 call_result;
    register s32 arg0 ASM_REG("$4");
    register long work_s0 ASM_REG("$16");
    register unsigned long temp_v0 ASM_REG("$2");
    register s32 mode ASM_REG("$18");
    register s32 outer ASM_REG("$19");
    register s32 row_offset ASM_REG("$21");
    register s32 check_offset ASM_REG("$23");
    register s32 mode_offset ASM_REG("$22");
    register u8 value ASM_REG("$17");
    register s8 *row ASM_REG("$20");
    register s8 *check_base ASM_REG("$7");
    s16 *bounds;
    register void *global_base ASM_REG("$3");
    register void *callback_base ASM_REG("$2");
    register M2C_UNK (*callback)(s32, u8, s32) ASM_REG("$2");

    work_s0 = (long)M2C_FIELD(D_80016000, s8 **, 0x38);
    result = func_8001E7E4(1);
    mode = 0;
    if (result != 0) {
        goto mode_done;
    }
    result = func_8001E7E4(2);
    mode = 2;
    if (result == 0) {
        goto mode_done;
    }
    mode = 1;
mode_done:
    ASM_KEEP(mode);
    outer = 0;
    ASM_KEEP(outer);
    row_offset = outer;
    ASM_KEEP(row_offset);
    row = (s8 *)work_s0;
    ASM_KEEP(row);
    check_offset = mode * 8;
    ASM_KEEP(check_offset);
    do {
        check_base = (s8 *)D_8001902C;
        ASM_KEEP(check_base);
        temp_v0 = (unsigned long)check_offset + (unsigned long)check_base;
        ASM_KEEP(temp_v0);
        work_s0 = 0;
        if (*(s16 *)temp_v0 > 0) {
            temp_v0 = 0x80020000UL;
            ASM_KEEP(temp_v0);
            bounds = (s16 *)(temp_v0 - 0x6FD4);
            mode_offset = mode * 8;
            ASM_KEEP(mode_offset);
loop_6:
            value = M2C_FIELD(row + work_s0, u8 *, 0x3640);
            if (value != 0) {
                call_result = func_8001D280(outer, work_s0, mode);
                global_base = D_80016000;
                ASM_USE(global_base);
                arg0 = call_result;
                ASM_KEEP(arg0);
                callback_base = M2C_FIELD(global_base, void **, 0x20);
                callback = M2C_FIELD(callback_base, M2C_UNK (**)(s32, u8, s32), 0x2D0);
                callback(arg0, value, mode);
                work_s0 += 1;
                if (work_s0 < *(s16 *)((long)(mode_offset + row_offset) + (long)bounds)) {
                    goto loop_6;
                }
            }
        }
        row_offset += 0x18;
        row += 0xC;
        outer += 1;
        check_offset += 0x18;
    } while (outer < 0x10);
}

/* MECHANISM: Separate byte offsets keep row_offset in s5 and the two mode-derived
   offsets in s6/s7; the block-local bounds base stays live in fp across callbacks.
   This hold set reproduces the retail 0x38 frame and ra,fp,s7..s0 save contract. */
