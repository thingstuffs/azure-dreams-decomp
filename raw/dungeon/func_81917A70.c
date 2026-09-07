#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

typedef struct Copy24 {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 word14;
} Copy24;

extern s32 D_800DEB70;
extern u8 D_80045340[];

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80025094;

s32 func_80025270(void *arg0, Copy24 *arg1, s16 arg2) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1_2;
    s32 var_v0;
    void *temp_a0_2;
    register Copy24 *temp_v1 ASM_REG("$3");
    void *temp_v0;
    s16 arg2_hold;
    temp_v0 = func_8003FD64(0x212, (u8 *)arg0 - 0x20);
    if (temp_v0 != NULL) {
        arg2_hold = arg2;
        temp_a0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80025094;
        M2C_FIELD(temp_v0, s32 *, 0x20) = (s32)arg0;
        M2C_FIELD(temp_a0_2, s16 *, 8) = (s16) (arg2_hold * 7);
        M2C_FIELD(temp_a0_2, s16 *, 4) = 0;
        M2C_FIELD(temp_a0_2, s16 *, 6) = 0;
        M2C_FIELD(temp_a0_2, s16 *, 0xA) = 0;
        M2C_FIELD(temp_a0_2, s16 *, 0xC) = (s16) (arg2_hold * 0x600);
        M2C_FIELD(temp_a0_2, s32 *, 0x20) = arg1->wordC;
        M2C_FIELD(temp_a0_2, s32 *, 0x24) = arg1->word10;
        M2C_FIELD(temp_a0_2, s32 *, 0x28) = arg1->word14;
        arg0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(arg0, s8 *, 0xE) = 0x20;
        M2C_FIELD(arg0, s8 *, 0xD) = 0x20;
        M2C_FIELD(arg0, s8 *, 0xC) = 0x20;
        M2C_FIELD(arg0, s16 *, 0x12) = 0x7DCF;
        M2C_FIELD(arg0, u16 *, 0x14) = (u16) (M2C_FIELD(arg0, u16 *, 0x14) | 0xC);
        M2C_FIELD(arg0, u16 *, 0x10) = (u16) (M2C_FIELD(arg0, u16 *, 0x10) | 0x20);
        M2C_FIELD(arg0, u16 *, 0x14) = (u16) (M2C_FIELD(arg0, u16 *, 0x14) | 0x100);
        func_8003DB94(arg0, &D_800DEB70, 0);
        var_v0 = rand();
        temp_v1_2 = var_v0;
        if (temp_v1_2 < 0) {
            var_v0 = temp_v1_2 + 0xFFF;
        }
        M2C_FIELD(arg0, s16 *, 0x1A) = (s16) (temp_v1_2 - ((var_v0 >> 0xC) << 0xC));
        M2C_FIELD(arg0, s16 *, 0x1E) = 0x400;
        M2C_FIELD(arg0, s16 *, 0x1C) = 0x400;
        func_8004491C(temp_v0, D_80045340);
        temp_v1 = M2C_FIELD(temp_v0, Copy24 **, 8);
        *temp_v1 = *arg1;
        temp_a0 = M2C_FIELD(temp_v1, s32 *, 0);
        temp_a1 = M2C_FIELD(temp_v1, s32 *, 4);
        M2C_FIELD(temp_v1, s32 *, 0xC) = temp_a0;
        M2C_FIELD(temp_v1, s32 *, 0x10) = temp_a1;
        return (s32)temp_v0;
    }
    return 0;
}
