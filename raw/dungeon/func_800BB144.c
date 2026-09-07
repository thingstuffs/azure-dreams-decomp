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

extern u8 *D_800E3D7C;
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80083460[3];
M2C_UNK func_8008D344();
M2C_UNK func_80098864();
M2C_UNK func_80098B38();
s32 func_8004A658();
s32 func_800998C0();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099368();
s32 func_80099734();
s32 func_80099978();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A6480();
s32 func_800A6D30();
M2C_UNK func_800A7A7C();
s32 func_800AD6FC();
extern M2C_UNK D_80089378;
extern M2C_UNK D_8008937C;
extern M2C_UNK D_800E13DA;
extern M2C_UNK D_800E13E9;

s32 func_800C08A4(u8 *arg0, u8 *arg1, s16 arg2, M2C_UNK arg3) {
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    u8 *temp_v0_7;
    s32 temp_s2;
    u8 *temp_s1;
    void *temp_s0;
    s32 temp_s0_2;

    temp_s1 = arg0;
    if (arg2 == 0xD) {
        if (M2C_FIELD(temp_s1, u8 *, 0x13) == 0x16) {
            if ((func_800A6D30() & 1) == 0) {
                goto main_path;
            }
        }
        return func_80098864(arg1, arg3);
    }
main_path:
    temp_v0_7 = D_800E3D7C;
    if (temp_s1 == temp_v0_7) {
        M2C_FIELD(temp_s1, u8 **, 0x110) = arg1;
        func_8008D344(temp_s1, D_80083780, D_80082E80, temp_s1);
        return 0;
    }
    temp_v0_7 = (u8 *) 0x9FFFFFFF;
    if ((u32) temp_s1 <= (u32) temp_v0_7) {
        if (M2C_FIELD(temp_s1, u8 *, 0x13) != 0x16) {
            func_800A6480(temp_s1, arg1);
            if (func_800AD6FC(temp_s1, (D_800DDE84[M2C_FIELD(temp_s1, u8 *, 0x13)] >> 4) & 3, 0) == 0) {
                func_800A5F38(temp_s1, arg1);
                return 1;
            }
            func_80098B38(arg1);
            goto decrement;
        }
        temp_s0 = M2C_FIELD(temp_s1, void **, -0x18);
        M2C_FIELD(temp_s1, u8 *, 0x4B) = (u8) (M2C_FIELD(temp_s1, u8 *, 0x4B) & 0xDF);
        func_800A7A7C((u16) M2C_FIELD(temp_s0, u16 *, 2) >> 6, (u16) M2C_FIELD(temp_s0, u16 *, 6) >> 6, M2C_FIELD(temp_s0, s16 *, 0xA), func_8004A658(M2C_FIELD(temp_s1, u8 *, 0x49), M2C_FIELD(temp_s1, u8 *, 0x48)), temp_s1 + 0x48);
        M2C_FIELD(temp_s1, u8 *, 0x48) = (u8) *arg1;
        M2C_FIELD(temp_s1, u8 *, 0x4B) = (u8) (M2C_FIELD(temp_s1, u8 *, 0x4B) | 0x20);
        temp_s2 = func_800990FC();
        temp_v0 = func_80099734(temp_s1, temp_s2);
        temp_v0_2 = func_80099194(&D_800E13DA, temp_v0);
        {
            register s32 node ASM_REG("$17");
            register s32 offset ASM_REG("$16");
            register s32 captured ASM_REG("$2");
            s32 result;

            node = func_80099978(temp_v0_2);
            ASM_KEEP_NV(node);
            captured = func_80099194(&D_80089378, node);
            offset = node - 2;
            ASM_KEEP_DEP_NV(offset, node);
            ASM_KEEP(captured);
            node = captured;
            result = func_80099368(arg1, node);
            {
                register s32 pass ASM_REG("$5");

                pass = node;
                node = result;
                ASM_KEEP(node);
                func_800998C0(offset, pass);
            }
            func_80099290(func_80099194(&D_8008937C, node));
        }
        func_800A5720(temp_s2);
        func_80098B38(arg1);
        goto decrement;
    }
    temp_s2 = func_800990FC();
    temp_v0_4 = func_80099734(temp_s1, temp_s2);
    temp_v0_5 = func_80099194(&D_800E13E9, temp_v0_4);
    {
        register s32 node ASM_REG("$17");
        register s32 offset ASM_REG("$16");
        register s32 captured ASM_REG("$2");
        s32 result;

        node = func_80099978(temp_v0_5);
        captured = func_80099194(&D_80089378, node);
        offset = node - 2;
        ASM_KEEP_DEP_NV(offset, node);
        ASM_KEEP(captured);
        node = captured;
        result = func_80099368(arg1, node);
        {
            register s32 pass ASM_REG("$5");

            pass = node;
            node = result;
            ASM_KEEP(node);
            func_800998C0(offset, pass);
        }
        func_80099290(func_80099194(&D_8008937C, node));
    }
    func_800A5720(temp_s2);
decrement:
    {
        u8 *counter_base = (u8 *) D_80083460;
        M2C_FIELD(counter_base, u16 *, 0xA) = (u16) (M2C_FIELD(counter_base, u16 *, 0xA) - 1);
    }
    return 1;
}
