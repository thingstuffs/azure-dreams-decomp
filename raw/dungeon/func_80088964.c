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

struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern void *D_8008ACDC[];
extern s32 D_80083460[3];
extern volatile s16 D_80013714[8];
extern u8 D_800E3CD0[9];
extern u16 D_80082E76;
M2C_UNK func_8008E1E4();
M2C_UNK func_8008E250();
M2C_UNK func_800945E8();
M2C_UNK func_800948BC();
M2C_UNK func_80099844();
extern M2C_UNK D_800E0672;

void func_8008E0C4(void *arg0, void *unused, void *arg2, void *arg3) {
    void *global_base;
    void *counter_base;
    u16 temp_v0;
    s32 temp_v1;

    global_base = &D_80083160;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state_0;
        }
        func_8008E250(arg3, global_base);
        return;
    }
    ASM_KEEP(temp_v1);
    if (temp_v1 == 2) {
        return;
    }
    if (temp_v1 == 0x10) {
        goto state_16;
    }
    func_8008E250(arg3, global_base);
    return;

state_0:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        func_80099844(arg3, &D_800E0672);
        (void) M2C_FIELD(arg0, volatile u8 *, 0x9B);
        temp_v1 = 0x80;
        M2C_FIELD(arg0, u16 *, 0x96) = temp_v1;
        func_8008E1E4();
    }
    return;

state_1:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        return;
    }
    ASM_KEEP(temp_v1);
    if ((u16) *D_80013714 & 4) {
        if (M2C_FIELD(D_800E3CD0, u8 *, 0) == 0) {
            M2C_FIELD(D_800E3CD0, u8 *, 0) = temp_v1;
            func_80040AA0(3);
            func_8008E250();
        }
    } else {
        func_800945E8(arg0);
        func_800948BC();
        D_80082E76 = 0xC000;
        func_80041094(6, 0, 0, 0, 0xC000);
        M2C_FIELD(arg0, u8 *, 0x9B)++;
        func_8008E250();
    }
    return;

state_16:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        counter_base = D_80083460;
        M2C_FIELD(arg3, u8 *, 0x28) = M2C_FIELD(arg3, u8 *, 0x29);
        M2C_FIELD(arg3, s16 *, 0x2A) = 0x400 - ((M2C_FIELD(global_base, u16 *, 0xC8) + 0x100) & 0xE00);
        M2C_FIELD(arg0, void ***, 0x8C) = D_8008ACDC;
        M2C_FIELD(counter_base, u16 *, 0xA) = M2C_FIELD(counter_base, u16 *, 0xA) - 1;
    }
}
