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

s32 func_8008C180();                        /* extern */
s16 func_80094AA0();               /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_80095388();                 /* extern */
M2C_UNK func_800954F4();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
s32 func_800A5894();                          /* extern */
M2C_UNK func_800A596C();                            /* extern */
s32 func_800C1D44();                             /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80083780;
extern s32 D_800A5A98;
extern M2C_UNK D_800FE488;

void func_800A58CC(void *arg0, void *arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 shared_s0;
    s32 var_v0;
    s32 tail_v0;
    u16 temp_v0_3;
    u8 *town;
    u8 *coords;
    register u8 *flag_page ASM_REG("$2");

    shared_s0 = (s32) arg1;
    town = D_80083160;
    func_80095C80((void *) shared_s0);
    temp_v0 = func_80095978((void *) shared_s0, &D_800FE488);
    if (M2C_FIELD((void *) shared_s0, s16 *, 0xA) >= temp_v0) {
        register u32 dead_page ASM_REG("$2");
        func_80095A94((void *) shared_s0, temp_v0, &D_800FE488);
        dead_page = 0x80080000;
        ASM_PAGEBASE_PIN(dead_page);
        func_800A596C();
        return;
    }
    flag_page = (u8 *)0x800D0000;
    ASM_KEEP(flag_page);
    if (flag_page[-0x311] != 0) {
        register u32 dead_page ASM_REG("$2");
        M2C_FIELD((void *) shared_s0, s32 *, 0x14) = 0;
        func_800954F4((void *) shared_s0, temp_v0);
        dead_page = 0x80080000;
        ASM_PAGEBASE_PIN(dead_page);
        func_800A596C();
        return;
    }
    func_80095388((void *) shared_s0, temp_v0);
    coords = (u8 *)&D_80083780;
    if (func_800C1D44(func_8008C180(M2C_FIELD(coords, s16 *, 2), M2C_FIELD(coords, s16 *, 6)) & 0xFFFF) != 0) {
        M2C_FIELD((void *) shared_s0, s32 *, 0x14) = (s32) (M2C_FIELD((void *) shared_s0, s32 *, 0x14) - func_800A5894((void *) shared_s0));
    }
    func_80095094((void *) shared_s0);
    func_80095094((void *) shared_s0);
    shared_s0 = (M2C_FIELD(arg0, s16 *, 0x10) - 0x800) & 0xFFF;
    temp_v0_2 = func_80094AA0(M2C_FIELD(town, s16 *, 0xC8), shared_s0, 0x80);
    M2C_FIELD(town, s16 *, 0xC8) = temp_v0_2;
    ASM_SCHED_BARRIER();
    var_v0 = (temp_v0_2 & 0xFFF) - shared_s0;
    if (var_v0 < 0) {
        var_v0 = 0 - var_v0;
    }
    if (var_v0 < 0x80) {
        M2C_FIELD(town, s16 *, 0xC8) = shared_s0;
    }
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_3;
    ASM_SCHED_BARRIER();
    {
        register s32 sign_v0 ASM_REG("$2");
        register s32 count_a0 ASM_REG("$4");
        register s32 quotient_v1 ASM_REG("$3");
        sign_v0 = (s32) temp_v0_3 << 16;
        ASM_KEEP(sign_v0);
        count_a0 = sign_v0 >> 16;
        ASM_KEEP(count_a0);
        quotient_v1 = -0x2B0;
        if (count_a0 <= 0) {
            M2C_FIELD(arg0, s16 *, 0xA) = 0;
        }
        tail_v0 = count_a0 > 0
            ? (quotient_v1 = (quotient_v1 - M2C_FIELD(town, s16 *, 0xC4)) / count_a0,
               M2C_FIELD(town, u16 *, 0xC4) + quotient_v1)
            : -0x2B0;
        M2C_FIELD(town, s16 *, 0xC4) = tail_v0;
        ASM_KEEP(quotient_v1);
    }
    if ((M2C_FIELD(arg0, s16 *, 0xA) == 0) && (M2C_FIELD(town, s16 *, 0xC8) == shared_s0)) {
        M2C_FIELD(arg0, s16 *, 0xA) = 0;
        M2C_FIELD(arg0, void **, 0) = &D_800A5A98;
    }
}
