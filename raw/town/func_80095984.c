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

M2C_UNK func_8009322C();                            /* extern */
M2C_UNK func_80093D48();     /* extern */
M2C_UNK func_80093ED8();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_80095094();                      /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_8009FF50();                                /* extern */
extern u8 D_80083160[];
extern u8 D_800CFCEF;
extern u8 D_800FE488[];

void func_800930E4(void *arg0, void *arg1, M2C_UNK arg2) {
    register void *self ASM_REG("$16");
    register void *target ASM_REG("$17");
    register M2C_UNK third ASM_REG("$18");
    s16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u8 *state;

    self = arg0;
    target = arg1;
    third = arg2;
    state = D_80083160;

    func_80095C80(target);
    ASM_KEEP(self);
    ASM_KEEP(target);
    ASM_KEEP(third);

    func_80095094(target);
    if (func_8009FF50() == 0) {
        temp_v0 = func_80095978(target, D_800FE488);
        if ((temp_v0 - M2C_FIELD(target, s16 *, 0xA)) >= 4) {
            if (M2C_FIELD(&D_800CFCEF, u8 *, 0) == 0) {
                func_80094378(self, target, third);
                func_8009322C();
                return;
            }
            goto block_7;
        }
        if (M2C_FIELD(&D_800CFCEF, u8 *, 0) == 0) {
            func_80095A94(target, temp_v0, D_800FE488);
        }
block_7:
        temp_v0_2 = M2C_FIELD(self, u16 *, 0xA) - 1;
        M2C_FIELD(self, u16 *, 0xA) = temp_v0_2;
        if ((s16) temp_v0_2 >= 0) {
            if (M2C_FIELD(state, s32 *, 8) & 0xF000) {
                func_80093ED8(self, target, third);
                func_8009322C();
                return;
            }
            if (M2C_FIELD(state, s32 *, 0x10) & 0x10) {
                func_800942B0(self, target, third);
                func_8009322C();
            }
        } else {
            goto block_15;
        }
    } else {
        temp_v0_3 = M2C_FIELD(self, u16 *, 0xA) - 1;
        M2C_FIELD(self, u16 *, 0xA) = temp_v0_3;
        if ((s16) temp_v0_3 < 0) {
block_15:
            func_80093D48(self, target, third);
        }
    }
}
/* MECHANISM: A 0x28 frame comes from pinned s0/s1/s2 argument holds plus
   D_80083160 held in s4; cdk materializes its address through v0.
   Signed halfword tests and one shared D_800CFCEF address fix the body.
   Moving ASM_KEEP after the first call lets sw s3 fill its jal delay slot. */
