#include "common.h"
#include "m2c_compat.h"

typedef struct { s32 a, b; } __attribute__((packed)) M2C_PACKED_PAIR;
typedef struct { s16 x, y, z; } M2C_VEC3S;

typedef struct { s32 sf; } M2C_S32F;
#define M2C_SFIELD(expr, offset) (((M2C_S32F *)((s8 *)(expr) + (offset)))->sf)
typedef struct S_819835AC_1 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_28;
    union {
        s16 s16;
        u16 u16;
    } unk_2A;
    union {
        s16 s16;
        u16 u16;
    } unk_2C;
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_34;
    s16 unk_36;
    u16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
    u8 pad_4E[0x3A];
    s16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0x8];
    u16 unk_94;
    s16 unk_96;
    u8 unk_98;
    u8 unk_99;
    u16 unk_9A;
    void * unk_9C;
} S_819835AC_1;

typedef struct S_819835AC_2 {
    union {
        s32 word;
        struct {
            u8 pad_00[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_02;
        } half;
    } unk_00;
    union {
        s32 word;
        struct {
            u8 pad_04[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_06;
        } half;
    } unk_04;
    union {
        s32 word;
        struct {
            u8 pad_08[0x2];
            union {
                s16 s16;
                u16 u16;
            } unk_0A;
        } half;
    } unk_08;
    union {
        s32 word;
        struct {
            u8 pad_0C[0x2];
            s16 unk_0E;
        } half;
    } unk_0C;
    union {
        s32 word;
        struct {
            u8 pad_10[0x2];
            s16 unk_12;
        } half;
    } unk_10;
    union {
        s32 word;
        struct {
            u8 pad_14[0x2];
            s16 unk_16;
        } half;
    } unk_14;
} S_819835AC_2;

typedef struct S_819835AC_3 {
    s32 unk_00;
    u8 unk_04;
    u8 pad_05[0x7];
    union {
        s32 word;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } half;
    } unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_819835AC_3;

typedef struct S_819835AC_4 {
    u8 pad_00[0x48];
    M2C_PACKED_PAIR unk_48;
    M2C_PACKED_PAIR unk_50;
} S_819835AC_4;

typedef struct S_819835AC_5 {
    u8 pad_00[0x2A];
    union {
        s16 s16;
        u16 u16;
    } unk_2A;
    u8 pad_2C[0x5C];
    union {
        s16 s16;
        u16 u16;
    } unk_88;
} S_819835AC_5;

typedef struct S_819835AC_6 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
    u8 pad_8A[0xC];
    s16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
} S_819835AC_6;

typedef struct S_819835AC_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    u8 unk_24;
    u8 unk_25;
} S_819835AC_7;

typedef struct S_819835AC_8 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_819835AC_8;

typedef struct S_819835AC_9 {
    u8 pad_00[0x50];
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
} S_819835AC_9;

typedef struct S_819835AC_10 {
    u16 unk_00;
} S_819835AC_10;

typedef struct S_819835AC_11 {
    void * unk_00;
} S_819835AC_11;

typedef struct S_819835AC_12 {
    s32 unk_00;
} S_819835AC_12;

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

/* Update a homing effect's movement, target hits, appearance, and attached copies. */
void func_80024DAC(S_819835AC_1 *effect, S_819835AC_2 *motion, S_819835AC_3 *visual) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16 };
    M2C_VEC3S emit_offset;
    s32 aim_angle;
    s32 angle_mask;
    s32 normalized_angle;
    s32 state;
    s32 approach_angle;
    s32 travel_angle;
    s32 homing_angle;
    s32 world_y;
    s32 world_x;
    s16 frame_step;
    s32 next_tile_y;
    s32 rise_speed;
    register s32 heading_or_owner ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 fade_speed_x;
    register s32 boost_speed_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 owner_ref;
    s32 boost_speed_y;
    s32 fade_speed_y;
    s16 height_frames;
    register s32 height_numerator ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 history_index ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 travel_turn_gap;
    s32 travel_gap_x;
    s32 travel_gap_y;
    s32 hit_height_gap;
    s32 homing_wrap_gap;
    s32 homing_turn_gap;
    s32 target_gap_x;
    s32 target_gap_y;
    s32 approach_wrap_gap;
    s32 approach_turn_gap;
    register s32 approach_gap_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 approach_gap_y;
    s32 approach_gap_z;
    s32 travel_wrap_gap;
    s32 visual_scale;
    u16 approach_ticks;
    u16 fade_ticks;
    u16 travel_ticks;
    u16 launch_ticks;
    u16 aim_ticks;
    u16 bob_phase;
    u16 search_ticks;
    u16 approach_heading;
    u16 travel_heading;
    u16 homing_heading;
    u16 approach_signed_angle;
    u16 travel_next_angle;
    u16 homing_signed_angle;
    u16 homing_next_angle;
    u16 approach_next_angle;
    u16 travel_signed_angle;
    u8 frame;
    u8 fade_red;
    u8 fade_green;
    u8 fade_blue;
    u8 red;
    S_819835AC_9 *owner_state;
    S_819835AC_7 *actor_data;
    S_819835AC_2 *related_motion;
    S_819835AC_6 *new_target;
    S_819835AC_6 *target;
    register S_819835AC_4 *history ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    S_819835AC_6 *hit_actor;
    S_819835AC_2 *state0_move;
    S_819835AC_5 *state0_actor;
    S_819835AC_5 *state0_height_actor;
    register s32 side_component ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 state0_delta_x;
    s32 state0_delta_y;
    register s32 coord_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 coord_delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 step_y;
    s32 step_z;
    S_819835AC_6 *state1_global;
    s32 target_coord;
    S_819835AC_2 *state1_move;
    S_819835AC_6 *state1_actor;
    S_819835AC_6 *state2_stage;
    register void *list_sentinel ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 tile_x;
    u16 tile_counter;
    u8 tile_y;
    s32 tile_div;
    S_819835AC_7 *state34_base;
    S_819835AC_2 *state34_move;
    S_819835AC_2 *state34_emit;
    S_819835AC_5 *state2_actor;
    u32 state2_angle;
    S_819835AC_7 *tile_base;
    u32 tile_coord;
    s32 tile_call_arg;
    s32 common_speed;
    register s32 common_pitch ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 state6_timer_signed;
    u16 state6_timer;
    u16 state6_next;
    u16 state6_height;
    s32 state6_spin_arg;
    register s32 state6_velocity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 state6_target_base;
    s32 alternate_delta;
    s32 alternate_scale;
    u16 approach_frames;

    history_index = 0;
    history = (S_819835AC_4 *) effect;
    (*(s16 *)&D_800269F8) = (s16) (((S_819835AC_10 *) &D_800269F8)->unk_00 + 1);
copy_history:
    {
        s32 history_xy;
        s32 history_z_pad;

        history_xy = history->unk_48.a;
        history_z_pad = history->unk_48.b;
        history->unk_50.a = history_xy;
        history->unk_50.b = history_z_pad;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    history_index -= 1;
    history = (S_819835AC_4 *) ((u8 *) history - 8);
    if (history_index >= 0) {
        goto copy_history;
    }
    owner_ref = effect->unk_20;
    effect->unk_48 = (u16) motion->unk_00.half.unk_02.u16;
    effect->unk_4A = (u16) motion->unk_04.half.unk_06.u16;
    effect->unk_4C = (u16) motion->unk_08.half.unk_0A.u16;
    if (owner_ref != 0) {
        goto block_138;
    }
    state = effect->unk_30;
    if ((u32) state >= 0x11U) {
        goto block_128;
    }
    (void)state_labels; goto *D_80024020[(u32)(state)];
jt_c0:
    func_8003DE58(*(M2C_UNK *)((((s32) (D_80083228 + ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C) + D_800E3D18), &D_80082E80, (u8 *) effect + 0x28, 0);
    heading_or_owner = func_80064584(((S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16);
    side_component = func_80064584(((S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16 - 0x400);
    state0_move = (S_819835AC_2 *) &D_80083780;
    ASM_KEEP(state0_move);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    heading_or_owner >>= 4;
    state0_delta_x = state0_move->unk_00.half.unk_02.u16;
    side_component >>= 4;
    state0_delta_x -= heading_or_owner;
    state0_delta_x += side_component;
    coord_value = effect->unk_28.u16;
    state0_actor = ((S_819835AC_11 *) &D_800E3D7C)->unk_00;
    coord_value += state0_delta_x;
    effect->unk_28.u16 = (u16) coord_value;
    heading_or_owner = func_800644B8(state0_actor->unk_2A.s16);
    side_component = func_800644B8(((S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16 - 0x400);
    heading_or_owner >>= 4;
    side_component >>= 4;
    state0_delta_y = state0_move->unk_04.half.unk_06.u16;
    coord_delta = effect->unk_2A.u16;
    state0_delta_y -= heading_or_owner;
    state0_delta_y += side_component;
    state0_height_actor = ((S_819835AC_11 *) &D_800E3D7C)->unk_00;
    coord_delta += state0_delta_y;
    effect->unk_2A.u16 = (u16) coord_delta;
    coord_delta = effect->unk_2C.u16;
    step_y = state0_height_actor->unk_88.u16;
    approach_frames = 0x10U;
    effect->unk_34.u16 = approach_frames;
    coord_delta -= 0x50;
    step_y += coord_delta;
    effect->unk_2C.u16 = (u16) step_y;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    height_numerator = (effect->unk_2C.s16 - motion->unk_08.half.unk_0A.s16) << 0x10;
    height_frames = 16;
    motion->unk_14.word = height_numerator / height_frames;
    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
jt_c1:
    aim_angle = func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16, (s16) effect->unk_28.u16, (s16) effect->unk_2A.u16);
    approach_heading = effect->unk_38;
    if (approach_heading & 0x800) {
        approach_signed_angle = approach_heading | 0xF800;
    } else {
        approach_signed_angle = approach_heading & 0x7FF;
    }
block_8:
    effect->unk_38 = approach_signed_angle;
    if (!(aim_angle & 0x800)) {
        goto block_10;
    }
    angle_mask = ~0x7FF;
    normalized_angle = aim_angle | angle_mask;
    goto block_11;
block_10:
    normalized_angle = aim_angle & 0x7FF;
block_11:
    aim_angle = normalized_angle;
    approach_wrap_gap = (s16) effect->unk_38 - aim_angle;
    if (approach_wrap_gap >= 0) {
        goto block_13;
    }
    approach_wrap_gap = 0 - approach_wrap_gap;
block_13:
    if (approach_wrap_gap < 0x801) {
        goto block_15;
    }
    effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
block_15:
    approach_angle = (s16) effect->unk_38;
    approach_turn_gap = aim_angle - approach_angle;
    if (approach_turn_gap >= 0) {
        goto block_17;
    }
    approach_turn_gap = 0 - approach_turn_gap;
block_17:
    if (approach_turn_gap < 0x81) {
        goto block_21;
    }
    if (effect->unk_96 != 0) {
        approach_next_angle = approach_angle + 0x80;
    } else {
        approach_next_angle = approach_angle - 0x80;
    }
    effect->unk_38 = approach_next_angle;
    goto block_22;
block_21:
    effect->unk_38 = aim_angle;
block_22:
    motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
    motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
    approach_ticks = effect->unk_34.u16 - 1;
    effect->unk_34.u16 = approach_ticks;
    if ((approach_ticks << 0x10) > 0) {
        goto block_24;
    }
    motion->unk_08.half.unk_0A.u16 = (u16) effect->unk_2C.u16;
    effect->unk_34.u16 = 0U;
    motion->unk_14.word = 0;
block_24:
    state1_global = ((S_819835AC_11 *) &D_800814A8)->unk_00;
    state1_global->unk_96 = 2;
    coord_value = motion->unk_00.word;
    coord_delta = motion->unk_0C.word;
    step_y = motion->unk_10.word;
    step_z = motion->unk_14.word;
    coord_value += coord_delta;
    motion->unk_00.word = coord_value;
    coord_value = motion->unk_04.word;
    coord_delta = motion->unk_08.word;
    coord_value += step_y;
    motion->unk_04.word = coord_value;
    approach_gap_x = motion->unk_00.half.unk_02.s16;
    coord_delta += step_z;
    motion->unk_08.word = coord_delta;
    approach_gap_x -= effect->unk_28.s16;
    if (__builtin_abs(approach_gap_x) >= 0x40) {
        goto block_129;
    }
    approach_gap_y = motion->unk_04.half.unk_06.s16;
    target_coord = effect->unk_2A.s16;
    approach_gap_y -= target_coord;
    if (__builtin_abs(approach_gap_y) >= 0x40) {
        goto block_129;
    }
    approach_gap_z = motion->unk_08.half.unk_0A.s16;
    target_coord = effect->unk_2C.s16;
    approach_gap_z -= target_coord;
    if (__builtin_abs(approach_gap_z) >= 0x40) {
        goto block_129;
    }
    func_8003DE58(*(M2C_UNK *)((((s32) (D_80083228 + ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C) + D_800E3D18), &D_80082E80, (u8 *) effect + 0x28, 0);
    state1_move = (S_819835AC_2 *) &D_80083780;
    coord_value = effect->unk_28.u16;
    coord_delta = state1_move->unk_00.half.unk_02.u16;
    coord_value += coord_delta;
    effect->unk_28.u16 = coord_value;
    coord_value = effect->unk_2A.u16;
    coord_delta = state1_move->unk_04.half.unk_06.u16;
    state1_actor = ((S_819835AC_11 *) &D_800814A8)->unk_00;
    coord_value += coord_delta;
    effect->unk_2A.u16 = coord_value;
    coord_delta = effect->unk_2C.u16;
    coord_value = ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_88.u16;
    coord_delta -= 0x50;
    coord_value += coord_delta;
    effect->unk_2C.u16 = coord_value;
    coord_value = state1_actor->unk_A6 - 1;
    state1_actor->unk_A6 = coord_value;
    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
    goto block_128;
jt_c2:
    aim_angle = func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16, (s16) effect->unk_28.u16, (s16) effect->unk_2A.u16);
    travel_heading = effect->unk_38;
    if (travel_heading & 0x800) {
        travel_signed_angle = travel_heading | 0xF800;
    } else {
        travel_signed_angle = travel_heading & 0x7FF;
    }
block_36:
    effect->unk_38 = travel_signed_angle;
    if (!(aim_angle & 0x800)) {
        goto block_38;
    }
    angle_mask = ~0x7FF;
    normalized_angle = aim_angle | angle_mask;
    goto block_39;
block_38:
    normalized_angle = aim_angle & 0x7FF;
block_39:
    aim_angle = normalized_angle;
    travel_wrap_gap = (s16) effect->unk_38 - aim_angle;
    if (travel_wrap_gap >= 0) {
        goto block_41;
    }
    travel_wrap_gap = 0 - travel_wrap_gap;
block_41:
    if (travel_wrap_gap < 0x801) {
        goto block_43;
    }
    effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
block_43:
    travel_angle = (s16) effect->unk_38;
    travel_turn_gap = aim_angle - travel_angle;
    if (travel_turn_gap >= 0) {
        goto block_45;
    }
    travel_turn_gap = 0 - travel_turn_gap;
block_45:
    if (travel_turn_gap < 0x81) {
        goto block_49;
    }
    if (effect->unk_96 != 0) {
        travel_next_angle = travel_angle + 0x80;
    } else {
        travel_next_angle = travel_angle - 0x80;
    }
    effect->unk_38 = travel_next_angle;
    goto block_50;
block_49:
    effect->unk_38 = aim_angle;
block_50:
    motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
    motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
    travel_ticks = effect->unk_34.u16 - 1;
    effect->unk_34.u16 = travel_ticks;
    if ((travel_ticks << 0x10) > 0) {
        goto block_52;
    }
    motion->unk_08.half.unk_0A.u16 = (u16) effect->unk_2C.u16;
    effect->unk_34.u16 = 0U;
    motion->unk_14.word = 0;
block_52:
    coord_value = motion->unk_00.word;
    coord_delta = motion->unk_0C.word;
    step_y = motion->unk_10.word;
    step_z = motion->unk_14.word;
    coord_value += coord_delta;
    motion->unk_00.word = coord_value;
    coord_value = motion->unk_04.word;
    coord_delta = motion->unk_08.word;
    coord_value += step_y;
    coord_delta += step_z;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    motion->unk_04.word = coord_value;
    state2_stage = (*(void **)((u8 *)&D_800814A8 + 0));
    motion->unk_08.word = coord_delta;
    state2_stage->unk_96 = 2;
    travel_gap_x = motion->unk_00.half.unk_02.s16;
    target_coord = effect->unk_28.s16;
    travel_gap_x -= target_coord;
    if (travel_gap_x >= 0) {
        goto block_54;
    }
    travel_gap_x = 0 - travel_gap_x;
block_54:
    if (travel_gap_x >= 0x20) {
        goto block_128;
    }
    travel_gap_y = motion->unk_04.half.unk_06.s16;
    target_coord = effect->unk_2A.s16;
    travel_gap_y -= target_coord;
    if (travel_gap_y >= 0) {
        goto block_57;
    }
    travel_gap_y = 0 - travel_gap_y;
block_57:
    if (travel_gap_y >= 0x20) {
        goto block_128;
    }
    effect->unk_34.u16 = 4U;
    state2_actor = ((S_819835AC_11 *) &D_800E3D7C)->unk_00;
    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
    ((S_819835AC_6 *) ((S_819835AC_11 *) &D_800814A8)->unk_00)->unk_96 = 0;
    effect->unk_38 = (u16) state2_actor->unk_2A.s16;
    state2_angle = state2_actor->unk_2A.u16;
    D_80026B28 = 0;
    effect->unk_44 = (u16) ((state2_angle >> 9) & 7);
    goto block_128;
jt_c3:
jt_c4:
    state34_base = (S_819835AC_7 *) &D_80082E80;
    if (func_8003DE58(state34_base->unk_08, state34_base, &emit_offset, 0) == 0) {
        goto block_63;
    }
    if (effect->unk_30 != 3) {
        goto block_62;
    }
    state34_move = (S_819835AC_2 *) &D_80083780;
    func_800B8D64(state34_move->unk_00.half.unk_02.s16 + emit_offset.x, state34_move->unk_04.half.unk_06.s16 + emit_offset.y, state34_move->unk_08.half.unk_0A.s16 + emit_offset.z);
    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
block_62:
    state34_emit = (S_819835AC_2 *) &D_80083780;
    func_80024B2C((s16) (state34_emit->unk_00.half.unk_02.u16 + (u16) emit_offset.x), (s16) (state34_emit->unk_04.half.unk_06.u16 + (u16) emit_offset.y), (s16) (state34_emit->unk_08.half.unk_0A.u16 + (u16) emit_offset.z), ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16, 0);
block_63:
    motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
    motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
    motion->unk_14.half.unk_16 = 0x16;
    rise_speed = motion->unk_14.word;
    motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
    motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
    M2C_SFIELD(motion, 8) = (s32) (motion->unk_08.word + motion->unk_14.word);
    if ((s16) motion->unk_08.half.unk_0A.u16 <= ((S_819835AC_5 *) (*(void **)((u8 *)&D_800E3D7C + 0)))->unk_88.s16) {
        goto block_65;
    }
    motion->unk_08.half.unk_0A.u16 = (u16) ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_88.s16;
block_65:
    launch_ticks = effect->unk_34.u16 - 1;
    effect->unk_34.u16 = launch_ticks;
    if ((launch_ticks << 0x10) > 0) {
        goto block_129;
    }
    tile_base = (S_819835AC_7 *) &D_80082E80;
    tile_coord = tile_base->unk_24;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    tile_call_arg = 0x300;
    ASM_KEEP(tile_call_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    effect->unk_40 = (s16) tile_coord;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    effect->unk_98 = (u8) tile_coord;
    tile_coord = tile_base->unk_25;
    effect->unk_30 = 5;
    effect->unk_46 = 3U;
    effect->unk_34.u16 = 0U;
    effect->unk_42 = (s16) tile_coord;
    effect->unk_99 = (u8) tile_coord;
    func_800A56E0(tile_call_arg, rise_speed);
    goto block_129;
jt_c5:
    motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
    motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
    motion->unk_14.word = 0;
    motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
    world_x = motion->unk_00.half.unk_02.s16;
    motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
    motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
    if (world_x >= 0) {
        goto block_69;
    }
    world_x += 0x3F;
block_69:
    tile_div = world_x >> 6;
    effect->unk_40 = (s16) tile_div;
    world_y = motion->unk_04.half.unk_06.s16;
    if (world_y >= 0) {
        goto block_71;
    }
    world_y += 0x3F;
block_71:
    next_tile_y = world_y >> 6;
    effect->unk_42 = (s16) next_tile_y;
    if (effect->unk_98 != effect->unk_40) {
        goto block_73;
    }
    if (effect->unk_99 == next_tile_y) {
        goto block_129;
    }
block_73:
    hit_actor = ((S_819835AC_11 *) &D_800814A8)->unk_00;
    list_sentinel = hit_actor;
    hit_actor = hit_actor->unk_5C + 0x20;
    if (hit_actor != list_sentinel) {
        do {
            actor_data = ((S_819835AC_8 *) ((u8 *) hit_actor - 0x20))->unk_0C;
            if ((actor_data->unk_24 == effect->unk_40) &&
                (actor_data->unk_25 == effect->unk_42)) {
                hit_height_gap = hit_actor->unk_88;
                target_coord = motion->unk_08.half.unk_0A.s16;
                hit_height_gap -= target_coord;
                if (hit_height_gap < 0) {
                    hit_height_gap = -hit_height_gap;
                }
                actor_data = (u8 *) hit_actor - 0x20;
                if ((hit_height_gap < 0x80) && !(actor_data->unk_1E & 0x2000)) {
                    func_8009CE1C(hit_actor, 0xC, D_80027C96, 0xA, (s32) (s16) (effect->unk_44 << 9), D_80027C98, 2);
                    related_motion = ((S_819835AC_8 *) ((u8 *) hit_actor - 0x20))->unk_08;
                    func_80024938(related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16, related_motion->unk_08.half.unk_0A.s16, (s16) effect->unk_38, (func_80069EF8() & 3) | 4);
                    actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                }
            }
            coord_delta = hit_actor->unk_5C;
            hit_actor = coord_delta + 0x20;
        } while (hit_actor != ((S_819835AC_11 *) &D_800814A8)->unk_00);
    }
block_83:
    tile_x = (u8) effect->unk_40;
    tile_counter = effect->unk_46;
    tile_y = (u8) effect->unk_42;
    tile_counter -= 1;
    effect->unk_46 = tile_counter;
    effect->unk_98 = tile_x;
    effect->unk_99 = tile_y;
    if ((tile_counter << 0x10) > 0) {
        goto block_128;
    }
    effect->unk_8A = (u16) ((func_80069EF8() & 0x1F) + 0x10);
    effect->unk_9C = NULL;
    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
    goto block_128;
jt_c6:
    target = effect->unk_9C;
    if (target == NULL) {
        goto block_117;
    }
    related_motion = ((S_819835AC_8 *) ((u8 *) target - 0x20))->unk_08;
    aim_angle = func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16, related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16);
    homing_heading = effect->unk_38;
    if (homing_heading & 0x800) {
        homing_signed_angle = homing_heading | 0xF800;
    } else {
        homing_signed_angle = homing_heading & 0x7FF;
    }
block_88:
    effect->unk_38 = homing_signed_angle;
    if (!(aim_angle & 0x800)) {
        goto block_90;
    }
    angle_mask = ~0x7FF;
    normalized_angle = aim_angle | angle_mask;
    goto block_91;
block_90:
    normalized_angle = aim_angle & 0x7FF;
block_91:
    aim_angle = normalized_angle;
    homing_wrap_gap = (s16) effect->unk_38 - aim_angle;
    if (homing_wrap_gap >= 0) {
        goto block_93;
    }
    homing_wrap_gap = 0 - homing_wrap_gap;
block_93:
    if (homing_wrap_gap < 0x801) {
        goto block_95;
    }
    effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
block_95:
    aim_ticks = effect->unk_9A - 1;
    effect->unk_9A = aim_ticks;
    if ((aim_ticks << 0x10) > 0) {
        goto block_97;
    }
    effect->unk_9A = 0x1EU;
    effect->unk_38 = aim_angle;
block_97:
    homing_angle = (s16) effect->unk_38;
    homing_turn_gap = aim_angle - homing_angle;
    if (homing_turn_gap >= 0) {
        goto block_99;
    }
    homing_turn_gap = 0 - homing_turn_gap;
block_99:
    if (homing_turn_gap < 0x81) {
        goto block_103;
    }
    if (effect->unk_96 != 0) {
        homing_next_angle = homing_angle + 0x80;
    } else {
        homing_next_angle = homing_angle - 0x80;
    }
    effect->unk_38 = homing_next_angle;
    goto block_104;
block_103:
    effect->unk_38 = aim_angle;
block_104:
    state6_timer_signed = effect->unk_34.s16;

    state6_timer = effect->unk_34.u16;
    if (state6_timer_signed == 0) {
        goto block_107;
    }
    state6_next = state6_timer - 1;
    effect->unk_34.u16 = state6_next;
    if ((state6_next << 0x10) != 0) {
        goto block_108;
    }
    state6_height = related_motion->unk_08.half.unk_0A.u16;
    motion->unk_14.word = 0;
    state6_height -= 0x40;
    motion->unk_08.half.unk_0A.u16 = state6_height;
    effect->unk_8A = 0U;
    goto block_108;
block_107:
    bob_phase = effect->unk_8A + 1;
    state6_spin_arg = (s32) (bob_phase << 0x10);

    state6_spin_arg >>= 9;
    effect->unk_8A = bob_phase;
    motion->unk_14.half.unk_16 = (s16) (func_800644B8(state6_spin_arg) >> 9);
block_108:
    target_gap_x = motion->unk_00.half.unk_02.s16;
    target_coord = related_motion->unk_00.half.unk_02.s16;
    target_gap_x -= target_coord;
    if (target_gap_x >= 0) {
        goto block_110;
    }
    target_gap_x = 0 - target_gap_x;
block_110:
    if (target_gap_x >= 0x20) {
        goto block_115;
    }
    target_gap_y = motion->unk_04.half.unk_06.s16;
    target_coord = related_motion->unk_04.half.unk_06.s16;
    target_gap_y -= target_coord;
    if (target_gap_y >= 0) {
        goto block_113;
    }
    target_gap_y = 0 - target_gap_y;
block_113:
    if (target_gap_y >= 0x20) {
        goto block_115;
    }
    actor_data = effect->unk_9C - 0x20;
    func_8009CE1C(effect->unk_9C, 0xC, D_80027C96, 0xA, (s32) (s16) (effect->unk_44 << 9), D_80027C98, 2);
    func_800A56E0(0x300);
    func_80024938(related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16, (s16) related_motion->unk_08.half.unk_0A.u16, (s16) effect->unk_38, (func_80069EF8() & 3) | 4);
    actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
    effect->unk_9C = NULL;
    effect->unk_8A = (u16) ((func_80069EF8() & 0x1F) + 0x10);
block_115:
    state6_velocity = func_80064584((s16) effect->unk_38);

    state6_velocity <<= 8;
    motion->unk_0C.word = state6_velocity;
    state6_velocity = func_800644B8((s16) effect->unk_38);

    state6_velocity <<= 8;
    ASM_KEEP(state6_velocity);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    motion->unk_10.word = state6_velocity;

    if ((s16) effect->unk_38 != aim_angle) {
        goto block_123;
    }
    boost_speed_x = motion->unk_0C.word;
    boost_speed_y = motion->unk_10.word;
    step_y = boost_speed_x >> 1;
    boost_speed_x += step_y;
    motion->unk_0C.word = boost_speed_x;
    coord_value = boost_speed_y >> 1;
    boost_speed_y += coord_value;
    motion->unk_10.word = boost_speed_y;
    goto block_123;
block_117:
    motion->unk_14.word = 0;
    search_ticks = effect->unk_8A - 1;
    effect->unk_8A = search_ticks;
    if ((search_ticks << 0x10) > 0) {
        goto block_121;
    }
    new_target = func_80026444(&D_80082E80);
    effect->unk_9C = new_target;
    if (new_target != NULL) {
        goto block_120;
    }
    effect->unk_30 = 0x10;
    effect->unk_8A = 8U;
    goto block_122;
block_120:
    related_motion = ((S_819835AC_8 *) ((u8 *) new_target - 0x20))->unk_08;
    effect->unk_34.u16 = 0x10U;
    state6_target_base = motion->unk_08.half.unk_0A.s16;
    coord_value = related_motion->unk_08.half.unk_0A.s16;
    state6_target_base += 0x40;
    height_numerator = (coord_value - state6_target_base) << 0x10;
    height_frames = 16;
    motion->unk_14.word = height_numerator / height_frames;
    effect->unk_9A = 0x3CU;
    goto block_122;
block_121:
    effect->unk_38 = (u16) (effect->unk_38 + 0x80);
block_122:
    motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
    motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
block_123:
    motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
    motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
    motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
    goto block_128;
jt_c16:
    fade_speed_x = motion->unk_0C.word;
    fade_speed_y = motion->unk_10.word;
    motion->unk_0C.word = (s32) (fade_speed_x - (fade_speed_x >> 3));
    motion->unk_10.word = (s32) (fade_speed_y - (fade_speed_y >> 3));
    if ((effect->unk_3E - 0x10) >= (s16) motion->unk_08.half.unk_0A.u16) {
        goto block_126;
    }
    motion->unk_08.half.unk_0A.u16 = (u16) ((u16) effect->unk_3E - 0x10);
block_126:
    motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
    motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
    motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
    fade_red = visual->unk_0C.half.unk_0C;
    visual->unk_0C.half.unk_0C = (u8) (fade_red - ((s32) fade_red / (s16) effect->unk_8A));
    fade_green = visual->unk_0C.half.unk_0D;
    visual->unk_0C.half.unk_0D = (u8) (fade_green - ((s32) fade_green / (s16) effect->unk_8A));
    fade_blue = visual->unk_0C.half.unk_0E;
    visual->unk_0C.half.unk_0E = (u8) (fade_blue - ((s32) fade_blue / (s16) effect->unk_8A));
    fade_ticks = effect->unk_8A - 1;
    effect->unk_8A = fade_ticks;
    if ((fade_ticks << 0x10) > 0) {
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
    visual->unk_1A = (u16) (func_800A07D0(0, 0, motion->unk_0C.half.unk_0E, motion->unk_10.half.unk_12) - 0x400);
    common_speed = motion->unk_14.half.unk_16;
    ASM_KEEP(common_speed);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    visual_scale = visual->unk_1C;
    red = visual->unk_0C.half.unk_0C;
    ASM_KEEP(visual_scale);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(red);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    aim_angle = common_speed * 4;
    common_pitch = aim_angle + 0x400;
    visual->unk_16 = (u16) common_pitch;
    common_pitch = 0x2000;
    common_pitch -= visual_scale;
    common_pitch >>= 2;
    visual_scale += common_pitch;
    red += 8;
    visual->unk_0C.half.unk_0C = red;
    visual->unk_1C = (u16) visual_scale;
    visual->unk_20 = (u16) visual_scale;
    visual->unk_1E = (u16) visual_scale;
    if ((u32) (red & 0xFF) < 0x81U) {
        goto block_131;
    }
    visual->unk_0C.word = 0x808080;
    goto block_132;
block_131:
    visual->unk_0C.half.unk_0D = (u8) (visual->unk_0C.half.unk_0D + 8);
    visual->unk_0C.half.unk_0E = (u8) (visual->unk_0C.half.unk_0E + 8);
block_132:
    func_80026694((u8 *) effect - 0x20, motion, 8, 0x300);
    func_800262F4(visual, (u8 *) effect + 0x36, effect->unk_3C, effect->unk_3A);
    func_80026240(effect, visual->unk_00);
    frame = visual->unk_04;
    if ((s8) frame != effect->unk_3A) {
        goto block_134;
    }
    frame_step = -1;
    goto block_136;
block_134:
    if ((s8) frame != effect->unk_3C) {
        goto block_137;
    }
    frame_step = 1;
block_136:
    effect->unk_36 = frame_step;
block_137:
    func_8002470C((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16, (s16) motion->unk_08.half.unk_0A.u16, (s16) effect->unk_38, D_80026BD4[(s8) visual->unk_04]);
    goto block_145;
block_138:
    heading_or_owner = owner_ref | 0x80000000;
    if (!(((S_819835AC_8 *) heading_or_owner)->unk_1E & 0x8000)) {
        goto block_140;
    }
block_139:
    ((S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E = (u16) (((S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_819835AC_12 *) &D_800814A0)->unk_00 | 0x8000);
    return;
block_140:
    actor_data = ((S_819835AC_8 *) heading_or_owner)->unk_0C;
    related_motion = ((S_819835AC_8 *) heading_or_owner)->unk_08;
    if (!(owner_ref & 0x80000000)) {
        goto block_142;
    }
    owner_state = heading_or_owner + 0x20;
    visual->unk_1A = (u16) (func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16, related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16) - 0x400);
    alternate_delta = related_motion->unk_08.half.unk_0A.s16;
    coord_value = motion->unk_08.half.unk_0A.s16;
    alternate_delta -= coord_value;
    alternate_scale = alternate_delta << 2;
    alternate_scale += alternate_delta;
    aim_angle = alternate_scale << 1;
    common_pitch = aim_angle + 0x400;
    visual->unk_16 = (u16) common_pitch;
    visual->unk_14 = (u16) actor_data->unk_14;
    motion->unk_00.half.unk_02.u16 = (u16) owner_state->unk_50;
    motion->unk_04.half.unk_06.u16 = (u16) owner_state->unk_52;
    motion->unk_08.half.unk_0A.u16 = (u16) owner_state->unk_54;
    goto block_143;
block_142:
    motion->unk_00.half.unk_02.u16 = (u16) related_motion->unk_00.half.unk_02.s16;
    motion->unk_04.half.unk_06.u16 = (u16) related_motion->unk_04.half.unk_06.s16;
    motion->unk_08.half.unk_0A.u16 = (u16) related_motion->unk_08.half.unk_0A.s16;
    visual->unk_16 = (u16) actor_data->unk_16;
    visual->unk_18 = (u16) actor_data->unk_18;
    visual->unk_1A = (u16) actor_data->unk_1A;
    visual->unk_14 = (u16) actor_data->unk_14;
block_143:
    visual->unk_1C = (u16) actor_data->unk_1C;
    visual->unk_1E = (u16) actor_data->unk_1E;
    visual->unk_20 = (u16) actor_data->unk_20;
    visual->unk_0C.word = actor_data->unk_0C;
    if (D_80026BC8[effect->unk_88] == 0) {
        goto block_145;
    }
    func_800263C0(visual, actor_data->unk_04);
    func_80026240(effect, visual->unk_00);
block_145:
    effect->unk_94 = (u16) (effect->unk_94 + 1);
block_146:
    return;
}
