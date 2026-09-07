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

typedef struct Copy24 {
    s32 words[6];
} Copy24;

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

extern void func_80024ABC(void) __attribute__((noreturn));
extern void func_80024AC0() __attribute__((noreturn));
extern void func_80024AC8() __attribute__((noreturn));
extern void func_80024B8C(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(s32);                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_80069EF8();                                /* extern */
extern M2C_UNK D_800248C0;
extern M2C_UNK D_80025E04;
extern M2C_UNK D_80045340;

s32 func_818BD1C4(s32 *arg0, void *arg1, s16 arg2, s32 arg3) {
    s16 temp_a0;
    u16 tail_y;
    s32 temp_v1;
    s32 var_v0;
    register void *tail_a0 ASM_REG("$4");
    register u32 tail_page ASM_REG("$5");
    register s32 tail_result ASM_REG("$2");
    void *temp_a0_2;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;
    register s32 s3_arg ASM_REG("$19");

    s3_arg = arg3;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800248C0;
        M2C_FIELD(temp_v0, s32 *, 0x20) = (s32) *arg0;
        temp_v0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0_2, s16 *, 6) = 0;
        M2C_FIELD(temp_v0_2, s16 *, 8) = 0;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_a0 = arg2 % 3;
        if (temp_a0 == 1) {
            goto case_1;
        }
        if (temp_a0 >= 2) {
            goto check_2;
        }
        if (temp_a0 == 0) {
            goto case_0;
        }
        tail_a0 = temp_s0;
        tail_page = 0x80020000;
        ASM_KEEP(tail_a0);
        ASM_PAGEBASE_PIN(tail_page);
        func_80024AC8();

check_2:
        if (temp_a0 == 2) {
            goto case_2;
        }
        tail_a0 = temp_s0;
        tail_page = 0x80020000;
        ASM_PAGEBASE_PIN(tail_page);
        func_80024AC8();

case_0:
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0;
        func_80024AC0();

case_1:
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0;
        func_80024ABC();

case_2:
        tail_a0 = temp_s0;
        ASM_KEEP(tail_a0);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0;
        ASM_CLOBBER("$4");
        tail_a0 = temp_s0;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x10) | 0x60);
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        func_8003DB94(tail_a0, &D_80025E04, 0);
        var_v0 = func_80069EF8();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x2000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x2000;
        func_8004491C(temp_v0, &D_80045340);
        tail_a0 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(tail_a0, Copy24 *, 0) =
            M2C_FIELD(arg1, Copy24 *, 0);
        tail_y = M2C_FIELD(tail_a0, u16 *, 0xA);
        tail_result = (s32) temp_v0;
        tail_y -= s3_arg;
        ASM_KEEP(tail_result);
        M2C_FIELD(tail_a0, u16 *, 0xA) = tail_y;
        func_80024B8C();
    }
    return 0;
}
