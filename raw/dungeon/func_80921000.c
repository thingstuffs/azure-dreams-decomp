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

typedef struct {
    s8 a;
    s8 b;
    s8 c;
    s8 d;
} ByteBuf;

typedef struct {
    u8 x;
    u8 y;
} CoordBuf;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_ERROR(desc) (0)

s32 func_80033BC0(s32);
void func_8003F80C(void *, s32, s32, s32);
s32 func_800A4E2C(u8 *, u8 *);
s32 func_800A7A38(void *);
void func_800A7A7C(u8, u8, s16, s32, void *);
s16 func_800BCB04(s32, s32, s16);
s32 func_800F61BC(s32, s32);
s32 func_800F6208(s32, s32);
extern u8 D_80081484[];
extern u8 D_800F6D48[];

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_80921000")
    __attribute__((section(".text.func_80921000"), aligned(4))) = {
    0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
    0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001,
};
__asm__(".globl func_80921000\n"
        ".size func_80921000, 444");
#define BODY_NAME func_80921020
#else
#define BODY_NAME func_80921000
#endif

void BODY_NAME(void *arg0) {
    ByteBuf sp18;
    CoordBuf sp20;
    s16 temp_s0;
    s16 temp_v0_3;
    s32 temp_v0_4;
    u16 temp_v0;
    u16 temp_v0_2;

    M2C_ERROR(/* Read from unset register $at */) << 0;
    temp_v0 = M2C_FIELD(arg0, u16 *, 2) - 1;
    M2C_FIELD(arg0, u16 *, 2) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, 2) = 1U;
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 6) + 8;
        M2C_FIELD(arg0, u16 *, 6) = temp_v0_2;
        if ((s16) temp_v0_2 >= 0x70) {
            M2C_FIELD(arg0, u16 *, 6) = 0U;
        }
        func_8003F80C(D_800F6D48 + ((s16) M2C_FIELD(arg0, u16 *, 6) * 4), 0x7380, 1, 2);
    }
    if ((func_80033BC0(0xA2) != 0) && ((func_800F61BC(6, 3) << 0x10) == 0) && ((func_800F6208(6, 3) << 0x10) == 0)) {
        u8 *mode;
        mode = D_80081484;
        if ((mode[0] != 3) || (mode[1] != 6)) {
            if (M2C_FIELD(arg0, s16 *, 8) == 0) {
                M2C_FIELD(arg0, s16 *, 8) = 0x40;
                goto block_11;
            }
            goto block_12;
        }
    }
block_11:
    if (M2C_FIELD(arg0, s16 *, 8) != 0) {
block_12:
        temp_v0_3 = (u16) M2C_FIELD(arg0, s16 *, 8) - 1;
        M2C_FIELD(arg0, s16 *, 8) = temp_v0_3;
        if ((temp_v0_3 << 0x10) == 0) {
            sp18.a = 3;
            sp18.b = 6;
            sp18.c = 0;
            sp18.d = 0;
            do {

            } while ((func_800A4E2C(&sp20.x, &sp20.y) << 0x10) < 0);
            temp_v0_4 = func_800BCB04((sp20.x << 6) | 0x20, (sp20.y << 6) | 0x20, -0x400);
            temp_s0 = temp_v0_4;
            func_800A7A7C(sp20.x, sp20.y, temp_s0, func_800A7A38(&sp18), &sp18);
        }
    }
}
