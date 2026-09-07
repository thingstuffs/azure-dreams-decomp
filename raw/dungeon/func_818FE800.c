/* cfail-repair: tf7-phase1-cache-v3 */
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

typedef struct Target {
    u8 pad0[3];
    u8 field3;
    u8 pad4[0x22];
    u8 field26;
} Target;

extern s32 func_800990FC(void);
extern s32 func_80099194(M2C_UNK *, s32);
extern s32 func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(Target *, s32);
extern s32 func_80099844(Target *, M2C_UNK *);
extern s32 func_8009D218(Target *, s32);
extern s32 func_800A5720(s32);
extern s32 func_800A6D30(void);
extern s32 func_800B4C7C(s32, Target *, s32, s32);
extern M2C_UNK D_800E2096;
extern M2C_UNK D_800E20BC;

#ifdef __mips__
extern void func_80024F10(void);
extern void func_80024658(void);
extern void func_80024674(void);
extern void func_8002469C(void);
extern void func_80025030(void);
extern void func_800250A4(void);
extern void func_8002536C(void);
extern void func_8002561C(void);
extern void func_80025BB0(void);
extern void func_80025CDC(void);
extern void func_80025D20(void);
extern void func_80025DF4(void);
extern void func_80025D90(void);

static void (*const func_80024000_bank[])(void)
    __attribute__((section(".text.func_80024000"))) = {
    func_80024F10, 0, func_80024658, func_80024658,
    func_80024658, func_80024674, func_80024658, func_80024658,
    func_80024658, func_8002469C,
};

static const u32 func_80024000_data[]
    __attribute__((section(".text.func_80024000"))) = {
    0x01000340, 0x00540060, 0x01540340, 0x00040004,
    0x00000020, 0x00200020, 0x00200000, 0x0020FFE0,
    0x0000FFE0, 0xFFE0FFE0, 0xFFE00000, 0xFFE00020,
};

static void (*const func_80024000_bank2[])(void)
    __attribute__((section(".text.func_80024000"))) = {
    func_80025030, func_800250A4, func_8002536C,
    func_8002561C, func_80025BB0, func_80025CDC,
    func_80025D20, func_80025DF4, func_80025D90,
};
#endif

s32 func_80024000(Target *arg0, s32 arg1) {
    s32 random;
    s32 value;
    s32 aux;
    s32 half;
    s32 counter;
    s32 arg1_low;

    if (func_8009D218(arg0, 1) != 0) {
        return;
    }
    random = func_800A6D30() & 0xFFFF;
    if (arg0->field3 != 0) {
        counter = random % arg0->field3;
    } else {
        counter = 0;
    }
    arg1_low = arg1 & 0xFF;
    if (counter < (arg1_low << 5) || arg1_low == 0xFF) {
        if (arg0->field26 >= 2) {
            half = ((s32)arg0->field26 + 1) >> 1;
            arg0->field26 -= half;
            value = func_800990FC();
            aux = value;
            value = func_8009929C(8, aux);
            value = func_80099734(arg0, value);
            value = func_80099194(&D_800E2096, value);
            func_80099290(value);
            func_800A5720(aux);
            func_800B4C7C(0x53, arg0, half, 1);
            return;
        }
    }
    func_80099844(arg0, &D_800E20BC);
    func_800B4C7C(0x53, arg0, -1, 1);
}
