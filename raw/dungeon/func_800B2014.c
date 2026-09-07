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

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Coord;

extern s32 D_80083460[3];
extern u8 *D_800E3D7C;
extern s32 D_800835E8[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern s32 D_800814A0;
M2C_UNK func_8003E188();
M2C_UNK func_80042640();
M2C_UNK func_800424E0();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_80099734();
M2C_UNK func_800997FC();
s32 func_8009B88C();
s32 *(*func_800A0B94())(M2C_UNK, s16, s16, s16);
s32 func_800A1618();
M2C_UNK func_800A1D4C();
s32 func_800A384C();
s32 func_800A3D18();
M2C_UNK func_800A48F0();
M2C_UNK func_800A5720();
M2C_UNK func_800A90E8();
void func_8009A180(s32 *, u8 *);
M2C_UNK func_800B7A30();
M2C_UNK func_800B7B18();
M2C_UNK func_800B7B40();
extern M2C_UNK D_800E0A42;
extern M2C_UNK D_800E0A56;
extern M2C_UNK D_800E0A6A;

void func_800B7774(void *arg0, Coord *arg1, void *arg2) {
    s16 sp18;
    s16 sp1A;
    s32 held_x;
    s32 held_y;
    u16 sp1C;
    s16 temp_v1;
    s32 *temp_v0;
    s32 *temp_v0_6;
    s32 temp_a1;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v1_2;
    s32 var_v1;
    u16 temp_v0_5;
    S_8003E2D8 *state_base;
    Coord *coord_arg = arg1;

    state_base = &D_80083160;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 != 0) {
            register void *null_arg ASM_REG("$4");
            null_arg = NULL;
            ASM_USE_NV(null_arg);
            func_800B7B18();
            return;
        }
        goto state_0;
    }
    if (temp_v1 == 2) {
        goto state_2;
    }
    func_800B7B18(state_base);
    return;

state_0:
    if ((func_8009B88C(0, (u16) coord_arg->x >> 6, (u16) coord_arg->y >> 6, &sp18, &sp1A) << 0x10) == 0) {
        {
        u8 *controls_base = (u8 *)&D_80083460;
        M2C_FIELD(controls_base, u16 *, 0xA) = (u16) (M2C_FIELD(controls_base, u16 *, 0xA) - 1);
        }
        func_800997FC(&D_800E0A42);
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
        func_800B7B40();
        return;
    }
    held_x = sp18;
    held_y = sp1A;
    temp_v0 = func_800A0B94(M2C_FIELD(arg0, u8 *, 0), func_800A1618(M2C_FIELD(arg0, u8 *, 0), 2), 1)(2, held_x, held_y, (s16) (coord_arg->z - 0x20));
    M2C_FIELD(arg0, s32 **, 4) = temp_v0;
    if (temp_v0 != NULL) {
        func_8003E188(M2C_FIELD(temp_v0, u8 *, 0x13), 0);
        func_800A90E8(arg0);
        func_80042640(temp_v0, M2C_FIELD(temp_v0, u8 *, 0x13));
        func_800424E0(temp_v0, M2C_FIELD(temp_v0, u8 *, 0x13), 0);
        M2C_FIELD(temp_v0, u8 *, 0x43) = 0xFE;
        func_800A48F0(temp_v0, 0x1B, 0);
        {
        register s32 clamp_value ASM_REG("$2");
        register s32 first_call_arg ASM_REG("$5");
        register s32 first_call_mode ASM_REG("$4");
        register s32 raw_first_result ASM_REG("$2");
        clamp_value = M2C_FIELD(D_800E3D7C, u8 *, 0x11) + 0x32;
        var_v1 = clamp_value;
        ASM_KEEP(clamp_value);
        if (clamp_value >= 0x64) {
            var_v1 = 0x63;
        }
        {
        s32 *scan_arg = D_800835E8;
        temp_v1_2 = D_800835E8[var_v1];
        M2C_FIELD(temp_v0, s32 *, 0x18) = temp_v1_2;
        if ((u32) temp_v1_2 >= (u32) D_800835E8[M2C_FIELD(temp_v0, u8 *, 0x11)]) {
            s32 *loop_base = D_800835E8;
            do {
                func_800A1D4C(temp_v0, 0);
            } while ((u32) loop_base[M2C_FIELD(temp_v0, u8 *, 0x11)] <= (u32) M2C_FIELD(temp_v0, s32 *, 0x18));
            scan_arg = temp_v0;
        }
        raw_first_result = func_800990FC(scan_arg);
        }
        first_call_mode = 8;
        ASM_KEEP(first_call_mode);
        first_call_arg = raw_first_result;
        ASM_KEEP(first_call_arg);
        temp_v0_3 = first_call_arg;
        func_80099290(func_80099194(&D_800E0A6A, func_8009929C(0xA, func_80099734(temp_v0, func_80099194(&D_800E0A56, func_8009929C(first_call_mode, first_call_arg))))));
        }
        func_800A5720(temp_v0_3);
        {
        register s32 *call_obj ASM_REG("$4");
        register u8 *call_state ASM_REG("$5");
        call_obj = temp_v0;
        ASM_KEEP(call_obj);
        call_state = D_800E3D7C;
        ASM_KEEP(call_state);
        M2C_FIELD(arg0, u16 *, 0xC) = 0x10U;
        func_8009A180(call_obj, call_state);
        }
        func_800B7A30();
        return;
    }
    goto block_30;

state_1:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0xC) - 1;
    M2C_FIELD(arg0, u16 *, 0xC) = temp_v0_5;
    if (((temp_v0_5 << 0x10) > 0) && !(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) && (M2C_FIELD(state_base, s32 *, 0x10) == 0)) {
        goto block_30;
    }
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) (M2C_FIELD(arg0, u16 *, 0xA) + 1);
    func_800B7B18(state_base);
    return;

state_2:
    temp_v0 = M2C_FIELD(arg0, s32 **, 4);
    if (M2C_FIELD(arg0, s16 *, 0xE) == 0) {
        M2C_FIELD(temp_v0, s32 *, 0x60) = func_800A3D18(M2C_FIELD(temp_v0, s32 *, -0x14), temp_v0, 2);
        {
        u8 *controls_base = (u8 *)&D_80083460;
        M2C_FIELD(controls_base, u16 *, 2) = (u16) (M2C_FIELD(controls_base, u16 *, 2) | 2);
        }
        temp_a1 = M2C_FIELD(temp_v0, s32 *, 0x60);
        M2C_FIELD(temp_v0, u16 *, 0x46) = 0x800C;
        if (temp_a1 != 0) {
            temp_v0_4 = func_800A384C(temp_v0, temp_a1, &sp1C, 1);
            M2C_FIELD(temp_v0, u16 *, 0x2A) = sp1C;
            if ((s16) temp_v0_4 >= 0) {
                M2C_FIELD(temp_v0, s16 *, 0x46) = (s16) (temp_v0_4 | 0x8000);
            }
        }
    }
    M2C_FIELD(D_800E3D7C, s32 *, 0x110) = 0;
    M2C_FIELD(temp_v0, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_v0, s32 *, 0x1C) | 0x400000);
    {
    u8 *controls_base = (u8 *)&D_80083460;
    M2C_FIELD(controls_base, u16 *, 0xA) = (u16) (M2C_FIELD(controls_base, u16 *, 0xA) - 1);
    }
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
block_30:
    ASM_USE_NV(coord_arg);
    temp_v0_6 = M2C_FIELD(arg0, s32 **, 4);
    if ((temp_v0_6 != NULL) && (M2C_FIELD(temp_v0_6, u16 *, -2) & 0x8000)) {
        M2C_FIELD(arg0, s16 *, 0xE) = 1;
    }
}
