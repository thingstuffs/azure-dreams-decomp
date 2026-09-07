#include "common.h"
#include "m2c_compat.h"

typedef struct { s32 a, b; } __attribute__((packed)) M2C_PACKED_PAIR;
typedef struct { s16 x, y, z; } M2C_VEC3S;

typedef struct { s32 sf; } M2C_S32F;
#define M2C_SFIELD(expr, offset) (((M2C_S32F *)((s8 *)(expr) + (offset)))->sf)
/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80024020[];
M2C_UNK func_8002470C();     /* extern */
M2C_UNK func_80024938();     /* extern */
M2C_UNK func_80024B2C();     /* extern */
M2C_UNK func_80026240();                 /* extern */
M2C_UNK func_800262F4();    /* extern */
M2C_UNK func_800263C0();                  /* extern */
void *func_80026444();        /* extern */
M2C_UNK func_80026694(); /* extern */
s32 func_8003DE58();  /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                /* extern */
s32 func_80069EF8();                              /* extern */
M2C_UNK func_8009CE1C(); /* extern */
s16 func_800A07D0();              /* extern */
M2C_UNK func_800A56E0();                /* extern */
M2C_UNK func_800B8D64();               /* extern */
extern M2C_UNK D_800269F8;
extern s16 D_80026B28;
extern u8 D_80026BC8[];
extern u8 D_80026BD4[];
extern s16 D_80027C94;
extern u8 D_80027C96;
extern s32 D_80027C98;
extern M2C_UNK D_800814A0;
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083780;
extern s32 D_800E3D18;
extern M2C_UNK D_800E3D7C;

void func_80024DAC(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16 };
    M2C_VEC3S sp20;
    s32 temp_s2;
    s32 angle_mask;
    s32 normalized_angle;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_9;
    s32 var_a0;
    s32 var_a2_2;
    s16 var_v0_22;
    s32 temp_a0;
    s32 temp_a1;
    register s32 temp_s0 ASM_REG("$16");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 temp_v0_11;
    register s32 temp_v0_8 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 divisor16;
    register s32 division_numerator ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 var_a3 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    s32 var_v0_10;
    s32 var_v0_12;
    s32 var_v0_13;
    s32 var_v0_15;
    s32 var_v0_17;
    s32 var_v0_18;
    s32 var_v0_20;
    s32 var_v0_21;
    s32 var_v0_2;
    s32 var_v0_3;
    register s32 var_v0_5 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_9;
    s32 temp_a0_3;
    u16 temp_a0_4;
    u16 temp_v0;
    u16 temp_v0_12;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_9;
    u16 temp_v1_3;
    u16 temp_v1_5;
    u16 temp_v1_7;
    u16 temp_v1_8;
    u16 var_v0;
    u16 var_v0_11;
    u16 var_v0_16;
    u16 var_v0_19;
    u16 var_v0_4;
    u16 var_v0_8;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_4;
    u8 temp_a0_2;
    u8 temp_v0_13;
    u8 temp_v1_12;
    u8 temp_v1_13;
    u8 temp_v1_14;
    u8 temp_v1_15;
    void **var_v0_14;
    void *temp_s0_4;
    void *temp_s1;
    void *temp_s3;
    void *temp_v0_10;
    void *temp_v0_4;
    register void *var_a2 ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
    void *var_s0;
    M2C_UNK *state0_move;
    void *state0_actor;
    void *state0_height_actor;
    register s32 state0_second ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 state0_delta_x;
    s32 state0_delta_y;
    register s32 update_v0 ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 update_v1 ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 update_a0;
    s32 update_a1;
    void *state1_global;
    s32 compare_v1;
    M2C_UNK *state1_move;
    void *state1_actor;
    void *state2_stage;
    register void *list_sentinel ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 tile_x;
    u16 tile_counter;
    u8 tile_y;
    s32 tile_div;
    M2C_UNK *state34_base;
    M2C_UNK *state34_move;
    M2C_UNK *state34_emit;
    void *state2_actor;
    u32 state2_angle;
    M2C_UNK *tile_base;
    u32 tile_coord;
    s32 tile_call_arg;
    s32 common_speed;
    register s32 common_pitch ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 state6_timer_signed;
    u16 state6_timer;
    u16 state6_next;
    u16 state6_height;
    s32 state6_spin_arg;
    register s32 state6_velocity ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
    s32 state6_target_base;
    s32 alternate_delta;
    s32 alternate_scale;
    u16 state0_c16;

    var_a3 = 0;
    var_a2 = arg0;
    (*(s16 *)&D_800269F8) = (s16) (M2C_FIELD(&D_800269F8, u16 *, 0) + 1);
loop_1:
    {
        s32 copy0;
        s32 copy1;

        copy0 = M2C_FIELD(var_a2, M2C_PACKED_PAIR *, 0x48).a;
        copy1 = M2C_FIELD(var_a2, M2C_PACKED_PAIR *, 0x48).b;
        M2C_FIELD(var_a2, M2C_PACKED_PAIR *, 0x50).a = copy0;
        M2C_FIELD(var_a2, M2C_PACKED_PAIR *, 0x50).b = copy1;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
    var_a3 -= 1;
    var_a2 -= 8;
    if (var_a3 >= 0) {
        goto loop_1;
    }
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x20);
    M2C_FIELD(arg0, u16 *, 0x48) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0x4A) = (u16) M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(arg0, u16 *, 0x4C) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    if (temp_v1 != 0) {
        goto block_138;
    }
    temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x30);
    if ((u32) temp_v1_2 >= 0x11U) {
        goto block_128;
    }
    (void)jt_keep; goto *D_80024020[(u32)(temp_v1_2)];
jt_c0:
    func_8003DE58(*(M2C_UNK *)((((s32) (D_80083228 + M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x2A) + 0x100) >> 7) & 0x1C) + D_800E3D18), &D_80082E80, arg0 + 0x28, 0);
    temp_s0 = func_80064584(M2C_FIELD((*(void **)&D_800E3D7C), s16 *, 0x2A));
    state0_second = func_80064584(M2C_FIELD((*(void **)&D_800E3D7C), s16 *, 0x2A) - 0x400);
    state0_move = &D_80083780;
    ASM_KEEP(state0_move);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0 >>= 4;
    state0_delta_x = M2C_FIELD(state0_move, u16 *, 2);
    state0_second >>= 4;
    state0_delta_x -= temp_s0;
    state0_delta_x += state0_second;
    update_v0 = M2C_FIELD(arg0, u16 *, 0x28);
    state0_actor = M2C_FIELD(&D_800E3D7C, void **, 0);
    update_v0 += state0_delta_x;
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) update_v0;
    temp_s0 = func_800644B8(M2C_FIELD(state0_actor, s16 *, 0x2A));
    state0_second = func_800644B8(M2C_FIELD((*(void **)&D_800E3D7C), s16 *, 0x2A) - 0x400);
    temp_s0 >>= 4;
    state0_second >>= 4;
    state0_delta_y = M2C_FIELD(state0_move, u16 *, 6);
    update_v1 = M2C_FIELD(arg0, u16 *, 0x2A);
    state0_delta_y -= temp_s0;
    state0_delta_y += state0_second;
    state0_height_actor = M2C_FIELD(&D_800E3D7C, void **, 0);
    update_v1 += state0_delta_y;
    M2C_FIELD(arg0, u16 *, 0x2A) = (u16) update_v1;
    update_v1 = M2C_FIELD(arg0, u16 *, 0x2C);
    update_a0 = M2C_FIELD(state0_height_actor, u16 *, 0x88);
    state0_c16 = 0x10U;
    M2C_FIELD(arg0, u16 *, 0x34) = state0_c16;
    update_v1 -= 0x50;
    update_a0 += update_v1;
    M2C_FIELD(arg0, u16 *, 0x2C) = (u16) update_a0;
    ASM_MEM_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    division_numerator = (M2C_FIELD(arg0, s16 *, 0x2C) - M2C_FIELD(arg1, s16 *, 0xA)) << 0x10;
    divisor16 = 16;
    ASM_KEEP(divisor16);   /* MATCH pin: keeps a constant in a register as retail does */
    M2C_FIELD(arg1, s32 *, 0x14) = division_numerator / divisor16;
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x30) + 1);
jt_c1:
    temp_s2 = func_800A07D0((s16) M2C_FIELD(arg1, u16 *, 2), (s16) M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg0, u16 *, 0x28), (s16) M2C_FIELD(arg0, u16 *, 0x2A));
    temp_v1_3 = M2C_FIELD(arg0, u16 *, 0x38);
    if (temp_v1_3 & 0x800) {
        var_v0 = temp_v1_3 | 0xF800;
    } else {
        var_v0 = temp_v1_3 & 0x7FF;
    }
block_8:
    M2C_FIELD(arg0, u16 *, 0x38) = var_v0;
    if (!(temp_s2 & 0x800)) {
        goto block_10;
    }
    angle_mask = ~0x7FF;
    normalized_angle = temp_s2 | angle_mask;
    goto block_11;
block_10:
    normalized_angle = temp_s2 & 0x7FF;
block_11:
    temp_s2 = normalized_angle;
    var_v0_2 = (s16) M2C_FIELD(arg0, u16 *, 0x38) - temp_s2;
    if (var_v0_2 >= 0) {
        goto block_13;
    }
    var_v0_2 = 0 - var_v0_2;
block_13:
    if (var_v0_2 < 0x801) {
        goto block_15;
    }
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) ((temp_s2 & ~0xFFF) | (M2C_FIELD(arg0, u16 *, 0x38) & 0xFFF));
block_15:
    temp_v1_4 = (s16) M2C_FIELD(arg0, u16 *, 0x38);
    var_v0_3 = temp_s2 - temp_v1_4;
    if (var_v0_3 >= 0) {
        goto block_17;
    }
    var_v0_3 = 0 - var_v0_3;
block_17:
    if (var_v0_3 < 0x81) {
        goto block_21;
    }
    if (M2C_FIELD(arg0, s16 *, 0x96) != 0) {
        var_v0_4 = temp_v1_4 + 0x80;
    } else {
        var_v0_4 = temp_v1_4 - 0x80;
    }
    M2C_FIELD(arg0, u16 *, 0x38) = var_v0_4;
    goto block_22;
block_21:
    M2C_FIELD(arg0, u16 *, 0x38) = temp_s2;
block_22:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x34) - 1;
    M2C_FIELD(arg0, u16 *, 0x34) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_24;
    }
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    M2C_FIELD(arg0, u16 *, 0x34) = 0U;
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
block_24:
    state1_global = M2C_FIELD(&D_800814A8, void **, 0);
    M2C_FIELD(state1_global, s16 *, 0x96) = 2;
    update_v0 = M2C_FIELD(arg1, s32 *, 0);
    update_v1 = M2C_FIELD(arg1, s32 *, 0xC);
    update_a0 = M2C_FIELD(arg1, s32 *, 0x10);
    update_a1 = M2C_FIELD(arg1, s32 *, 0x14);
    update_v0 += update_v1;
    M2C_FIELD(arg1, s32 *, 0) = update_v0;
    update_v0 = M2C_FIELD(arg1, s32 *, 4);
    update_v1 = M2C_FIELD(arg1, s32 *, 8);
    update_v0 += update_a0;
    M2C_FIELD(arg1, s32 *, 4) = update_v0;
    var_v0_5 = M2C_FIELD(arg1, s16 *, 2);
    update_v1 += update_a1;
    M2C_FIELD(arg1, s32 *, 8) = update_v1;
    var_v0_5 -= M2C_FIELD(arg0, s16 *, 0x28);
    if (__builtin_abs(var_v0_5) >= 0x40) {
        goto block_129;
    }
    var_v0_6 = M2C_FIELD(arg1, s16 *, 6);
    compare_v1 = M2C_FIELD(arg0, s16 *, 0x2A);
    var_v0_6 -= compare_v1;
    if (__builtin_abs(var_v0_6) >= 0x40) {
        goto block_129;
    }
    var_v0_7 = M2C_FIELD(arg1, s16 *, 0xA);
    compare_v1 = M2C_FIELD(arg0, s16 *, 0x2C);
    var_v0_7 -= compare_v1;
    if (__builtin_abs(var_v0_7) >= 0x40) {
        goto block_129;
    }
    func_8003DE58(*(M2C_UNK *)((((s32) (D_80083228 + M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x2A) + 0x100) >> 7) & 0x1C) + D_800E3D18), &D_80082E80, arg0 + 0x28, 0);
    state1_move = &D_80083780;
    update_v0 = M2C_FIELD(arg0, u16 *, 0x28);
    update_v1 = M2C_FIELD(state1_move, u16 *, 2);
    update_v0 += update_v1;
    M2C_FIELD(arg0, u16 *, 0x28) = update_v0;
    update_v0 = M2C_FIELD(arg0, u16 *, 0x2A);
    update_v1 = M2C_FIELD(state1_move, u16 *, 6);
    state1_actor = M2C_FIELD(&D_800814A8, void **, 0);
    update_v0 += update_v1;
    M2C_FIELD(arg0, u16 *, 0x2A) = update_v0;
    update_v1 = M2C_FIELD(arg0, u16 *, 0x2C);
    update_v0 = M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), u16 *, 0x88);
    update_v1 -= 0x50;
    update_v0 += update_v1;
    M2C_FIELD(arg0, u16 *, 0x2C) = update_v0;
    update_v0 = M2C_FIELD(state1_actor, u16 *, 0xA6) - 1;
    M2C_FIELD(state1_actor, u16 *, 0xA6) = update_v0;
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x30) + 1);
    goto block_128;
jt_c2:
    temp_s2 = func_800A07D0((s16) M2C_FIELD(arg1, u16 *, 2), (s16) M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg0, u16 *, 0x28), (s16) M2C_FIELD(arg0, u16 *, 0x2A));
    temp_v1_5 = M2C_FIELD(arg0, u16 *, 0x38);
    if (temp_v1_5 & 0x800) {
        var_v0_8 = temp_v1_5 | 0xF800;
    } else {
        var_v0_8 = temp_v1_5 & 0x7FF;
    }
block_36:
    M2C_FIELD(arg0, u16 *, 0x38) = var_v0_8;
    if (!(temp_s2 & 0x800)) {
        goto block_38;
    }
    angle_mask = ~0x7FF;
    normalized_angle = temp_s2 | angle_mask;
    goto block_39;
block_38:
    normalized_angle = temp_s2 & 0x7FF;
block_39:
    temp_s2 = normalized_angle;
    var_v0_9 = (s16) M2C_FIELD(arg0, u16 *, 0x38) - temp_s2;
    if (var_v0_9 >= 0) {
        goto block_41;
    }
    var_v0_9 = 0 - var_v0_9;
block_41:
    if (var_v0_9 < 0x801) {
        goto block_43;
    }
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) ((temp_s2 & ~0xFFF) | (M2C_FIELD(arg0, u16 *, 0x38) & 0xFFF));
block_43:
    temp_v1_6 = (s16) M2C_FIELD(arg0, u16 *, 0x38);
    var_v0_10 = temp_s2 - temp_v1_6;
    if (var_v0_10 >= 0) {
        goto block_45;
    }
    var_v0_10 = 0 - var_v0_10;
block_45:
    if (var_v0_10 < 0x81) {
        goto block_49;
    }
    if (M2C_FIELD(arg0, s16 *, 0x96) != 0) {
        var_v0_11 = temp_v1_6 + 0x80;
    } else {
        var_v0_11 = temp_v1_6 - 0x80;
    }
    M2C_FIELD(arg0, u16 *, 0x38) = var_v0_11;
    goto block_50;
block_49:
    M2C_FIELD(arg0, u16 *, 0x38) = temp_s2;
block_50:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x34) - 1;
    M2C_FIELD(arg0, u16 *, 0x34) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_52;
    }
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    M2C_FIELD(arg0, u16 *, 0x34) = 0U;
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
block_52:
    update_v0 = M2C_FIELD(arg1, s32 *, 0);
    update_v1 = M2C_FIELD(arg1, s32 *, 0xC);
    update_a0 = M2C_FIELD(arg1, s32 *, 0x10);
    update_a1 = M2C_FIELD(arg1, s32 *, 0x14);
    update_v0 += update_v1;
    M2C_FIELD(arg1, s32 *, 0) = update_v0;
    update_v0 = M2C_FIELD(arg1, s32 *, 4);
    update_v1 = M2C_FIELD(arg1, s32 *, 8);
    update_v0 += update_a0;
    update_v1 += update_a1;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    M2C_FIELD(arg1, s32 *, 4) = update_v0;
    state2_stage = M2C_FIELD(&D_800814A8, void **, 0);
    M2C_FIELD(arg1, s32 *, 8) = update_v1;
    M2C_FIELD(state2_stage, s16 *, 0x96) = 2;
    var_v0_12 = M2C_FIELD(arg1, s16 *, 2);
    compare_v1 = M2C_FIELD(arg0, s16 *, 0x28);
    var_v0_12 -= compare_v1;
    if (var_v0_12 >= 0) {
        goto block_54;
    }
    var_v0_12 = 0 - var_v0_12;
block_54:
    if (var_v0_12 >= 0x20) {
        goto block_128;
    }
    var_v0_13 = M2C_FIELD(arg1, s16 *, 6);
    compare_v1 = M2C_FIELD(arg0, s16 *, 0x2A);
    var_v0_13 -= compare_v1;
    if (var_v0_13 >= 0) {
        goto block_57;
    }
    var_v0_13 = 0 - var_v0_13;
block_57:
    if (var_v0_13 >= 0x20) {
        goto block_128;
    }
    M2C_FIELD(arg0, u16 *, 0x34) = 4U;
    state2_actor = M2C_FIELD(&D_800E3D7C, void **, 0);
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x30) + 1);
    M2C_FIELD(M2C_FIELD(&D_800814A8, void **, 0), s16 *, 0x96) = 0;
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) M2C_FIELD(state2_actor, s16 *, 0x2A);
    state2_angle = M2C_FIELD(state2_actor, u16 *, 0x2A);
    D_80026B28 = 0;
    M2C_FIELD(arg0, u16 *, 0x44) = (u16) ((state2_angle >> 9) & 7);
    goto block_128;
jt_c3:
jt_c4:
    state34_base = &D_80082E80;
    if (func_8003DE58(M2C_FIELD(state34_base, s32 *, 8), state34_base, &sp20, 0) == 0) {
        goto block_63;
    }
    if (M2C_FIELD(arg0, s16 *, 0x30) != 3) {
        goto block_62;
    }
    state34_move = &D_80083780;
    func_800B8D64(M2C_FIELD(state34_move, s16 *, 2) + sp20.x, M2C_FIELD(state34_move, s16 *, 6) + sp20.y, M2C_FIELD(state34_move, s16 *, 0xA) + sp20.z);
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x30) + 1);
block_62:
    state34_emit = &D_80083780;
    func_80024B2C((s16) (M2C_FIELD(state34_emit, u16 *, 2) + (u16) sp20.x), (s16) (M2C_FIELD(state34_emit, u16 *, 6) + (u16) sp20.y), (s16) (M2C_FIELD(state34_emit, u16 *, 0xA) + (u16) sp20.z), M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x2A), 0);
block_63:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s16 *, 0x16) = 0x16;
    temp_a1 = M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_SFIELD(arg1, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if ((s16) M2C_FIELD(arg1, u16 *, 0xA) <= M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x88)) {
        goto block_65;
    }
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x88);
block_65:
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x34) - 1;
    M2C_FIELD(arg0, u16 *, 0x34) = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_129;
    }
    tile_base = &D_80082E80;
    tile_coord = M2C_FIELD(tile_base, u8 *, 0x24);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    tile_call_arg = 0x300;
    ASM_KEEP(tile_call_arg);   /* MATCH pin: retail delay-slot fill depends on it */
    M2C_FIELD(arg0, s16 *, 0x40) = (s16) tile_coord;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    M2C_FIELD(arg0, u8 *, 0x98) = (u8) tile_coord;
    tile_coord = M2C_FIELD(tile_base, u8 *, 0x25);
    M2C_FIELD(arg0, s16 *, 0x30) = 5;
    M2C_FIELD(arg0, u16 *, 0x46) = 3U;
    M2C_FIELD(arg0, u16 *, 0x34) = 0U;
    M2C_FIELD(arg0, s16 *, 0x42) = (s16) tile_coord;
    M2C_FIELD(arg0, u8 *, 0x99) = (u8) tile_coord;
    func_800A56E0(tile_call_arg, temp_a1);
    goto block_129;
jt_c5:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    var_a2_2 = M2C_FIELD(arg1, s16 *, 2);
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    if (var_a2_2 >= 0) {
        goto block_69;
    }
    var_a2_2 += 0x3F;
block_69:
    tile_div = var_a2_2 >> 6;
    M2C_FIELD(arg0, s16 *, 0x40) = (s16) tile_div;
    var_a0 = M2C_FIELD(arg1, s16 *, 6);
    if (var_a0 >= 0) {
        goto block_71;
    }
    var_a0 += 0x3F;
block_71:
    temp_a0 = var_a0 >> 6;
    M2C_FIELD(arg0, s16 *, 0x42) = (s16) temp_a0;
    if (M2C_FIELD(arg0, u8 *, 0x98) != M2C_FIELD(arg0, s16 *, 0x40)) {
        goto block_73;
    }
    if (M2C_FIELD(arg0, u8 *, 0x99) == temp_a0) {
        goto block_129;
    }
block_73:
    var_s0 = M2C_FIELD(&D_800814A8, void **, 0);
    list_sentinel = var_s0;
    var_s0 = M2C_FIELD(var_s0, s32 *, 0x5C) + 0x20;
    if (var_s0 != list_sentinel) {
        do {
            temp_s1 = M2C_FIELD(var_s0, void **, -0x14);
            if ((M2C_FIELD(temp_s1, u8 *, 0x24) == M2C_FIELD(arg0, s16 *, 0x40)) &&
                (M2C_FIELD(temp_s1, u8 *, 0x25) == M2C_FIELD(arg0, s16 *, 0x42))) {
                var_v0_15 = M2C_FIELD(var_s0, s16 *, 0x88);
                compare_v1 = M2C_FIELD(arg1, s16 *, 0xA);
                var_v0_15 -= compare_v1;
                if (var_v0_15 < 0) {
                    var_v0_15 = -var_v0_15;
                }
                temp_s1 = var_s0 - 0x20;
                if ((var_v0_15 < 0x80) && !(M2C_FIELD(temp_s1, u16 *, 0x1E) & 0x2000)) {
                    func_8009CE1C(var_s0, 0xC, D_80027C96, 0xA, (s32) (s16) (M2C_FIELD(arg0, u16 *, 0x44) << 9), D_80027C98, 2);
                    temp_s3 = M2C_FIELD(var_s0, void **, -0x18);
                    func_80024938(M2C_FIELD(temp_s3, s16 *, 2), M2C_FIELD(temp_s3, s16 *, 6), M2C_FIELD(temp_s3, s16 *, 0xA), (s16) M2C_FIELD(arg0, u16 *, 0x38), (func_80069EF8() & 3) | 4);
                    M2C_FIELD(temp_s1, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x1E) | 0x2000);
                }
            }
            update_v1 = M2C_FIELD(var_s0, s32 *, 0x5C);
            var_s0 = update_v1 + 0x20;
        } while (var_s0 != M2C_FIELD(&D_800814A8, void **, 0));
    }
block_83:
    tile_x = (u8) M2C_FIELD(arg0, s16 *, 0x40);
    tile_counter = M2C_FIELD(arg0, u16 *, 0x46);
    tile_y = (u8) M2C_FIELD(arg0, s16 *, 0x42);
    tile_counter -= 1;
    M2C_FIELD(arg0, u16 *, 0x46) = tile_counter;
    M2C_FIELD(arg0, u8 *, 0x98) = tile_x;
    M2C_FIELD(arg0, u8 *, 0x99) = tile_y;
    if ((tile_counter << 0x10) > 0) {
        goto block_128;
    }
    M2C_FIELD(arg0, u16 *, 0x8A) = (u16) ((func_80069EF8() & 0x1F) + 0x10);
    M2C_FIELD(arg0, void **, 0x9C) = NULL;
    M2C_FIELD(arg0, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x30) + 1);
    goto block_128;
jt_c6:
    temp_v0_4 = M2C_FIELD(arg0, void **, 0x9C);
    if (temp_v0_4 == NULL) {
        goto block_117;
    }
    temp_s3 = M2C_FIELD(temp_v0_4, void **, -0x18);
    temp_s2 = func_800A07D0((s16) M2C_FIELD(arg1, u16 *, 2), (s16) M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(temp_s3, s16 *, 2), M2C_FIELD(temp_s3, s16 *, 6));
    temp_v1_8 = M2C_FIELD(arg0, u16 *, 0x38);
    if (temp_v1_8 & 0x800) {
        var_v0_16 = temp_v1_8 | 0xF800;
    } else {
        var_v0_16 = temp_v1_8 & 0x7FF;
    }
block_88:
    M2C_FIELD(arg0, u16 *, 0x38) = var_v0_16;
    if (!(temp_s2 & 0x800)) {
        goto block_90;
    }
    angle_mask = ~0x7FF;
    normalized_angle = temp_s2 | angle_mask;
    goto block_91;
block_90:
    normalized_angle = temp_s2 & 0x7FF;
block_91:
    temp_s2 = normalized_angle;
    var_v0_17 = (s16) M2C_FIELD(arg0, u16 *, 0x38) - temp_s2;
    if (var_v0_17 >= 0) {
        goto block_93;
    }
    var_v0_17 = 0 - var_v0_17;
block_93:
    if (var_v0_17 < 0x801) {
        goto block_95;
    }
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) ((temp_s2 & ~0xFFF) | (M2C_FIELD(arg0, u16 *, 0x38) & 0xFFF));
block_95:
    temp_v0_5 = M2C_FIELD(arg0, u16 *, 0x9A) - 1;
    M2C_FIELD(arg0, u16 *, 0x9A) = temp_v0_5;
    if ((temp_v0_5 << 0x10) > 0) {
        goto block_97;
    }
    M2C_FIELD(arg0, u16 *, 0x9A) = 0x1EU;
    M2C_FIELD(arg0, u16 *, 0x38) = temp_s2;
block_97:
    temp_v1_9 = (s16) M2C_FIELD(arg0, u16 *, 0x38);
    var_v0_18 = temp_s2 - temp_v1_9;
    if (var_v0_18 >= 0) {
        goto block_99;
    }
    var_v0_18 = 0 - var_v0_18;
block_99:
    if (var_v0_18 < 0x81) {
        goto block_103;
    }
    if (M2C_FIELD(arg0, s16 *, 0x96) != 0) {
        var_v0_19 = temp_v1_9 + 0x80;
    } else {
        var_v0_19 = temp_v1_9 - 0x80;
    }
    M2C_FIELD(arg0, u16 *, 0x38) = var_v0_19;
    goto block_104;
block_103:
    M2C_FIELD(arg0, u16 *, 0x38) = temp_s2;
block_104:
    state6_timer_signed = M2C_FIELD(arg0, s16 *, 0x34);

    state6_timer = M2C_FIELD(arg0, u16 *, 0x34);
    if (state6_timer_signed == 0) {
        goto block_107;
    }
    state6_next = state6_timer - 1;
    M2C_FIELD(arg0, u16 *, 0x34) = state6_next;
    if ((state6_next << 0x10) != 0) {
        goto block_108;
    }
    state6_height = M2C_FIELD(temp_s3, u16 *, 0xA);
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    state6_height -= 0x40;
    M2C_FIELD(arg1, u16 *, 0xA) = state6_height;
    M2C_FIELD(arg0, u16 *, 0x8A) = 0U;
    goto block_108;
block_107:
    temp_v0_7 = M2C_FIELD(arg0, u16 *, 0x8A) + 1;
    state6_spin_arg = (s32) (temp_v0_7 << 0x10);

    state6_spin_arg >>= 9;
    M2C_FIELD(arg0, u16 *, 0x8A) = temp_v0_7;
    M2C_FIELD(arg1, s16 *, 0x16) = (s16) (func_800644B8(state6_spin_arg) >> 9);
block_108:
    var_v0_20 = M2C_FIELD(arg1, s16 *, 2);
    compare_v1 = M2C_FIELD(temp_s3, s16 *, 2);
    var_v0_20 -= compare_v1;
    if (var_v0_20 >= 0) {
        goto block_110;
    }
    var_v0_20 = 0 - var_v0_20;
block_110:
    if (var_v0_20 >= 0x20) {
        goto block_115;
    }
    var_v0_21 = M2C_FIELD(arg1, s16 *, 6);
    compare_v1 = M2C_FIELD(temp_s3, s16 *, 6);
    var_v0_21 -= compare_v1;
    if (var_v0_21 >= 0) {
        goto block_113;
    }
    var_v0_21 = 0 - var_v0_21;
block_113:
    if (var_v0_21 >= 0x20) {
        goto block_115;
    }
    temp_s1 = M2C_FIELD(arg0, void **, 0x9C) - 0x20;
    func_8009CE1C(M2C_FIELD(arg0, void **, 0x9C), 0xC, D_80027C96, 0xA, (s32) (s16) (M2C_FIELD(arg0, u16 *, 0x44) << 9), D_80027C98, 2);
    func_800A56E0(0x300);
    func_80024938(M2C_FIELD(temp_s3, s16 *, 2), M2C_FIELD(temp_s3, s16 *, 6), (s16) M2C_FIELD(temp_s3, u16 *, 0xA), (s16) M2C_FIELD(arg0, u16 *, 0x38), (func_80069EF8() & 3) | 4);
    M2C_FIELD(temp_s1, u16 *, 0x1E) = (u16) (M2C_FIELD(temp_s1, u16 *, 0x1E) | 0x2000);
    M2C_FIELD(arg0, void **, 0x9C) = NULL;
    M2C_FIELD(arg0, u16 *, 0x8A) = (u16) ((func_80069EF8() & 0x1F) + 0x10);
block_115:
    state6_velocity = func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x38));

    state6_velocity <<= 8;
    M2C_FIELD(arg1, s32 *, 0xC) = state6_velocity;
    state6_velocity = func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x38));

    state6_velocity <<= 8;
    ASM_KEEP(state6_velocity);   /* MATCH pin: retail delay-slot fill depends on it */
    M2C_FIELD(arg1, s32 *, 0x10) = state6_velocity;

    if ((s16) M2C_FIELD(arg0, u16 *, 0x38) != temp_s2) {
        goto block_123;
    }
    temp_v0_8 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_v1_10 = M2C_FIELD(arg1, s32 *, 0x10);
    update_a0 = temp_v0_8 >> 1;
    temp_v0_8 += update_a0;
    M2C_FIELD(arg1, s32 *, 0xC) = temp_v0_8;
    update_v0 = temp_v1_10 >> 1;
    temp_v1_10 += update_v0;
    M2C_FIELD(arg1, s32 *, 0x10) = temp_v1_10;
    goto block_123;
block_117:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    temp_v0_9 = M2C_FIELD(arg0, u16 *, 0x8A) - 1;
    M2C_FIELD(arg0, u16 *, 0x8A) = temp_v0_9;
    if ((temp_v0_9 << 0x10) > 0) {
        goto block_121;
    }
    temp_v0_10 = func_80026444(&D_80082E80);
    M2C_FIELD(arg0, void **, 0x9C) = temp_v0_10;
    if (temp_v0_10 != NULL) {
        goto block_120;
    }
    M2C_FIELD(arg0, s16 *, 0x30) = 0x10;
    M2C_FIELD(arg0, u16 *, 0x8A) = 8U;
    goto block_122;
block_120:
    temp_s3 = M2C_FIELD(temp_v0_10, void **, -0x18);
    M2C_FIELD(arg0, u16 *, 0x34) = 0x10U;
    state6_target_base = M2C_FIELD(arg1, s16 *, 0xA);
    update_v0 = M2C_FIELD(temp_s3, s16 *, 0xA);
    state6_target_base += 0x40;
    division_numerator = (update_v0 - state6_target_base) << 0x10;
    divisor16 = 16;
    ASM_KEEP(divisor16);   /* MATCH pin: keeps a constant in a register as retail does */
    M2C_FIELD(arg1, s32 *, 0x14) = division_numerator / divisor16;
    M2C_FIELD(arg0, u16 *, 0x9A) = 0x3CU;
    goto block_122;
block_121:
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) (M2C_FIELD(arg0, u16 *, 0x38) + 0x80);
block_122:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x38)) << 8);
block_123:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    goto block_128;
jt_c16:
    temp_v0_11 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_v1_11 = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v0_11 - (temp_v0_11 >> 3));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v1_11 - (temp_v1_11 >> 3));
    if ((M2C_FIELD(arg0, s16 *, 0x3E) - 0x10) >= (s16) M2C_FIELD(arg1, u16 *, 0xA)) {
        goto block_126;
    }
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) ((u16) M2C_FIELD(arg0, s16 *, 0x3E) - 0x10);
block_126:
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    temp_v1_12 = M2C_FIELD(arg2, u8 *, 0xC);
    M2C_FIELD(arg2, u8 *, 0xC) = (u8) (temp_v1_12 - ((s32) temp_v1_12 / (s16) M2C_FIELD(arg0, u16 *, 0x8A)));
    temp_v1_13 = M2C_FIELD(arg2, u8 *, 0xD);
    M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_v1_13 - ((s32) temp_v1_13 / (s16) M2C_FIELD(arg0, u16 *, 0x8A)));
    temp_v1_14 = M2C_FIELD(arg2, u8 *, 0xE);
    M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_v1_14 - ((s32) temp_v1_14 / (s16) M2C_FIELD(arg0, u16 *, 0x8A)));
    temp_v0_12 = M2C_FIELD(arg0, u16 *, 0x8A) - 1;
    M2C_FIELD(arg0, u16 *, 0x8A) = temp_v0_12;
    if ((temp_v0_12 << 0x10) > 0) {
        goto block_146;
    }
    D_80027C94 = 0;
    goto block_139;
jt_c7:
jt_c8:
jt_c9:
jt_c10:
jt_c11:
jt_c12:
jt_c13:
jt_c14:
jt_c15:
block_128:
block_129:
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (func_800A07D0(0, 0, M2C_FIELD(arg1, s16 *, 0xE), M2C_FIELD(arg1, s16 *, 0x12)) - 0x400);
    common_speed = M2C_FIELD(arg1, s16 *, 0x16);
    ASM_KEEP(common_speed);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_a0_3 = M2C_FIELD(arg2, u16 *, 0x1C);
    temp_v1_15 = M2C_FIELD(arg2, u8 *, 0xC);
    ASM_KEEP(temp_a0_3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(temp_v1_15);   /* MATCH pin: load-bearing for the whole function shape */
    temp_s2 = common_speed * 4;
    common_pitch = temp_s2 + 0x400;
    M2C_FIELD(arg2, u16 *, 0x16) = (u16) common_pitch;
    common_pitch = 0x2000;
    common_pitch -= temp_a0_3;
    common_pitch >>= 2;
    temp_a0_3 += common_pitch;
    temp_v1_15 += 8;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v1_15;
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) temp_a0_3;
    M2C_FIELD(arg2, u16 *, 0x20) = (u16) temp_a0_3;
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) temp_a0_3;
    if ((u32) (temp_v1_15 & 0xFF) < 0x81U) {
        goto block_131;
    }
    M2C_FIELD(arg2, s32 *, 0xC) = 0x808080;
    goto block_132;
block_131:
    M2C_FIELD(arg2, u8 *, 0xD) = (u8) (M2C_FIELD(arg2, u8 *, 0xD) + 8);
    M2C_FIELD(arg2, u8 *, 0xE) = (u8) (M2C_FIELD(arg2, u8 *, 0xE) + 8);
block_132:
    func_80026694(arg0 - 0x20, arg1, 8, 0x300);
    func_800262F4(arg2, arg0 + 0x36, M2C_FIELD(arg0, s16 *, 0x3C), M2C_FIELD(arg0, s16 *, 0x3A));
    func_80026240(arg0, M2C_FIELD(arg2, s32 *, 0));
    temp_v0_13 = M2C_FIELD(arg2, u8 *, 4);
    if ((s8) temp_v0_13 != M2C_FIELD(arg0, s16 *, 0x3A)) {
        goto block_134;
    }
    var_v0_22 = -1;
    goto block_136;
block_134:
    if ((s8) temp_v0_13 != M2C_FIELD(arg0, s16 *, 0x3C)) {
        goto block_137;
    }
    var_v0_22 = 1;
block_136:
    M2C_FIELD(arg0, s16 *, 0x36) = var_v0_22;
block_137:
    func_8002470C((s16) M2C_FIELD(arg1, u16 *, 2), (s16) M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA), (s16) M2C_FIELD(arg0, u16 *, 0x38), D_80026BD4[(s8) M2C_FIELD(arg2, u8 *, 4)]);
    goto block_145;
block_138:
    temp_s0 = temp_v1 | 0x80000000;
    if (!(M2C_FIELD(temp_s0, u16 *, 0x1E) & 0x8000)) {
        goto block_140;
    }
block_139:
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    return;
block_140:
    temp_s1 = M2C_FIELD(temp_s0, void **, 0xC);
    temp_s3 = M2C_FIELD(temp_s0, void **, 8);
    if (!(temp_v1 & 0x80000000)) {
        goto block_142;
    }
    temp_s0_4 = temp_s0 + 0x20;
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (func_800A07D0((s16) M2C_FIELD(arg1, u16 *, 2), (s16) M2C_FIELD(arg1, u16 *, 6), M2C_FIELD(temp_s3, s16 *, 2), M2C_FIELD(temp_s3, s16 *, 6)) - 0x400);
    alternate_delta = M2C_FIELD(temp_s3, s16 *, 0xA);
    update_v0 = M2C_FIELD(arg1, s16 *, 0xA);
    alternate_delta -= update_v0;
    alternate_scale = alternate_delta << 2;
    alternate_scale += alternate_delta;
    temp_s2 = alternate_scale << 1;
    common_pitch = temp_s2 + 0x400;
    M2C_FIELD(arg2, u16 *, 0x16) = (u16) common_pitch;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) M2C_FIELD(temp_s1, u16 *, 0x14);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_s0_4, u16 *, 0x50);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_s0_4, u16 *, 0x52);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(temp_s0_4, u16 *, 0x54);
    goto block_143;
block_142:
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_s3, s16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_s3, s16 *, 6);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(temp_s3, s16 *, 0xA);
    M2C_FIELD(arg2, u16 *, 0x16) = (u16) M2C_FIELD(temp_s1, u16 *, 0x16);
    M2C_FIELD(arg2, u16 *, 0x18) = (u16) M2C_FIELD(temp_s1, u16 *, 0x18);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) M2C_FIELD(temp_s1, u16 *, 0x1A);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) M2C_FIELD(temp_s1, u16 *, 0x14);
block_143:
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) M2C_FIELD(temp_s1, u16 *, 0x1C);
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) M2C_FIELD(temp_s1, u16 *, 0x1E);
    M2C_FIELD(arg2, u16 *, 0x20) = (u16) M2C_FIELD(temp_s1, u16 *, 0x20);
    M2C_FIELD(arg2, s32 *, 0xC) = M2C_FIELD(temp_s1, s32 *, 0xC);
    if (D_80026BC8[M2C_FIELD(arg0, s16 *, 0x88)] == 0) {
        goto block_145;
    }
    func_800263C0(arg2, M2C_FIELD(temp_s1, s8 *, 4));
    func_80026240(arg0, M2C_FIELD(arg2, s32 *, 0));
block_145:
    M2C_FIELD(arg0, u16 *, 0x94) = (u16) (M2C_FIELD(arg0, u16 *, 0x94) + 1);
block_146:
    return;
}
