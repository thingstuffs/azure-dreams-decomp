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

M2C_UNK func_80035208();                         /* extern */
M2C_UNK func_8008B158();                         /* extern */
M2C_UNK func_80092A30();                            /* extern */
M2C_UNK func_80092A60();                            /* extern */
M2C_UNK func_80093D38();     /* extern */
M2C_UNK func_8009455C();     /* extern */
M2C_UNK func_800945B8();     /* extern */
M2C_UNK func_80094660();     /* extern */
M2C_UNK func_800946A0();     /* extern */
M2C_UNK func_80094774();     /* extern */
s32 func_80094B0C();                          /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
M2C_UNK func_8009550C();                      /* extern */
M2C_UNK func_8009567C();                   /* extern */
s32 func_80095760();                       /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_800988C8();     /* extern */
M2C_UNK func_80099754();                      /* extern */
s32 func_8009FF50();                                /* extern */
s32 func_800A9D74();                     /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_80093B00;
extern M2C_UNK D_8009B828;
extern M2C_UNK D_8009B8E8;
extern M2C_UNK D_8009B9BC;
extern M2C_UNK D_800CFCB4;
extern void *D_800CFCC4;
extern u8 D_800CFCEF[];
extern M2C_UNK D_800FE488;
extern s32 D_800FE518[];
extern s32 *D_800FE5D8;

void func_800927EC(void *arg0, void *arg1, M2C_UNK arg2) {
    u8 *state = D_80083160;
    M2C_UNK *var_v0;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80095094(arg1);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if ((temp_v0 - M2C_FIELD(arg1, s16 *, 0xA)) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094660(arg0, arg1, arg2);
            func_80092A60();
            return;
        }
        goto block_6;
    }
    if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
    }
block_6:
    if (M2C_FIELD(state, s32 *, 0x10) & 0x10) {
        func_800945B8(arg0, arg1, arg2);
        func_80092A60();
        return;
    }
    if (M2C_FIELD(state, s32 *, 0x10) & 0x80) {
        if ((D_800CFCC4 != NULL) && (M2C_FIELD(D_800CFCC4, u8 *, 0x14) == 4)) {
            func_8009550C(arg1);
            func_80094774(arg0, arg1, arg2);
            D_800FE518[0] = 1;
            func_80092A60();
            return;
        }
        func_80099754(arg1);
        func_8009550C(arg1);
        if (func_80094B0C(arg0 - 0x20) != 0) {
            register u32 page ASM_REG("$3");

            func_80093D38(arg0, arg1, arg2);
            page = 0x80100000;
            ASM_PAGEBASE_PIN(page);
            func_80092A30();
        }
    } else {
        if (M2C_FIELD(state, s32 *, 0x10) & 0x40) {
            func_800946A0(arg0, arg1, arg2);
            func_80092A60();
            return;
        }
        if ((func_80095760(&D_800CFCB4) == -1) && (func_8009FF50() == 0)) {
            func_8009567C(&D_800CFCB4);
            func_80094C1C(arg0);
            func_800988C8(arg0, arg1, arg2);
            temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x2C), s32 *, 0x50);
            if ((temp_v1 != &D_8009B828) && (temp_v1 != &D_8009B8E8)) {
                if (temp_v1 != &D_8009B9BC) {
                    M2C_FIELD(arg0, void **, 0x2C) = NULL;
                }
            }
            var_v0 = &D_800CFCB4;
            temp_v0_2 = func_800A9D74(M2C_FIELD(var_v0, s32 *, 0x10), M2C_FIELD(arg0, void **, 0x2C));
            if (temp_v0_2 != 0) {
                register u32 page ASM_REG("$3");

                func_80035208(temp_v0_2);
                page = 0x80100000;
                ASM_PAGEBASE_PIN(page);
                func_80092A30();
                return;
            }
            func_8008B158(M2C_FIELD(var_v0, s32 *, 0x10));
            D_800FE5D8 = &D_80093B00;
            func_80092A60();
            return;
        }
        if (M2C_FIELD(state, s32 *, 8) & 0xF000) {
            func_8009455C(arg0, arg1, arg2);
        }
    }
}
