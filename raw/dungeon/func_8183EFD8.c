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

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083498[];
extern u8 D_800DECF8[];
extern s32 D_800814A0[];
void func_80024A5C() __attribute__((noreturn)); /* extern */
void *func_8003FD64();                 /* extern */
s32 func_80069EF8();                          /* extern */
extern u8 D_80024688[];

void func_8183EFD8(void *arg0, void *arg1, void *arg2) {
    register void *r_arg0 ASM_REG("$19") = arg0;
    register s32 color ASM_REG("$4");
    s32 temp_v1_2;
    s32 temp_v0_3;
    s32 random;
    s32 var_s2;
    u8 temp_v0;
    u8 temp_v0_2;
    void *temp_s0;
    void *temp_v0_4;
    void *temp_v1;
    void *temp_v1_3;
    void *global_s6;

    ASM_KEEP_NV(r_arg0);
    temp_v1 = M2C_FIELD(r_arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x52) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x52) | 0x8000);
    temp_v1_2 = *(s16 *)((s8 *)r_arg0 + 0x4C);
    M2C_FIELD(r_arg0, u16 *, 0x48) = (u16) (M2C_FIELD(r_arg0, u16 *, 0x48) - 1);
    if (temp_v1_2 == 1) {
        goto case_1;
    }
    if (temp_v1_2 < 2) {
        if (temp_v1_2 == 0) {
            goto case_0;
        }
        func_80024A5C();
    }
    ASM_SCHED_BARRIER();
    var_s2 = 0x10;
    if (temp_v1_2 == 2) {
        goto case_2;
    }
    func_80024A5C();

case_0:
        func_800478B8(arg2);
        if ((u8) M2C_FIELD(arg2, u8 *, 0xC) < 0x81U) {
            temp_v0 = M2C_FIELD(arg2, u8 *, 0xE) + 0x20;
            M2C_FIELD(arg2, u8 *, 0xE) = temp_v0;
            M2C_FIELD(arg2, u8 *, 0xD) = temp_v0;
            M2C_FIELD(arg2, u8 *, 0xC) = temp_v0;
        }
        if ((s16) M2C_FIELD(r_arg0, u16 *, 0x48) <= 0) {
            M2C_FIELD(r_arg0, u16 *, 0x48) = 0x10U;
            M2C_FIELD(r_arg0, u16 *, 0x4C) = (u16) (M2C_FIELD(r_arg0, u16 *, 0x4C) + 1);
            func_80024A5C();
        }
        goto end;

case_1:
        temp_v0_3 = M2C_FIELD(arg1, s32 *, 0x14) + 0x8000;
        M2C_FIELD(arg1, s32 *, 0x14) = temp_v0_3;
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + temp_v0_3);
        var_s2 = 0x14;
        if ((s16) M2C_FIELD(r_arg0, u16 *, 0x48) <= 0) {
            global_s6 = D_80024688;
            M2C_FIELD(r_arg0, s16 *, 0x4C) = (s16) ((u16) M2C_FIELD(r_arg0, s16 *, 0x4C) + 1);
            do {
                temp_v0_4 = func_8003FD64(0x312, D_80083498);
                if (temp_v0_4 != NULL) {
                    M2C_FIELD(temp_v0_4, M2C_UNK **, 0x10) = global_s6;
                    temp_s0 = M2C_FIELD(temp_v0_4, void **, 0xC);
                    M2C_FIELD(M2C_FIELD(temp_v0_4, void **, 8), s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
                    M2C_FIELD(M2C_FIELD(temp_v0_4, void **, 8), s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
                    random = func_80069EF8();
                    {
                        void *child = M2C_FIELD(temp_v0_4, void **, 8);
                        M2C_FIELD(child, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + ((random & 0x1F) << 0x10));
                        random = func_80069EF8(child);
                    }
                    M2C_FIELD(M2C_FIELD(temp_v0_4, void **, 8), s32 *, 0xC) = (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    random = func_80069EF8();
                    color = 0x800000;
                    ASM_KEEP_NV(color);
                    M2C_FIELD(M2C_FIELD(temp_v0_4, void **, 8), s32 *, 0x10) = (s32) (((random & 0xFFF) - 0x7FF) << 8);
                    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
                    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
                    M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
                    M2C_FIELD(temp_s0, u8 **, 0) = D_800DECF8;
                    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
                    random = (s32) M2C_FIELD(D_800DECF8, s32 *, 4);
                    ASM_SCHED_BARRIER();
                    color |= 0x8080;
                    ASM_SCHED_BARRIER();
                    M2C_FIELD(temp_s0, s8 *, 4) = 0;
                    M2C_FIELD(temp_s0, s8 *, 5) = 0;
                    M2C_FIELD(temp_s0, s32 *, 0xC) = color;
                    M2C_FIELD(temp_s0, s32 *, 8) = random;
                    temp_v1_3 = temp_v0_4 + 0x20;
                    M2C_FIELD(temp_v1_3, s16 *, 0x48) = (s16) (func_80069EF8((void *)color) & 3);
                    M2C_FIELD(temp_v1_3, s16 *, 0x4A) = 0xC;
                    M2C_FIELD(temp_v1_3, s16 *, 0x4C) = 0;
                    M2C_FIELD(temp_v0_4, void **, 0x20) = (void *) M2C_FIELD(r_arg0, void **, 0);
                }
                var_s2 -= 1;
            } while (var_s2 >= 0);
            func_80024A5C();
        }
        goto end;

case_2:
        if (var_s2 >= (s32) M2C_FIELD(arg2, u8 *, 0xC)) {
            M2C_FIELD(arg2, s32 *, 0xC) = 0;
            M2C_FIELD(r_arg0, u16 *, -2) = (u16) (M2C_FIELD(r_arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] |= 0x8000;
            func_80024A5C();
        }
        temp_v0_2 = M2C_FIELD(arg2, u8 *, 0xE) - 0x10;
        M2C_FIELD(arg2, u8 *, 0xE) = temp_v0_2;
        M2C_FIELD(arg2, u8 *, 0xD) = temp_v0_2;
        M2C_FIELD(arg2, u8 *, 0xC) = temp_v0_2;

end:
    return;
}
