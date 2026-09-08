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

/* Update a homing effect's movement, target hits, appearance, and attached copies. */
void func_80024DAC(void *effect, void *motion, void *visual) {
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
    s32 height_frames;
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
    void *owner_state;
    void *actor_data;
    void *related_motion;
    void *new_target;
    void *target;
    register void *history ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    void *hit_actor;
    M2C_UNK *state0_move;
    void *state0_actor;
    void *state0_height_actor;
    register s32 side_component ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 state0_delta_x;
    s32 state0_delta_y;
    register s32 coord_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 coord_delta ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 step_y;
    s32 step_z;
    void *state1_global;
    s32 target_coord;
    M2C_UNK *state1_move;
    void *state1_actor;
    void *state2_stage;
    register void *list_sentinel ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
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
    history = effect;
    (*(s16 *)&D_800269F8) = (s16) (M2C_FIELD(&D_800269F8, u16 *, 0) + 1);
copy_history:
    {
        s32 history_xy;
        s32 history_z_pad;

        history_xy = M2C_FIELD(history, M2C_PACKED_PAIR *, 0x48).a;
        history_z_pad = M2C_FIELD(history, M2C_PACKED_PAIR *, 0x48).b;
        M2C_FIELD(history, M2C_PACKED_PAIR *, 0x50).a = history_xy;
        M2C_FIELD(history, M2C_PACKED_PAIR *, 0x50).b = history_z_pad;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    history_index -= 1;
    history -= 8;
    if (history_index >= 0) {
        goto copy_history;
    }
    owner_ref = M2C_FIELD(effect, s32 *, 0x20);
    M2C_FIELD(effect, u16 *, 0x48) = (u16) M2C_FIELD(motion, u16 *, 2);
    M2C_FIELD(effect, u16 *, 0x4A) = (u16) M2C_FIELD(motion, u16 *, 6);
    M2C_FIELD(effect, u16 *, 0x4C) = (u16) M2C_FIELD(motion, u16 *, 0xA);
    if (owner_ref != 0) {
        goto block_138;
    }
    state = M2C_FIELD(effect, s16 *, 0x30);
    if ((u32) state >= 0x11U) {
        goto block_128;
    }
    (void)state_labels; goto *D_80024020[(u32)(state)];
jt_c0:
    func_8003DE58(*(M2C_UNK *)((((s32) (D_80083228 + M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x2A) + 0x100) >> 7) & 0x1C) + D_800E3D18), &D_80082E80, effect + 0x28, 0);
    heading_or_owner = func_80064584(M2C_FIELD((*(void **)&D_800E3D7C), s16 *, 0x2A));
    side_component = func_80064584(M2C_FIELD((*(void **)&D_800E3D7C), s16 *, 0x2A) - 0x400);
    state0_move = &D_80083780;
    ASM_KEEP(state0_move);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    heading_or_owner >>= 4;
    state0_delta_x = M2C_FIELD(state0_move, u16 *, 2);
    side_component >>= 4;
    state0_delta_x -= heading_or_owner;
    state0_delta_x += side_component;
    coord_value = M2C_FIELD(effect, u16 *, 0x28);
    state0_actor = M2C_FIELD(&D_800E3D7C, void **, 0);
    coord_value += state0_delta_x;
    M2C_FIELD(effect, u16 *, 0x28) = (u16) coord_value;
    heading_or_owner = func_800644B8(M2C_FIELD(state0_actor, s16 *, 0x2A));
    side_component = func_800644B8(M2C_FIELD((*(void **)&D_800E3D7C), s16 *, 0x2A) - 0x400);
    heading_or_owner >>= 4;
    side_component >>= 4;
    state0_delta_y = M2C_FIELD(state0_move, u16 *, 6);
    coord_delta = M2C_FIELD(effect, u16 *, 0x2A);
    state0_delta_y -= heading_or_owner;
    state0_delta_y += side_component;
    state0_height_actor = M2C_FIELD(&D_800E3D7C, void **, 0);
    coord_delta += state0_delta_y;
    M2C_FIELD(effect, u16 *, 0x2A) = (u16) coord_delta;
    coord_delta = M2C_FIELD(effect, u16 *, 0x2C);
    step_y = M2C_FIELD(state0_height_actor, u16 *, 0x88);
    approach_frames = 0x10U;
    M2C_FIELD(effect, u16 *, 0x34) = approach_frames;
    coord_delta -= 0x50;
    step_y += coord_delta;
    M2C_FIELD(effect, u16 *, 0x2C) = (u16) step_y;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    height_numerator = (M2C_FIELD(effect, s16 *, 0x2C) - M2C_FIELD(motion, s16 *, 0xA)) << 0x10;
    height_frames = 16;
    ASM_KEEP(height_frames);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(motion, s32 *, 0x14) = height_numerator / height_frames;
    M2C_FIELD(effect, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(effect, s16 *, 0x30) + 1);
jt_c1:
    aim_angle = func_800A07D0((s16) M2C_FIELD(motion, u16 *, 2), (s16) M2C_FIELD(motion, u16 *, 6), (s16) M2C_FIELD(effect, u16 *, 0x28), (s16) M2C_FIELD(effect, u16 *, 0x2A));
    approach_heading = M2C_FIELD(effect, u16 *, 0x38);
    if (approach_heading & 0x800) {
        approach_signed_angle = approach_heading | 0xF800;
    } else {
        approach_signed_angle = approach_heading & 0x7FF;
    }
block_8:
    M2C_FIELD(effect, u16 *, 0x38) = approach_signed_angle;
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
    approach_wrap_gap = (s16) M2C_FIELD(effect, u16 *, 0x38) - aim_angle;
    if (approach_wrap_gap >= 0) {
        goto block_13;
    }
    approach_wrap_gap = 0 - approach_wrap_gap;
block_13:
    if (approach_wrap_gap < 0x801) {
        goto block_15;
    }
    M2C_FIELD(effect, u16 *, 0x38) = (u16) ((aim_angle & ~0xFFF) | (M2C_FIELD(effect, u16 *, 0x38) & 0xFFF));
block_15:
    approach_angle = (s16) M2C_FIELD(effect, u16 *, 0x38);
    approach_turn_gap = aim_angle - approach_angle;
    if (approach_turn_gap >= 0) {
        goto block_17;
    }
    approach_turn_gap = 0 - approach_turn_gap;
block_17:
    if (approach_turn_gap < 0x81) {
        goto block_21;
    }
    if (M2C_FIELD(effect, s16 *, 0x96) != 0) {
        approach_next_angle = approach_angle + 0x80;
    } else {
        approach_next_angle = approach_angle - 0x80;
    }
    M2C_FIELD(effect, u16 *, 0x38) = approach_next_angle;
    goto block_22;
block_21:
    M2C_FIELD(effect, u16 *, 0x38) = aim_angle;
block_22:
    M2C_FIELD(motion, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    approach_ticks = M2C_FIELD(effect, u16 *, 0x34) - 1;
    M2C_FIELD(effect, u16 *, 0x34) = approach_ticks;
    if ((approach_ticks << 0x10) > 0) {
        goto block_24;
    }
    M2C_FIELD(motion, u16 *, 0xA) = (u16) M2C_FIELD(effect, u16 *, 0x2C);
    M2C_FIELD(effect, u16 *, 0x34) = 0U;
    M2C_FIELD(motion, s32 *, 0x14) = 0;
block_24:
    state1_global = M2C_FIELD(&D_800814A8, void **, 0);
    M2C_FIELD(state1_global, s16 *, 0x96) = 2;
    coord_value = M2C_FIELD(motion, s32 *, 0);
    coord_delta = M2C_FIELD(motion, s32 *, 0xC);
    step_y = M2C_FIELD(motion, s32 *, 0x10);
    step_z = M2C_FIELD(motion, s32 *, 0x14);
    coord_value += coord_delta;
    M2C_FIELD(motion, s32 *, 0) = coord_value;
    coord_value = M2C_FIELD(motion, s32 *, 4);
    coord_delta = M2C_FIELD(motion, s32 *, 8);
    coord_value += step_y;
    M2C_FIELD(motion, s32 *, 4) = coord_value;
    approach_gap_x = M2C_FIELD(motion, s16 *, 2);
    coord_delta += step_z;
    M2C_FIELD(motion, s32 *, 8) = coord_delta;
    approach_gap_x -= M2C_FIELD(effect, s16 *, 0x28);
    if (__builtin_abs(approach_gap_x) >= 0x40) {
        goto block_129;
    }
    approach_gap_y = M2C_FIELD(motion, s16 *, 6);
    target_coord = M2C_FIELD(effect, s16 *, 0x2A);
    approach_gap_y -= target_coord;
    if (__builtin_abs(approach_gap_y) >= 0x40) {
        goto block_129;
    }
    approach_gap_z = M2C_FIELD(motion, s16 *, 0xA);
    target_coord = M2C_FIELD(effect, s16 *, 0x2C);
    approach_gap_z -= target_coord;
    if (__builtin_abs(approach_gap_z) >= 0x40) {
        goto block_129;
    }
    func_8003DE58(*(M2C_UNK *)((((s32) (D_80083228 + M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x2A) + 0x100) >> 7) & 0x1C) + D_800E3D18), &D_80082E80, effect + 0x28, 0);
    state1_move = &D_80083780;
    coord_value = M2C_FIELD(effect, u16 *, 0x28);
    coord_delta = M2C_FIELD(state1_move, u16 *, 2);
    coord_value += coord_delta;
    M2C_FIELD(effect, u16 *, 0x28) = coord_value;
    coord_value = M2C_FIELD(effect, u16 *, 0x2A);
    coord_delta = M2C_FIELD(state1_move, u16 *, 6);
    state1_actor = M2C_FIELD(&D_800814A8, void **, 0);
    coord_value += coord_delta;
    M2C_FIELD(effect, u16 *, 0x2A) = coord_value;
    coord_delta = M2C_FIELD(effect, u16 *, 0x2C);
    coord_value = M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), u16 *, 0x88);
    coord_delta -= 0x50;
    coord_value += coord_delta;
    M2C_FIELD(effect, u16 *, 0x2C) = coord_value;
    coord_value = M2C_FIELD(state1_actor, u16 *, 0xA6) - 1;
    M2C_FIELD(state1_actor, u16 *, 0xA6) = coord_value;
    M2C_FIELD(effect, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(effect, s16 *, 0x30) + 1);
    goto block_128;
jt_c2:
    aim_angle = func_800A07D0((s16) M2C_FIELD(motion, u16 *, 2), (s16) M2C_FIELD(motion, u16 *, 6), (s16) M2C_FIELD(effect, u16 *, 0x28), (s16) M2C_FIELD(effect, u16 *, 0x2A));
    travel_heading = M2C_FIELD(effect, u16 *, 0x38);
    if (travel_heading & 0x800) {
        travel_signed_angle = travel_heading | 0xF800;
    } else {
        travel_signed_angle = travel_heading & 0x7FF;
    }
block_36:
    M2C_FIELD(effect, u16 *, 0x38) = travel_signed_angle;
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
    travel_wrap_gap = (s16) M2C_FIELD(effect, u16 *, 0x38) - aim_angle;
    if (travel_wrap_gap >= 0) {
        goto block_41;
    }
    travel_wrap_gap = 0 - travel_wrap_gap;
block_41:
    if (travel_wrap_gap < 0x801) {
        goto block_43;
    }
    M2C_FIELD(effect, u16 *, 0x38) = (u16) ((aim_angle & ~0xFFF) | (M2C_FIELD(effect, u16 *, 0x38) & 0xFFF));
block_43:
    travel_angle = (s16) M2C_FIELD(effect, u16 *, 0x38);
    travel_turn_gap = aim_angle - travel_angle;
    if (travel_turn_gap >= 0) {
        goto block_45;
    }
    travel_turn_gap = 0 - travel_turn_gap;
block_45:
    if (travel_turn_gap < 0x81) {
        goto block_49;
    }
    if (M2C_FIELD(effect, s16 *, 0x96) != 0) {
        travel_next_angle = travel_angle + 0x80;
    } else {
        travel_next_angle = travel_angle - 0x80;
    }
    M2C_FIELD(effect, u16 *, 0x38) = travel_next_angle;
    goto block_50;
block_49:
    M2C_FIELD(effect, u16 *, 0x38) = aim_angle;
block_50:
    M2C_FIELD(motion, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    travel_ticks = M2C_FIELD(effect, u16 *, 0x34) - 1;
    M2C_FIELD(effect, u16 *, 0x34) = travel_ticks;
    if ((travel_ticks << 0x10) > 0) {
        goto block_52;
    }
    M2C_FIELD(motion, u16 *, 0xA) = (u16) M2C_FIELD(effect, u16 *, 0x2C);
    M2C_FIELD(effect, u16 *, 0x34) = 0U;
    M2C_FIELD(motion, s32 *, 0x14) = 0;
block_52:
    coord_value = M2C_FIELD(motion, s32 *, 0);
    coord_delta = M2C_FIELD(motion, s32 *, 0xC);
    step_y = M2C_FIELD(motion, s32 *, 0x10);
    step_z = M2C_FIELD(motion, s32 *, 0x14);
    coord_value += coord_delta;
    M2C_FIELD(motion, s32 *, 0) = coord_value;
    coord_value = M2C_FIELD(motion, s32 *, 4);
    coord_delta = M2C_FIELD(motion, s32 *, 8);
    coord_value += step_y;
    coord_delta += step_z;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    M2C_FIELD(motion, s32 *, 4) = coord_value;
    state2_stage = M2C_FIELD(&D_800814A8, void **, 0);
    M2C_FIELD(motion, s32 *, 8) = coord_delta;
    M2C_FIELD(state2_stage, s16 *, 0x96) = 2;
    travel_gap_x = M2C_FIELD(motion, s16 *, 2);
    target_coord = M2C_FIELD(effect, s16 *, 0x28);
    travel_gap_x -= target_coord;
    if (travel_gap_x >= 0) {
        goto block_54;
    }
    travel_gap_x = 0 - travel_gap_x;
block_54:
    if (travel_gap_x >= 0x20) {
        goto block_128;
    }
    travel_gap_y = M2C_FIELD(motion, s16 *, 6);
    target_coord = M2C_FIELD(effect, s16 *, 0x2A);
    travel_gap_y -= target_coord;
    if (travel_gap_y >= 0) {
        goto block_57;
    }
    travel_gap_y = 0 - travel_gap_y;
block_57:
    if (travel_gap_y >= 0x20) {
        goto block_128;
    }
    M2C_FIELD(effect, u16 *, 0x34) = 4U;
    state2_actor = M2C_FIELD(&D_800E3D7C, void **, 0);
    M2C_FIELD(effect, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(effect, s16 *, 0x30) + 1);
    M2C_FIELD(M2C_FIELD(&D_800814A8, void **, 0), s16 *, 0x96) = 0;
    M2C_FIELD(effect, u16 *, 0x38) = (u16) M2C_FIELD(state2_actor, s16 *, 0x2A);
    state2_angle = M2C_FIELD(state2_actor, u16 *, 0x2A);
    D_80026B28 = 0;
    M2C_FIELD(effect, u16 *, 0x44) = (u16) ((state2_angle >> 9) & 7);
    goto block_128;
jt_c3:
jt_c4:
    state34_base = &D_80082E80;
    if (func_8003DE58(M2C_FIELD(state34_base, s32 *, 8), state34_base, &emit_offset, 0) == 0) {
        goto block_63;
    }
    if (M2C_FIELD(effect, s16 *, 0x30) != 3) {
        goto block_62;
    }
    state34_move = &D_80083780;
    func_800B8D64(M2C_FIELD(state34_move, s16 *, 2) + emit_offset.x, M2C_FIELD(state34_move, s16 *, 6) + emit_offset.y, M2C_FIELD(state34_move, s16 *, 0xA) + emit_offset.z);
    M2C_FIELD(effect, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(effect, s16 *, 0x30) + 1);
block_62:
    state34_emit = &D_80083780;
    func_80024B2C((s16) (M2C_FIELD(state34_emit, u16 *, 2) + (u16) emit_offset.x), (s16) (M2C_FIELD(state34_emit, u16 *, 6) + (u16) emit_offset.y), (s16) (M2C_FIELD(state34_emit, u16 *, 0xA) + (u16) emit_offset.z), M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x2A), 0);
block_63:
    M2C_FIELD(motion, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s16 *, 0x16) = 0x16;
    rise_speed = M2C_FIELD(motion, s32 *, 0x14);
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    M2C_SFIELD(motion, 8) = (s32) (M2C_FIELD(motion, s32 *, 8) + M2C_FIELD(motion, s32 *, 0x14));
    if ((s16) M2C_FIELD(motion, u16 *, 0xA) <= M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x88)) {
        goto block_65;
    }
    M2C_FIELD(motion, u16 *, 0xA) = (u16) M2C_FIELD(M2C_FIELD(&D_800E3D7C, void **, 0), s16 *, 0x88);
block_65:
    launch_ticks = M2C_FIELD(effect, u16 *, 0x34) - 1;
    M2C_FIELD(effect, u16 *, 0x34) = launch_ticks;
    if ((launch_ticks << 0x10) > 0) {
        goto block_129;
    }
    tile_base = &D_80082E80;
    tile_coord = M2C_FIELD(tile_base, u8 *, 0x24);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    tile_call_arg = 0x300;
    ASM_KEEP(tile_call_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(effect, s16 *, 0x40) = (s16) tile_coord;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    M2C_FIELD(effect, u8 *, 0x98) = (u8) tile_coord;
    tile_coord = M2C_FIELD(tile_base, u8 *, 0x25);
    M2C_FIELD(effect, s16 *, 0x30) = 5;
    M2C_FIELD(effect, u16 *, 0x46) = 3U;
    M2C_FIELD(effect, u16 *, 0x34) = 0U;
    M2C_FIELD(effect, s16 *, 0x42) = (s16) tile_coord;
    M2C_FIELD(effect, u8 *, 0x99) = (u8) tile_coord;
    func_800A56E0(tile_call_arg, rise_speed);
    goto block_129;
jt_c5:
    M2C_FIELD(motion, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s32 *, 0x14) = 0;
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    world_x = M2C_FIELD(motion, s16 *, 2);
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    M2C_FIELD(motion, s32 *, 8) = (s32) (M2C_FIELD(motion, s32 *, 8) + M2C_FIELD(motion, s32 *, 0x14));
    if (world_x >= 0) {
        goto block_69;
    }
    world_x += 0x3F;
block_69:
    tile_div = world_x >> 6;
    M2C_FIELD(effect, s16 *, 0x40) = (s16) tile_div;
    world_y = M2C_FIELD(motion, s16 *, 6);
    if (world_y >= 0) {
        goto block_71;
    }
    world_y += 0x3F;
block_71:
    next_tile_y = world_y >> 6;
    M2C_FIELD(effect, s16 *, 0x42) = (s16) next_tile_y;
    if (M2C_FIELD(effect, u8 *, 0x98) != M2C_FIELD(effect, s16 *, 0x40)) {
        goto block_73;
    }
    if (M2C_FIELD(effect, u8 *, 0x99) == next_tile_y) {
        goto block_129;
    }
block_73:
    hit_actor = M2C_FIELD(&D_800814A8, void **, 0);
    list_sentinel = hit_actor;
    hit_actor = M2C_FIELD(hit_actor, s32 *, 0x5C) + 0x20;
    if (hit_actor != list_sentinel) {
        do {
            actor_data = M2C_FIELD(hit_actor, void **, -0x14);
            if ((M2C_FIELD(actor_data, u8 *, 0x24) == M2C_FIELD(effect, s16 *, 0x40)) &&
                (M2C_FIELD(actor_data, u8 *, 0x25) == M2C_FIELD(effect, s16 *, 0x42))) {
                hit_height_gap = M2C_FIELD(hit_actor, s16 *, 0x88);
                target_coord = M2C_FIELD(motion, s16 *, 0xA);
                hit_height_gap -= target_coord;
                if (hit_height_gap < 0) {
                    hit_height_gap = -hit_height_gap;
                }
                actor_data = hit_actor - 0x20;
                if ((hit_height_gap < 0x80) && !(M2C_FIELD(actor_data, u16 *, 0x1E) & 0x2000)) {
                    func_8009CE1C(hit_actor, 0xC, D_80027C96, 0xA, (s32) (s16) (M2C_FIELD(effect, u16 *, 0x44) << 9), D_80027C98, 2);
                    related_motion = M2C_FIELD(hit_actor, void **, -0x18);
                    func_80024938(M2C_FIELD(related_motion, s16 *, 2), M2C_FIELD(related_motion, s16 *, 6), M2C_FIELD(related_motion, s16 *, 0xA), (s16) M2C_FIELD(effect, u16 *, 0x38), (func_80069EF8() & 3) | 4);
                    M2C_FIELD(actor_data, u16 *, 0x1E) = (u16) (M2C_FIELD(actor_data, u16 *, 0x1E) | 0x2000);
                }
            }
            coord_delta = M2C_FIELD(hit_actor, s32 *, 0x5C);
            hit_actor = coord_delta + 0x20;
        } while (hit_actor != M2C_FIELD(&D_800814A8, void **, 0));
    }
block_83:
    tile_x = (u8) M2C_FIELD(effect, s16 *, 0x40);
    tile_counter = M2C_FIELD(effect, u16 *, 0x46);
    tile_y = (u8) M2C_FIELD(effect, s16 *, 0x42);
    tile_counter -= 1;
    M2C_FIELD(effect, u16 *, 0x46) = tile_counter;
    M2C_FIELD(effect, u8 *, 0x98) = tile_x;
    M2C_FIELD(effect, u8 *, 0x99) = tile_y;
    if ((tile_counter << 0x10) > 0) {
        goto block_128;
    }
    M2C_FIELD(effect, u16 *, 0x8A) = (u16) ((func_80069EF8() & 0x1F) + 0x10);
    M2C_FIELD(effect, void **, 0x9C) = NULL;
    M2C_FIELD(effect, s16 *, 0x30) = (s16) ((u16) M2C_FIELD(effect, s16 *, 0x30) + 1);
    goto block_128;
jt_c6:
    target = M2C_FIELD(effect, void **, 0x9C);
    if (target == NULL) {
        goto block_117;
    }
    related_motion = M2C_FIELD(target, void **, -0x18);
    aim_angle = func_800A07D0((s16) M2C_FIELD(motion, u16 *, 2), (s16) M2C_FIELD(motion, u16 *, 6), M2C_FIELD(related_motion, s16 *, 2), M2C_FIELD(related_motion, s16 *, 6));
    homing_heading = M2C_FIELD(effect, u16 *, 0x38);
    if (homing_heading & 0x800) {
        homing_signed_angle = homing_heading | 0xF800;
    } else {
        homing_signed_angle = homing_heading & 0x7FF;
    }
block_88:
    M2C_FIELD(effect, u16 *, 0x38) = homing_signed_angle;
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
    homing_wrap_gap = (s16) M2C_FIELD(effect, u16 *, 0x38) - aim_angle;
    if (homing_wrap_gap >= 0) {
        goto block_93;
    }
    homing_wrap_gap = 0 - homing_wrap_gap;
block_93:
    if (homing_wrap_gap < 0x801) {
        goto block_95;
    }
    M2C_FIELD(effect, u16 *, 0x38) = (u16) ((aim_angle & ~0xFFF) | (M2C_FIELD(effect, u16 *, 0x38) & 0xFFF));
block_95:
    aim_ticks = M2C_FIELD(effect, u16 *, 0x9A) - 1;
    M2C_FIELD(effect, u16 *, 0x9A) = aim_ticks;
    if ((aim_ticks << 0x10) > 0) {
        goto block_97;
    }
    M2C_FIELD(effect, u16 *, 0x9A) = 0x1EU;
    M2C_FIELD(effect, u16 *, 0x38) = aim_angle;
block_97:
    homing_angle = (s16) M2C_FIELD(effect, u16 *, 0x38);
    homing_turn_gap = aim_angle - homing_angle;
    if (homing_turn_gap >= 0) {
        goto block_99;
    }
    homing_turn_gap = 0 - homing_turn_gap;
block_99:
    if (homing_turn_gap < 0x81) {
        goto block_103;
    }
    if (M2C_FIELD(effect, s16 *, 0x96) != 0) {
        homing_next_angle = homing_angle + 0x80;
    } else {
        homing_next_angle = homing_angle - 0x80;
    }
    M2C_FIELD(effect, u16 *, 0x38) = homing_next_angle;
    goto block_104;
block_103:
    M2C_FIELD(effect, u16 *, 0x38) = aim_angle;
block_104:
    state6_timer_signed = M2C_FIELD(effect, s16 *, 0x34);

    state6_timer = M2C_FIELD(effect, u16 *, 0x34);
    if (state6_timer_signed == 0) {
        goto block_107;
    }
    state6_next = state6_timer - 1;
    M2C_FIELD(effect, u16 *, 0x34) = state6_next;
    if ((state6_next << 0x10) != 0) {
        goto block_108;
    }
    state6_height = M2C_FIELD(related_motion, u16 *, 0xA);
    M2C_FIELD(motion, s32 *, 0x14) = 0;
    state6_height -= 0x40;
    M2C_FIELD(motion, u16 *, 0xA) = state6_height;
    M2C_FIELD(effect, u16 *, 0x8A) = 0U;
    goto block_108;
block_107:
    bob_phase = M2C_FIELD(effect, u16 *, 0x8A) + 1;
    state6_spin_arg = (s32) (bob_phase << 0x10);

    state6_spin_arg >>= 9;
    M2C_FIELD(effect, u16 *, 0x8A) = bob_phase;
    M2C_FIELD(motion, s16 *, 0x16) = (s16) (func_800644B8(state6_spin_arg) >> 9);
block_108:
    target_gap_x = M2C_FIELD(motion, s16 *, 2);
    target_coord = M2C_FIELD(related_motion, s16 *, 2);
    target_gap_x -= target_coord;
    if (target_gap_x >= 0) {
        goto block_110;
    }
    target_gap_x = 0 - target_gap_x;
block_110:
    if (target_gap_x >= 0x20) {
        goto block_115;
    }
    target_gap_y = M2C_FIELD(motion, s16 *, 6);
    target_coord = M2C_FIELD(related_motion, s16 *, 6);
    target_gap_y -= target_coord;
    if (target_gap_y >= 0) {
        goto block_113;
    }
    target_gap_y = 0 - target_gap_y;
block_113:
    if (target_gap_y >= 0x20) {
        goto block_115;
    }
    actor_data = M2C_FIELD(effect, void **, 0x9C) - 0x20;
    func_8009CE1C(M2C_FIELD(effect, void **, 0x9C), 0xC, D_80027C96, 0xA, (s32) (s16) (M2C_FIELD(effect, u16 *, 0x44) << 9), D_80027C98, 2);
    func_800A56E0(0x300);
    func_80024938(M2C_FIELD(related_motion, s16 *, 2), M2C_FIELD(related_motion, s16 *, 6), (s16) M2C_FIELD(related_motion, u16 *, 0xA), (s16) M2C_FIELD(effect, u16 *, 0x38), (func_80069EF8() & 3) | 4);
    M2C_FIELD(actor_data, u16 *, 0x1E) = (u16) (M2C_FIELD(actor_data, u16 *, 0x1E) | 0x2000);
    M2C_FIELD(effect, void **, 0x9C) = NULL;
    M2C_FIELD(effect, u16 *, 0x8A) = (u16) ((func_80069EF8() & 0x1F) + 0x10);
block_115:
    state6_velocity = func_80064584((s16) M2C_FIELD(effect, u16 *, 0x38));

    state6_velocity <<= 8;
    M2C_FIELD(motion, s32 *, 0xC) = state6_velocity;
    state6_velocity = func_800644B8((s16) M2C_FIELD(effect, u16 *, 0x38));

    state6_velocity <<= 8;
    ASM_KEEP(state6_velocity);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(motion, s32 *, 0x10) = state6_velocity;

    if ((s16) M2C_FIELD(effect, u16 *, 0x38) != aim_angle) {
        goto block_123;
    }
    boost_speed_x = M2C_FIELD(motion, s32 *, 0xC);
    boost_speed_y = M2C_FIELD(motion, s32 *, 0x10);
    step_y = boost_speed_x >> 1;
    boost_speed_x += step_y;
    M2C_FIELD(motion, s32 *, 0xC) = boost_speed_x;
    coord_value = boost_speed_y >> 1;
    boost_speed_y += coord_value;
    M2C_FIELD(motion, s32 *, 0x10) = boost_speed_y;
    goto block_123;
block_117:
    M2C_FIELD(motion, s32 *, 0x14) = 0;
    search_ticks = M2C_FIELD(effect, u16 *, 0x8A) - 1;
    M2C_FIELD(effect, u16 *, 0x8A) = search_ticks;
    if ((search_ticks << 0x10) > 0) {
        goto block_121;
    }
    new_target = func_80026444(&D_80082E80);
    M2C_FIELD(effect, void **, 0x9C) = new_target;
    if (new_target != NULL) {
        goto block_120;
    }
    M2C_FIELD(effect, s16 *, 0x30) = 0x10;
    M2C_FIELD(effect, u16 *, 0x8A) = 8U;
    goto block_122;
block_120:
    related_motion = M2C_FIELD(new_target, void **, -0x18);
    M2C_FIELD(effect, u16 *, 0x34) = 0x10U;
    state6_target_base = M2C_FIELD(motion, s16 *, 0xA);
    coord_value = M2C_FIELD(related_motion, s16 *, 0xA);
    state6_target_base += 0x40;
    height_numerator = (coord_value - state6_target_base) << 0x10;
    height_frames = 16;
    ASM_KEEP(height_frames);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    M2C_FIELD(motion, s32 *, 0x14) = height_numerator / height_frames;
    M2C_FIELD(effect, u16 *, 0x9A) = 0x3CU;
    goto block_122;
block_121:
    M2C_FIELD(effect, u16 *, 0x38) = (u16) (M2C_FIELD(effect, u16 *, 0x38) + 0x80);
block_122:
    M2C_FIELD(motion, s32 *, 0xC) = (s32) (func_80064584((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
    M2C_FIELD(motion, s32 *, 0x10) = (s32) (func_800644B8((s16) M2C_FIELD(effect, u16 *, 0x38)) << 8);
block_123:
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    M2C_FIELD(motion, s32 *, 8) = (s32) (M2C_FIELD(motion, s32 *, 8) + M2C_FIELD(motion, s32 *, 0x14));
    goto block_128;
jt_c16:
    fade_speed_x = M2C_FIELD(motion, s32 *, 0xC);
    fade_speed_y = M2C_FIELD(motion, s32 *, 0x10);
    M2C_FIELD(motion, s32 *, 0xC) = (s32) (fade_speed_x - (fade_speed_x >> 3));
    M2C_FIELD(motion, s32 *, 0x10) = (s32) (fade_speed_y - (fade_speed_y >> 3));
    if ((M2C_FIELD(effect, s16 *, 0x3E) - 0x10) >= (s16) M2C_FIELD(motion, u16 *, 0xA)) {
        goto block_126;
    }
    M2C_FIELD(motion, u16 *, 0xA) = (u16) ((u16) M2C_FIELD(effect, s16 *, 0x3E) - 0x10);
block_126:
    M2C_FIELD(motion, s32 *, 0) = (s32) (M2C_FIELD(motion, s32 *, 0) + M2C_FIELD(motion, s32 *, 0xC));
    M2C_FIELD(motion, s32 *, 4) = (s32) (M2C_FIELD(motion, s32 *, 4) + M2C_FIELD(motion, s32 *, 0x10));
    M2C_FIELD(motion, s32 *, 8) = (s32) (M2C_FIELD(motion, s32 *, 8) + M2C_FIELD(motion, s32 *, 0x14));
    fade_red = M2C_FIELD(visual, u8 *, 0xC);
    M2C_FIELD(visual, u8 *, 0xC) = (u8) (fade_red - ((s32) fade_red / (s16) M2C_FIELD(effect, u16 *, 0x8A)));
    fade_green = M2C_FIELD(visual, u8 *, 0xD);
    M2C_FIELD(visual, u8 *, 0xD) = (u8) (fade_green - ((s32) fade_green / (s16) M2C_FIELD(effect, u16 *, 0x8A)));
    fade_blue = M2C_FIELD(visual, u8 *, 0xE);
    M2C_FIELD(visual, u8 *, 0xE) = (u8) (fade_blue - ((s32) fade_blue / (s16) M2C_FIELD(effect, u16 *, 0x8A)));
    fade_ticks = M2C_FIELD(effect, u16 *, 0x8A) - 1;
    M2C_FIELD(effect, u16 *, 0x8A) = fade_ticks;
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
    M2C_FIELD(visual, u16 *, 0x1A) = (u16) (func_800A07D0(0, 0, M2C_FIELD(motion, s16 *, 0xE), M2C_FIELD(motion, s16 *, 0x12)) - 0x400);
    common_speed = M2C_FIELD(motion, s16 *, 0x16);
    ASM_KEEP(common_speed);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    visual_scale = M2C_FIELD(visual, u16 *, 0x1C);
    red = M2C_FIELD(visual, u8 *, 0xC);
    ASM_KEEP(visual_scale);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(red);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    aim_angle = common_speed * 4;
    common_pitch = aim_angle + 0x400;
    M2C_FIELD(visual, u16 *, 0x16) = (u16) common_pitch;
    common_pitch = 0x2000;
    common_pitch -= visual_scale;
    common_pitch >>= 2;
    visual_scale += common_pitch;
    red += 8;
    M2C_FIELD(visual, u8 *, 0xC) = red;
    M2C_FIELD(visual, u16 *, 0x1C) = (u16) visual_scale;
    M2C_FIELD(visual, u16 *, 0x20) = (u16) visual_scale;
    M2C_FIELD(visual, u16 *, 0x1E) = (u16) visual_scale;
    if ((u32) (red & 0xFF) < 0x81U) {
        goto block_131;
    }
    M2C_FIELD(visual, s32 *, 0xC) = 0x808080;
    goto block_132;
block_131:
    M2C_FIELD(visual, u8 *, 0xD) = (u8) (M2C_FIELD(visual, u8 *, 0xD) + 8);
    M2C_FIELD(visual, u8 *, 0xE) = (u8) (M2C_FIELD(visual, u8 *, 0xE) + 8);
block_132:
    func_80026694(effect - 0x20, motion, 8, 0x300);
    func_800262F4(visual, effect + 0x36, M2C_FIELD(effect, s16 *, 0x3C), M2C_FIELD(effect, s16 *, 0x3A));
    func_80026240(effect, M2C_FIELD(visual, s32 *, 0));
    frame = M2C_FIELD(visual, u8 *, 4);
    if ((s8) frame != M2C_FIELD(effect, s16 *, 0x3A)) {
        goto block_134;
    }
    frame_step = -1;
    goto block_136;
block_134:
    if ((s8) frame != M2C_FIELD(effect, s16 *, 0x3C)) {
        goto block_137;
    }
    frame_step = 1;
block_136:
    M2C_FIELD(effect, s16 *, 0x36) = frame_step;
block_137:
    func_8002470C((s16) M2C_FIELD(motion, u16 *, 2), (s16) M2C_FIELD(motion, u16 *, 6), (s16) M2C_FIELD(motion, u16 *, 0xA), (s16) M2C_FIELD(effect, u16 *, 0x38), D_80026BD4[(s8) M2C_FIELD(visual, u8 *, 4)]);
    goto block_145;
block_138:
    heading_or_owner = owner_ref | 0x80000000;
    if (!(M2C_FIELD(heading_or_owner, u16 *, 0x1E) & 0x8000)) {
        goto block_140;
    }
block_139:
    M2C_FIELD(effect, u16 *, -2) = (u16) (M2C_FIELD(effect, u16 *, -2) | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (M2C_FIELD(&D_800814A0, s32 *, 0) | 0x8000);
    return;
block_140:
    actor_data = M2C_FIELD(heading_or_owner, void **, 0xC);
    related_motion = M2C_FIELD(heading_or_owner, void **, 8);
    if (!(owner_ref & 0x80000000)) {
        goto block_142;
    }
    owner_state = heading_or_owner + 0x20;
    M2C_FIELD(visual, u16 *, 0x1A) = (u16) (func_800A07D0((s16) M2C_FIELD(motion, u16 *, 2), (s16) M2C_FIELD(motion, u16 *, 6), M2C_FIELD(related_motion, s16 *, 2), M2C_FIELD(related_motion, s16 *, 6)) - 0x400);
    alternate_delta = M2C_FIELD(related_motion, s16 *, 0xA);
    coord_value = M2C_FIELD(motion, s16 *, 0xA);
    alternate_delta -= coord_value;
    alternate_scale = alternate_delta << 2;
    alternate_scale += alternate_delta;
    aim_angle = alternate_scale << 1;
    common_pitch = aim_angle + 0x400;
    M2C_FIELD(visual, u16 *, 0x16) = (u16) common_pitch;
    M2C_FIELD(visual, u16 *, 0x14) = (u16) M2C_FIELD(actor_data, u16 *, 0x14);
    M2C_FIELD(motion, u16 *, 2) = (u16) M2C_FIELD(owner_state, u16 *, 0x50);
    M2C_FIELD(motion, u16 *, 6) = (u16) M2C_FIELD(owner_state, u16 *, 0x52);
    M2C_FIELD(motion, u16 *, 0xA) = (u16) M2C_FIELD(owner_state, u16 *, 0x54);
    goto block_143;
block_142:
    M2C_FIELD(motion, u16 *, 2) = (u16) M2C_FIELD(related_motion, s16 *, 2);
    M2C_FIELD(motion, u16 *, 6) = (u16) M2C_FIELD(related_motion, s16 *, 6);
    M2C_FIELD(motion, u16 *, 0xA) = (u16) M2C_FIELD(related_motion, s16 *, 0xA);
    M2C_FIELD(visual, u16 *, 0x16) = (u16) M2C_FIELD(actor_data, u16 *, 0x16);
    M2C_FIELD(visual, u16 *, 0x18) = (u16) M2C_FIELD(actor_data, u16 *, 0x18);
    M2C_FIELD(visual, u16 *, 0x1A) = (u16) M2C_FIELD(actor_data, u16 *, 0x1A);
    M2C_FIELD(visual, u16 *, 0x14) = (u16) M2C_FIELD(actor_data, u16 *, 0x14);
block_143:
    M2C_FIELD(visual, u16 *, 0x1C) = (u16) M2C_FIELD(actor_data, u16 *, 0x1C);
    M2C_FIELD(visual, u16 *, 0x1E) = (u16) M2C_FIELD(actor_data, u16 *, 0x1E);
    M2C_FIELD(visual, u16 *, 0x20) = (u16) M2C_FIELD(actor_data, u16 *, 0x20);
    M2C_FIELD(visual, s32 *, 0xC) = M2C_FIELD(actor_data, s32 *, 0xC);
    if (D_80026BC8[M2C_FIELD(effect, s16 *, 0x88)] == 0) {
        goto block_145;
    }
    func_800263C0(visual, M2C_FIELD(actor_data, s8 *, 4));
    func_80026240(effect, M2C_FIELD(visual, s32 *, 0));
block_145:
    M2C_FIELD(effect, u16 *, 0x94) = (u16) (M2C_FIELD(effect, u16 *, 0x94) + 1);
block_146:
    return;
}
