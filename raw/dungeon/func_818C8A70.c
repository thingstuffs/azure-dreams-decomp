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
extern s16 D_80024D04;
extern u8 D_80045340[];
extern u8 D_800DE870[9];
extern s32 D_800814A0[3];
extern u8 D_800DEC00[];
void func_80024414(void) __attribute__((noreturn));                            /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8();                                /* extern */
s32 func_8009D218();            /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800C8CD8();        /* extern */
extern M2C_UNK D_80024024;
extern M2C_UNK D_80024124;
extern u8 D_800E3D68;

void func_818C8A70(void *arg0, void *arg1) {
    M2C_UNK var_a1;
    s16 temp_v1;
    s32 temp_a2;
    s32 temp_random;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_6;
    void *temp_s0;
    void *temp_s2;
    register void *temp_s4 ASM_REG("$20");
    void *temp_s7;
    void *temp_v0;

    D_80024D04 = 1;
    temp_s7 = M2C_FIELD(arg0, void **, 0x2C);
    if (M2C_FIELD(arg0, s16 *, 0) == 0) {
        temp_v0 = func_8003FC64(0x212);
        temp_s4 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            M2C_FIELD(temp_s4, s16 *, 2) = 0x1A;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024124;
            func_8004491C(temp_v0, D_80045340);
            temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
            M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
            temp_s2 = M2C_FIELD(temp_v0, void **, 8);
            temp_random = func_80069EF8();
            temp_v1 = M2C_FIELD(arg1, u16 *, 2);
            temp_v1 -= 8;
            temp_v1 += temp_random & 0xF;
            M2C_FIELD(temp_s2, s16 *, 2) = temp_v1;
            temp_random = func_80069EF8();
            temp_v1 = M2C_FIELD(arg1, u16 *, 6);
            temp_v1 -= 8;
            temp_v1 += temp_random & 0xF;
            M2C_FIELD(temp_s2, s16 *, 6) = temp_v1;
            temp_random = func_80069EF8();
            temp_v1 = M2C_FIELD(arg1, u16 *, 0xA);
            temp_v1 -= 4;
            temp_v1 += temp_random & 7;
            M2C_FIELD(temp_s2, s16 *, 0xA) = temp_v1;
            M2C_FIELD(temp_s4, s32 *, 0x60) = (s32) (func_80069EF8() + 0xFFFE0000);
            temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
            M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
            M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
            M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DCF;
            M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
            func_8003DB94(temp_s0, D_800DE870, 0);
        }
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 2) - 1;
        M2C_FIELD(arg0, u16 *, 2) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            if (M2C_FIELD(arg0, s16 *, 8) != 0) {
                M2C_FIELD(arg0, s16 *, 0) = 1;
                M2C_FIELD(arg0, u16 *, 2) = 0U;
                func_800A56E0(0x300);
                func_80024414();
                return;
            }
            ASM_SCHED_BARRIER();
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            goto block_8;
        }
block_8:
        if ((func_800A4778(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA), M2C_FIELD(arg0, void **, 0x30)) << 0x10) == 0) {
            M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x58));
            M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x5C));
            M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x60));
            goto block_10;
        }
        goto block_25;
    }
block_10:
    temp_v1 = M2C_FIELD(arg0, s16 *, 0);
    if (temp_v1 == 1) {
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 2) + 1;
        M2C_FIELD(arg0, u16 *, 2) = temp_v0_3;
        if ((temp_v0_3 & 3) == temp_v1) {
            temp_v0 = func_8003FC64(0x212);
            temp_s4 = temp_v0 + 0x20;
            if (temp_v0 != NULL) {
                register s16 temp_z ASM_REG("$3");
                M2C_FIELD(temp_s4, s16 *, 2) = 0x1A;
                M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024124;
                func_8004491C(temp_v0, D_80045340);
                temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
                M2C_FIELD(temp_s0, s16 *, 0x10) = 0x60;
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
                temp_s2 = M2C_FIELD(temp_v0, void **, 8);
                temp_s0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), void **, -0x18);
                temp_random = func_80069EF8();
                temp_v1 = M2C_FIELD(temp_s0, u16 *, 2);
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                M2C_FIELD(temp_s2, s16 *, 2) = temp_v1;
                temp_random = func_80069EF8();
                temp_v1 = M2C_FIELD(temp_s0, u16 *, 6);
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                M2C_FIELD(temp_s2, s16 *, 6) = temp_v1;
                temp_random = func_80069EF8();
                temp_random &= 0x1F;
                temp_v1 = M2C_FIELD(temp_s0, u16 *, 0xA);
                temp_random += 0x10;
                temp_z = temp_v1 - temp_random;
                M2C_FIELD(temp_s2, s16 *, 0xA) = temp_z;
                M2C_FIELD(temp_s4, s32 *, 0x58) = (s32) (func_80069EF8() - 0x8000);
                M2C_FIELD(temp_s4, s32 *, 0x5C) = (s32) (func_80069EF8() - 0x8000);
                M2C_FIELD(temp_s4, s32 *, 0x60) = (s32) ((func_80069EF8() + 0xFFFC0000) * 2);
                temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
                M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
                M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
                M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
                M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
                M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
                M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DCF;
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
                func_8003DB94(temp_s0, D_800DE870, 0);
            }
        }
        if ((M2C_FIELD(arg0, u16 *, 2) & 3) == 2) {
            temp_v0 = func_8003FC64(0x212);
            temp_s4 = temp_v0 + 0x20;
            if (temp_v0 != NULL) {
                register s16 temp_z ASM_REG("$3");
                M2C_FIELD(temp_s4, s16 *, 2) = 0x14;
                M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024024;
                func_8004491C(temp_v0, D_80045340);
                temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
                M2C_FIELD(temp_s0, s16 *, 0x10) = 0;
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
                temp_s2 = M2C_FIELD(temp_v0, void **, 8);
                temp_s0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), void **, -0x18);
                temp_random = func_80069EF8();
                temp_v1 = M2C_FIELD(temp_s0, u16 *, 2);
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                M2C_FIELD(temp_s2, s16 *, 2) = temp_v1;
                temp_random = func_80069EF8();
                temp_v1 = M2C_FIELD(temp_s0, u16 *, 6);
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                M2C_FIELD(temp_s2, s16 *, 6) = temp_v1;
                temp_random = func_80069EF8();
                temp_random &= 0x3F;
                temp_v1 = M2C_FIELD(temp_s0, u16 *, 0xA);
                temp_random += 0x20;
                temp_z = temp_v1 - temp_random;
                M2C_FIELD(temp_s2, s16 *, 0xA) = temp_z;
                temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
                M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x800;
                M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x800;
                M2C_FIELD(temp_s4, s32 *, 0x60) = (s32) (func_80069EF8() + 0xFFFE0000);
                M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
                M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
                M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
                M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7DC0;
                M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
                func_8003DB94(temp_s0, D_800DEC00, 0);
            }
        }
        if ((s16) M2C_FIELD(arg0, u16 *, 2) >= 0x29) {
            M2C_FIELD(arg0, s16 *, 0) = 2;
            M2C_FIELD(arg0, u16 *, 2) = 0U;
            if (func_8009D218(M2C_FIELD(temp_s7, s32 *, 0x60), 1, temp_s7) == 0) {
                register s32 final_random ASM_REG("$2");
                u32 final_field;
                final_random = func_800A6D30();
                final_random &= 3;
                final_field = M2C_FIELD(arg0, u8 *, 0x15);
                ASM_SCHED_BARRIER();
                final_random += 2;
                final_field >>= 2;
                temp_a2 = final_field + final_random;
                var_a1 = 0x10;
                if (D_800E3D68 == 0xFF) {
                    var_a1 = 0xFF;
                }
                func_800C8CD8(M2C_FIELD(arg0, void **, 0x30), var_a1, temp_a2);
            }
        }
    }
    if (M2C_FIELD(arg0, s16 *, 0) == 2) {
        temp_v0_6 = M2C_FIELD(arg0, u16 *, 2) + 1;
        M2C_FIELD(arg0, u16 *, 2) = temp_v0_6;
        if ((s16) temp_v0_6 >= 0x15) {
block_25:
            M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }
}
