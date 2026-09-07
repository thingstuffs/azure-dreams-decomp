#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
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

extern u16 D_80027330[5];
extern s32 D_800814A0[3];
M2C_UNK func_800269AC() __attribute__((noreturn));
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_80065320();
M2C_UNK func_80065820();
s32 rand();
extern u16 D_800273BC[5];

M2C_UNK func_81960CD4(void *arg0, void *arg1, void *arg2) {
    u8 *scratch = (u8 *)0x1F800000;
    u16 sp10[3];
    s16 temp_a1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_lo;
    u16 temp_a0;
    u16 temp_v0_4;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u16 counter;
    u16 temp_v1_6;

    M2C_FIELD(scratch, u16 *, 0x70) = M2C_FIELD(arg0, u16 *, 0x10) - M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(scratch, u16 *, 0x78) = M2C_FIELD(arg0, u16 *, 0x18) - M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(scratch, u16 *, 0x80) = M2C_FIELD(arg0, u16 *, 0x20) - M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(scratch, u16 *, 0x88) = M2C_FIELD(arg0, u16 *, 0x28) - M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(scratch, u16 *, 0x72) = M2C_FIELD(arg0, u16 *, 0x12) - M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(scratch, u16 *, 0x7A) = M2C_FIELD(arg0, u16 *, 0x1A) - M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(scratch, u16 *, 0x82) = M2C_FIELD(arg0, u16 *, 0x22) - M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(scratch, u16 *, 0x8A) = M2C_FIELD(arg0, u16 *, 0x2A) - M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(scratch, u16 *, 0x74) = M2C_FIELD(arg0, u16 *, 0x14) - M2C_FIELD(arg1, u16 *, 0xA);
    M2C_FIELD(scratch, u16 *, 0x7C) = M2C_FIELD(arg0, u16 *, 0x1C) - M2C_FIELD(arg1, u16 *, 0xA);
    counter = D_80027330[0];
    temp_v1_6 = M2C_FIELD(arg0, u16 *, 0x24);
    temp_a0 = M2C_FIELD(arg1, u16 *, 0xA);
    D_80027330[0] = (u16)(counter + 1);
    M2C_FIELD(scratch, u16 *, 0x84) = temp_v1_6 - temp_a0;
    M2C_FIELD(scratch, u16 *, 0x8C) = M2C_FIELD(arg0, u16 *, 0x2C) - M2C_FIELD(arg1, u16 *, 0xA);
    func_800649A0(temp_a0);
    sp10[0] = M2C_FIELD(arg2, u16 *, 0x16);
    sp10[1] = M2C_FIELD(arg2, u16 *, 0x18);
    sp10[2] = 0;
    M2C_FIELD(scratch, u32 *, 0x30) = M2C_FIELD(arg2, u16 *, 0x1C);
    M2C_FIELD(scratch, u32 *, 0x34) = M2C_FIELD(arg2, u16 *, 0x1E);
    M2C_FIELD(scratch, u32 *, 0x38) = 0x1000;
    M2C_FIELD(scratch, u32 *, 0x6C) = 0;
    M2C_FIELD(scratch, u32 *, 0x68) = 0;
    M2C_FIELD(scratch, u32 *, 0x64) = 0;
    func_80065820(sp10, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);
    func_80065320(scratch + 0x70, scratch + 0x98, scratch + 0x94);
    func_80065320(scratch + 0x78, scratch + 0xA0, scratch + 0x94);
    func_80065320(scratch + 0x80, scratch + 0xA8, scratch + 0x94);
    func_80065320(scratch + 0x88, scratch + 0xB0, scratch + 0x94);
    func_80064A40();
    M2C_FIELD(arg1, s32 *, 0) = (s32)(M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32)(M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32)(M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    M2C_FIELD(arg0, u16 *, 0x10) = (u16)(M2C_FIELD(scratch, u16 *, 0x98) + M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, u16 *, 0x18) = (u16)(M2C_FIELD(scratch, u16 *, 0xA0) + M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, u16 *, 0x20) = (u16)(M2C_FIELD(scratch, u16 *, 0xA8) + M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, u16 *, 0x28) = (u16)(M2C_FIELD(scratch, u16 *, 0xB0) + M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, u16 *, 0x12) = (u16)(M2C_FIELD(scratch, u16 *, 0x9A) + M2C_FIELD(arg1, u16 *, 6));
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16)(M2C_FIELD(scratch, u16 *, 0xA2) + M2C_FIELD(arg1, u16 *, 6));
    M2C_FIELD(arg0, u16 *, 0x22) = (u16)(M2C_FIELD(scratch, u16 *, 0xAA) + M2C_FIELD(arg1, u16 *, 6));
    M2C_FIELD(arg0, u16 *, 0x2A) = (u16)(M2C_FIELD(scratch, u16 *, 0xB2) + M2C_FIELD(arg1, u16 *, 6));
    M2C_FIELD(arg0, u16 *, 0x14) = (u16)(M2C_FIELD(scratch, u16 *, 0x9C) + M2C_FIELD(arg1, u16 *, 0xA));
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16)(M2C_FIELD(scratch, u16 *, 0xA4) + M2C_FIELD(arg1, u16 *, 0xA));
    M2C_FIELD(arg0, u16 *, 0x24) = (u16)(M2C_FIELD(scratch, u16 *, 0xAC) + M2C_FIELD(arg1, u16 *, 0xA));
    M2C_FIELD(arg0, u16 *, 0x2C) = (u16)(M2C_FIELD(scratch, u16 *, 0xB4) + M2C_FIELD(arg1, u16 *, 0xA));
    if (M2C_FIELD(arg0, s16 *, 0x48) == 0) {
        temp_v1 = M2C_FIELD(arg2, u8 *, 0xC);
        M2C_FIELD(arg2, u8 *, 0xC) = (u8)(temp_v1 + ((s32)(0xC0 - temp_v1) / (s16)M2C_FIELD(arg0, s16 *, 0x4C)));
        temp_v1_2 = M2C_FIELD(arg2, u8 *, 0xD);
        temp_a1 = M2C_FIELD(arg0, s16 *, 0x4C);
        temp_v0 = M2C_FIELD(arg2, u8 *, 0xE);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8)(temp_v1_2 + ((s32)(0xC0 - temp_v1_2) / temp_a1));
        temp_lo = (s32)(0xC0 - temp_v0) / (s16)M2C_FIELD(arg0, s16 *, 0x4C);
        M2C_FIELD(arg2, u8 *, 0xE) = (u8)(temp_v0 + temp_lo);
        temp_v0_2 = (u16)M2C_FIELD(arg0, s16 *, 0x4C) - 1;
        M2C_FIELD(arg0, s16 *, 0x4C) = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            M2C_FIELD(arg1, s32 *, 0xC) = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            M2C_FIELD(arg1, s32 *, 0x10) = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            M2C_FIELD(arg1, s32 *, 0x14) = (s32)(((rand() & 0x3F) - 0x20) << 0x10);
            M2C_FIELD(arg2, u16 *, 0x16) = (u16)((rand() & 0x3FF) - 0x200);
            M2C_FIELD(arg2, u16 *, 0x18) = (u16)((rand() & 0x3FF) - 0x200);
            M2C_FIELD(arg0, s16 *, 0x4C) = 0x10;
            M2C_FIELD(arg0, u16 *, 0x48) = (u16)(M2C_FIELD(arg0, u16 *, 0x48) + 1);
            return func_800269AC();
        }
    } else {
        temp_v1_3 = M2C_FIELD(arg2, u8 *, 0xC);
        M2C_FIELD(arg2, u8 *, 0xC) = (u8)(temp_v1_3 - ((s32)temp_v1_3 / (s16)M2C_FIELD(arg0, s16 *, 0x4C)));
        temp_v1_4 = M2C_FIELD(arg2, u8 *, 0xD);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8)(temp_v1_4 - ((s32)temp_v1_4 / (s16)M2C_FIELD(arg0, s16 *, 0x4C)));
        temp_v1_5 = M2C_FIELD(arg2, u8 *, 0xE);
        M2C_FIELD(arg2, u8 *, 0xE) = (u8)(temp_v1_5 - ((s32)temp_v1_5 / (s16)M2C_FIELD(arg0, s16 *, 0x4C)));
        temp_v0_3 = (u16)M2C_FIELD(arg0, s16 *, 0x4C) - 1;
        M2C_FIELD(arg0, s16 *, 0x4C) = temp_v0_3;
        if ((temp_v0_3 << 0x10) <= 0) {
            temp_a1 = *(s16 *)D_800273BC;
            if (temp_a1 != 0) {
                temp_v0_4 = D_800273BC[0] - 1;
                (*(u16 *)D_800273BC) = temp_v0_4;
                if ((s16)temp_v0_4 == 1) {
                    (*(u16 *)D_800273BC) = 0U;
                }
            }
            M2C_FIELD(arg0, u16 *, -2) = (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }
}
