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

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;
typedef struct {
    Vec3s item[3];
} Vec3sTable;

extern Vec3sTable D_80170838;
extern Vec3sTable D_8017084C;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_80083228[5];
extern u8 D_80174AA4[];
extern u8 D_80083498[];
extern u8 D_80174AAC[];
extern u8 D_80170E94[];
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern void *D_80170860[];
s32 func_8003DE58();
void *func_8003FD64(s32, void *);
M2C_UNK func_8004491C();
s16 func_80066460();
s16 func_8006649C();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
extern M2C_UNK D_800DB618;
extern M2C_UNK D_800DB660;
extern u8 D_80174A8C;
extern u8 D_80174A94;

void func_801727B4(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    Vec3sTable sp10;
    Vec3sTable sp28;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    u32 formula_factor;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 case_left;
    s32 case_right;
    u16 temp_v0_3;
    u16 temp_v0_7;
    u8 temp_v1;
    u8 state_v;
    void *temp_a2;
    void *temp_s0;
    void *temp_v0_2;
    void *temp_v0_6;
    void *temp_v1_4;

    sp10 = D_80170838;
    sp28 = D_8017084C;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 6U) {
        goto block_50;
    }
    (void)jt_keep; goto *D_80170860[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u16 *, 0xA8) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0xAA) = (u16) M2C_FIELD(arg1, u16 *, 6);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_5;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    goto block_50;
block_5:
    temp_v0 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 9) & 7;
    temp_a0 = temp_v0 + 4;
    var_v1 = temp_a0;
    if (temp_a0 >= 0) {
        goto block_7;
    }
    var_v1 = temp_v0 + 0xB;
block_7:
    temp_v1_2 = temp_a0 - (var_v1 & 0x18);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s16) D_8006CCD8[temp_v1_2] * 0x30000);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s16) D_8006CCE8[temp_v1_2] * 0x30000);
    M2C_FIELD(arg2, u8 **, 0x2C) = &D_80174A8C;
    func_80047784(arg2, (&D_80174A8C)[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    goto increment_state_load;
jt_c1:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_50;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = &D_80174A94;
    func_80047784(arg2, (&D_80174A94)[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF40000;
    goto increment_state_load;
jt_c2:
    temp_v1_3 = M2C_FIELD(arg1, s32 *, 0x14) + 0x20000;
    M2C_FIELD(arg1, s32 *, 0x14) = temp_v1_3;
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + temp_v1_3);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_50;
    }
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (0 - M2C_FIELD(arg1, s32 *, 0xC)) >> 1);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (0 - M2C_FIELD(arg1, s32 *, 0x10)) >> 1);
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174AA4;
    func_80047784(arg2, D_80174AA4[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x96) = 7;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    goto block_50;
jt_c3:
    if (M2C_FIELD(arg2, s8 *, 4) >= 3) {
        goto block_20;
    }
    if (func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, arg0 + 0xAC, 0) != 0) {
        goto block_18;
    }
    M2C_FIELD(arg0, u16 *, 0xB0) = 0U;
    M2C_FIELD(arg0, u16 *, 0xAE) = 0U;
    M2C_FIELD(arg0, u16 *, 0xAC) = 0U;
block_18:
    M2C_FIELD(arg0, u16 *, 0xAC) = (u16) (M2C_FIELD(arg0, u16 *, 0xAC) + M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, u16 *, 0xAE) = (u16) (M2C_FIELD(arg0, u16 *, 0xAE) + M2C_FIELD(arg1, u16 *, 6));
    M2C_FIELD(arg0, u16 *, 0xB0) = (u16) (M2C_FIELD(arg0, u16 *, 0xB0) + M2C_FIELD(arg1, u16 *, 0xA));
    goto block_24;
block_20:
    temp_v0_2 = func_8003FD64(1, D_80083498);
    if (temp_v0_2 == NULL) {
        goto block_24;
    }
    M2C_FIELD(temp_v0_2, M2C_UNK **, 0x10) = &D_800DB618;
    func_8004491C(temp_v0_2, &D_800DB660);
    temp_s0 = temp_v0_2 + 0x20;
    M2C_FIELD(temp_s0, u16 *, 0x10) = (u16) M2C_FIELD(arg0, u16 *, 0xAC);
    M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) M2C_FIELD(arg0, u16 *, 0xAE);
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) M2C_FIELD(arg0, u16 *, 0xB0);
    temp_v0 = func_8003DE58(M2C_FIELD(arg2, s32 *, 8), arg2, arg0 + 0xAC, 0);
    if (temp_v0 == 0) {
        M2C_FIELD(arg0, u16 *, 0xB0) = 0U;
        M2C_FIELD(arg0, u16 *, 0xAE) = 0U;
        M2C_FIELD(arg0, u16 *, 0xAC) = 0U;
    }
    {
    s32 color_a;
    s32 color_b;
    s32 color_c;
    s32 effect_a0;
    s32 effect_a1;
    s32 effect_a2;

    color_a = 0x200020;
    color_b = 0xC0C0C0;
    effect_a0 = 0;
    effect_a1 = 1;
    effect_a2 = 0x2C0;
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xAC) + M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0xAC) = temp_v0_3;
    M2C_FIELD(temp_s0, u16 *, 8) = temp_v0_3;
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xAE) + M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 0xAE) = temp_v0_3;
    M2C_FIELD(temp_s0, u16 *, 0xA) = temp_v0_3;
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0xB0) + M2C_FIELD(arg1, u16 *, 0xA);
    M2C_FIELD(arg0, u16 *, 0xB0) = temp_v0_3;
    M2C_FIELD(temp_s0, u16 *, 0xC) = temp_v0_3;
    M2C_FIELD(temp_s0, u16 *, 0x2C) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
    M2C_FIELD(temp_s0, s16 *, 0x2E) = 0x10;
    M2C_FIELD(temp_s0, s16 *, 0x30) = 0x10;
    M2C_FIELD(temp_s0, s16 *, 0x36) = 0x10;
    M2C_FIELD(temp_s0, s32 *, 4) = color_a;
    M2C_FIELD(temp_s0, s32 *, 0x18) = color_b;
    formula_factor = 6 - M2C_FIELD(arg2, s8 *, 4);
    color_c = 0x141414;
    M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) ((formula_factor * 0x30303) + color_c);
    M2C_FIELD(temp_v0_2, Vec3s *, 0x40) = sp10.item[M2C_FIELD(arg2, s8 *, 4) - 3];
    M2C_FIELD(temp_v0_2, Vec3s *, 0x46) = sp28.item[M2C_FIELD(arg2, s8 *, 4) - 3];
    M2C_FIELD(temp_s0, s16 *, 0x32) = func_80066460(effect_a0, effect_a1, effect_a2, 0x100);
    M2C_FIELD(temp_s0, s16 *, 0x34) = func_8006649C(0, 0x1F8);
    }
block_24:
    temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_7;
    if ((temp_v0_7 << 0x10) == 0) {
        goto block_26;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_27;
    }
block_26:
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    func_800A56E0(0x808);
block_27:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_50;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174AAC;
    func_80047784(arg2, D_80174AAC[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    goto block_50;
jt_c4:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_50;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80174AAC;
    func_80047784(arg2, D_80174AAC[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_33;
    }
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
block_33:
increment_state_load:
    state_v = M2C_FIELD(arg0, u8 *, 0x9B);
increment_state:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (state_v + 1);
    goto block_50;
jt_c5:
    case_left = (s16) M2C_FIELD(arg1, u16 *, 2);
    case_right = (s16) M2C_FIELD(arg0, u16 *, 0xA8);
    case_left = case_left - case_right;
    if (case_left >= 0) {
        goto block_37;
    }
    case_left = 0 - case_left;
block_37:
    if (case_left >= 0x41) {
        goto block_41;
    }
    case_left = (s16) M2C_FIELD(arg1, u16 *, 6);
    case_right = (s16) M2C_FIELD(arg0, u16 *, 0xAA);
    case_left = case_left - case_right;
    if (case_left >= 0) {
        goto block_40;
    }
    case_left = 0 - case_left;
block_40:
    if (case_left < 0x41) {
        goto block_42;
    }
block_41:
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
block_42:
    if ((s16) M2C_FIELD(arg1, u16 *, 2) != (s16) M2C_FIELD(arg0, u16 *, 0xA8)) {
        goto block_50;
    }
    if ((s16) M2C_FIELD(arg1, u16 *, 6) != (s16) M2C_FIELD(arg0, u16 *, 0xAA)) {
        goto block_50;
    }
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    func_800AD594(arg3, 0x100);
    M2C_FIELD(arg0, u8 **, 0x8C) = D_80170E94;
    *D_8008346C = 0;
    func_800A4ACC(arg3);
    if (M2C_FIELD(arg3, s8 *, 0x6D) == 0) {
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    } else {
        *D_800E3DE8 = arg3 - 0x20;
    }
block_47:
    temp_a0_2 = M2C_FIELD(arg3, s32 *, 0x60);
    if (temp_a0_2 == 0) {
        goto block_50;
    }
    if (M2C_FIELD(arg3, s32 *, 0x14) & 0x20000) {
        goto block_50;
    }
    func_800C8EFC(temp_a0_2, 0x10);
block_50:
    return;
}
