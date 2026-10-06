#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
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
void *func_8002470C();     /* extern */
void *func_80024938();     /* extern */
void *func_80024B2C();     /* extern */
M2C_UNK func_80026240();                 /* extern */
M2C_UNK func_800262F4();    /* extern */
void func_800263C0();                  /* extern */
void *func_80026444();        /* extern */
M2C_UNK func_80026694(); /* extern */
s32 func_8003DE58();  /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                /* extern */
s32 func_80069EF8();                              /* extern */
void func_8009CE1C(); /* extern */
s16 func_800A07D0();              /* extern */
s32 func_800A56E0();                /* extern */
void func_800B8D64();               /* extern */
extern M2C_UNK D_800269F8;
extern s16 D_80026B28;
extern u8 D_80026BC8[];
extern u8 D_80026BD4[];
extern s16 D_80027C94;
extern u8 D_80027C96;
extern s32 D_80027C98;
extern void *D_800814A8;
extern s32 D_800E3D18;
extern M2C_UNK D_800E3D7C;

/* Update a homing effect's movement, target hits, appearance, and attached copies. */
void func_80024DAC(S_819835AC_1 *effect, S_819835AC_2 *motion, S_819835AC_3 *visual) {
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
    s32 owner_ptr;
    s32 sin_x;
    s32 sin_y;
    s32 sin_y_shift;
    s32 fade_speed_x;
    s32 boost_speed_x;
    s32 alternate_value;
    s32 height_value;
    s32 hit_origin;
    s32 cos_x;
    s32 cos_y;
    s32 owner_ref;
    s32 fade_speed_y;
    s16 height_frames;
    s32 height_numerator;
    s32 height_numerator_2;
    s32 history_index;
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
    s32 approach_gap_y;
    s32 approach_gap_z;
    s32 travel_wrap_gap;
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
    S_819835AC_9 *owner_state;
    S_819835AC_7 *actor_data;
    S_819835AC_2 *related_motion;
    S_819835AC_6 *new_target;
    S_819835AC_6 *target;
    S_819835AC_4 *history;
    S_819835AC_6 *hit_actor;
    EntityRec *state0_move;
    S_819835AC_5 *state0_actor;
    S_819835AC_5 *state0_height_actor;
    s32 state0_delta_x;
    s32 coord_delta;
    s32 step_y;
    s32 step_z;
    S_819835AC_6 *state1_global;
    s32 target_coord;
    EntityRec *state1_move;
    S_819835AC_6 *state1_actor;
    S_819835AC_6 *state2_stage;
    u8 tile_x;
    u16 tile_counter;
    u8 tile_y;
    s32 tile_div;
    TileObject *state34_base;
    EntityRec *state34_move;
    EntityRec *state34_emit;
    S_819835AC_5 *state2_actor;
    u32 state2_angle;
    TileObject *tile_base;
    u32 tile_coord;
    s32 tile_call_arg;
    s32 state6_timer_signed;
    u16 state6_timer;
    u16 state6_next;
    u16 state6_height;
    s32 state6_spin_arg;
    s32 state6_target_base;
    s32 alternate_delta;
    s32 alternate_scale;
    u16 approach_frames;

    (*(s16 *)&D_800269F8) = (s16) (((S_819835AC_10 *) &D_800269F8)->unk_00 + 1);
    for (history_index = 0; history_index >= 0; history_index--) {
        history = (S_819835AC_4 *) ((u8 *) effect + history_index * 8);
        history->unk_50 = history->unk_48;
    }
    owner_ref = effect->unk_20;
    effect->unk_48 = (u16) motion->unk_00.half.unk_02.u16;
    effect->unk_4A = (u16) motion->unk_04.half.unk_06.u16;
    effect->unk_4C = (u16) motion->unk_08.half.unk_0A.u16;
    if (owner_ref == 0) {
        state = effect->unk_30;
        switch (state) {
        case 0:
            func_8003DE58(*(M2C_UNK *)((((s32) (gameWork.view.viewAngle
                + ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C)
                + D_800E3D18), &D_80082E80.unk_000, (u8 *) effect + 0x28, 0);
            sin_x = func_80064584(((S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16);
            cos_x = func_80064584(((S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16 - 0x400);
            state0_move = &D_80083780;
            sin_x >>= 4;
            state0_delta_x = ((u16)state0_move->x.w.i);
            cos_x >>= 4;
            state0_delta_x -= sin_x;
            state0_delta_x += cos_x;
            state0_actor = ((S_819835AC_11 *) &D_800E3D7C)->unk_00;
            effect->unk_28.u16 += state0_delta_x;
            sin_y = func_800644B8(state0_actor->unk_2A.s16);
            cos_y = func_800644B8(((S_819835AC_5 *) (*(void **)&D_800E3D7C))->unk_2A.s16 - 0x400);
            sin_y_shift = sin_y >> 4;
            cos_y >>= 4;
            step_y = ((u16)state0_move->y.w.i);
            coord_delta = effect->unk_2A.u16;
            step_y -= sin_y_shift;
            step_y += cos_y;
            state0_height_actor = ((S_819835AC_11 *) &D_800E3D7C)->unk_00;
            coord_delta += step_y;
            effect->unk_2A.u16 = (u16) coord_delta;
            coord_delta = effect->unk_2C.u16;
            step_y = state0_height_actor->unk_88.u16;
            approach_frames = 0x10U;
            coord_delta -= 0x50;
            step_y += coord_delta;
            effect->unk_2C.u16 = (u16) step_y;
            effect->unk_34.u16 = approach_frames;
            height_numerator_2 = (effect->unk_2C.s16 - motion->unk_08.half.unk_0A.s16) << 0x10;
            height_frames = 16;
            motion->unk_14.word = height_numerator_2 / height_frames;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
        case 1:
            aim_angle = func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
                (s16) effect->unk_28.u16, (s16) effect->unk_2A.u16);
            approach_heading = effect->unk_38;
            if (approach_heading & 0x800) {
                approach_signed_angle = approach_heading | 0xF800;
            } else {
                approach_signed_angle = approach_heading & 0x7FF;
            }
            effect->unk_38 = approach_signed_angle;
            if (aim_angle & 0x800) {
                angle_mask = ~0x7FF;
                normalized_angle = aim_angle | angle_mask;
            } else {
                normalized_angle = aim_angle & 0x7FF;
            }
            aim_angle = normalized_angle;
            approach_wrap_gap = (s16) effect->unk_38 - aim_angle;
            if (approach_wrap_gap < 0) {
                approach_wrap_gap = 0 - approach_wrap_gap;
            }
            if (approach_wrap_gap >= 0x801) {
                effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
            }
            approach_angle = (s16) effect->unk_38;
            approach_turn_gap = aim_angle - approach_angle;
            if (approach_turn_gap < 0) {
                approach_turn_gap = 0 - approach_turn_gap;
            }
            if (approach_turn_gap >= 0x81) {
                if (effect->unk_96 != 0) {
                    approach_next_angle = approach_angle + 0x80;
                } else {
                    approach_next_angle = approach_angle - 0x80;
                }
                effect->unk_38 = approach_next_angle;
            } else {
                effect->unk_38 = aim_angle;
            }
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            approach_ticks = effect->unk_34.u16 - 1;
            effect->unk_34.u16 = approach_ticks;
            if ((approach_ticks << 0x10) <= 0) {
                motion->unk_08.half.unk_0A.u16 = (u16) effect->unk_2C.u16;
                effect->unk_34.u16 = 0U;
                motion->unk_14.word = 0;
            }
            state1_global = ((S_819835AC_11 *) &D_800814A8)->unk_00;
            state1_global->unk_96 = 2;
            boost_speed_x = motion->unk_00.word;
            coord_delta = motion->unk_0C.word;
            step_y = motion->unk_10.word;
            step_z = motion->unk_14.word;
            boost_speed_x += coord_delta;
            motion->unk_00.word = boost_speed_x;
            boost_speed_x = motion->unk_04.word;
            coord_delta = motion->unk_08.word;
            boost_speed_x += step_y;
            motion->unk_04.word = boost_speed_x;
            boost_speed_x = motion->unk_00.half.unk_02.s16;
            coord_delta += step_z;
            motion->unk_08.word = coord_delta;
            coord_delta = effect->unk_28.s16;
            boost_speed_x -= coord_delta;
            if (__builtin_abs(boost_speed_x) >= 0x40) {
                break;
            }
            approach_gap_y = motion->unk_04.half.unk_06.s16;
            target_coord = effect->unk_2A.s16;
            approach_gap_y -= target_coord;
            if (__builtin_abs(approach_gap_y) >= 0x40) {
                break;
            }
            approach_gap_z = motion->unk_08.half.unk_0A.s16;
            target_coord = effect->unk_2C.s16;
            approach_gap_z -= target_coord;
            if (__builtin_abs(approach_gap_z) >= 0x40) {
                break;
            }
            func_8003DE58(*(M2C_UNK *)((((s32) (gameWork.view.viewAngle
                + ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16 + 0x100) >> 7) & 0x1C)
                + D_800E3D18), &D_80082E80.unk_000, (u8 *) effect + 0x28, 0);
            state1_move = &D_80083780;
            effect->unk_28.u16 += (u16)state1_move->x.w.i;
            state1_actor = ((S_819835AC_11 *) &D_800814A8)->unk_00;
            effect->unk_2A.u16 += (u16)state1_move->y.w.i;
            coord_delta = effect->unk_2C.u16;
            boost_speed_x = ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_88.u16;
            coord_delta -= 0x50;
            boost_speed_x += coord_delta;
            effect->unk_2C.u16 = boost_speed_x;
            state1_actor->unk_A6 = state1_actor->unk_A6 - 1;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
            break;
        case 2:
            aim_angle = func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
                (s16) effect->unk_28.u16, (s16) effect->unk_2A.u16);
            travel_heading = effect->unk_38;
            if (travel_heading & 0x800) {
                travel_signed_angle = travel_heading | 0xF800;
            } else {
                travel_signed_angle = travel_heading & 0x7FF;
            }
            effect->unk_38 = travel_signed_angle;
            if (aim_angle & 0x800) {
                angle_mask = ~0x7FF;
                normalized_angle = aim_angle | angle_mask;
            } else {
                normalized_angle = aim_angle & 0x7FF;
            }
            aim_angle = normalized_angle;
            travel_wrap_gap = (s16) effect->unk_38 - aim_angle;
            if (travel_wrap_gap < 0) {
                travel_wrap_gap = 0 - travel_wrap_gap;
            }
            if (travel_wrap_gap >= 0x801) {
                effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
            }
            travel_angle = (s16) effect->unk_38;
            travel_turn_gap = aim_angle - travel_angle;
            if (travel_turn_gap < 0) {
                travel_turn_gap = 0 - travel_turn_gap;
            }
            if (travel_turn_gap >= 0x81) {
                if (effect->unk_96 != 0) {
                    travel_next_angle = travel_angle + 0x80;
                } else {
                    travel_next_angle = travel_angle - 0x80;
                }
                effect->unk_38 = travel_next_angle;
            } else {
                effect->unk_38 = aim_angle;
            }
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            travel_ticks = effect->unk_34.u16 - 1;
            effect->unk_34.u16 = travel_ticks;
            if ((travel_ticks << 0x10) <= 0) {
                motion->unk_08.half.unk_0A.u16 = (u16) effect->unk_2C.u16;
                effect->unk_34.u16 = 0U;
                motion->unk_14.word = 0;
            }
            boost_speed_x = motion->unk_00.word;
            coord_delta = motion->unk_0C.word;
            step_y = motion->unk_10.word;
            step_z = motion->unk_14.word;
            boost_speed_x += coord_delta;
            motion->unk_00.word = boost_speed_x;
            boost_speed_x = motion->unk_04.word;
            coord_delta = motion->unk_08.word;
            boost_speed_x += step_y;
            coord_delta += step_z;
            motion->unk_04.word = boost_speed_x;
            state2_stage = (*(void **)((u8 *)&D_800814A8 + 0));
            motion->unk_08.word = coord_delta;
            state2_stage->unk_96 = 2;
            travel_gap_x = motion->unk_00.half.unk_02.s16;
            target_coord = effect->unk_28.s16;
            travel_gap_x -= target_coord;
            if (travel_gap_x < 0) {
                travel_gap_x = 0 - travel_gap_x;
            }
            if (travel_gap_x >= 0x20) {
                break;
            }
            travel_gap_y = motion->unk_04.half.unk_06.s16;
            target_coord = effect->unk_2A.s16;
            travel_gap_y -= target_coord;
            if (travel_gap_y < 0) {
                travel_gap_y = 0 - travel_gap_y;
            }
            if (travel_gap_y >= 0x20) {
                break;
            }
            effect->unk_34.u16 = 4U;
            state2_actor = ((S_819835AC_11 *) &D_800E3D7C)->unk_00;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
            ((S_819835AC_6 *) ((S_819835AC_11 *) &D_800814A8)->unk_00)->unk_96 = 0;
            effect->unk_38 = (u16) state2_actor->unk_2A.s16;
            state2_angle = state2_actor->unk_2A.u16;
            D_80026B28 = 0;
            effect->unk_44 = (u16) ((state2_angle >> 9) & 7);
            break;
        case 3:
        case 4:
            state34_base = &D_80082E80;
            if (func_8003DE58(state34_base->unk_008, state34_base, &emit_offset, 0) != 0) {
                if (effect->unk_30 == 3) {
                    state34_move = &D_80083780;
                    func_800B8D64(state34_move->x.w.i + emit_offset.x, state34_move->y.w.i + emit_offset.y,
                        state34_move->z.w.i + emit_offset.z);
                    effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
                }
                state34_emit = &D_80083780;
                func_80024B2C((s16) (((u16)state34_emit->x.w.i) + (u16) emit_offset.x),
                    (s16) (((u16)state34_emit->y.w.i) + (u16) emit_offset.y),
                    (s16) (((u16)state34_emit->z.w.i) + (u16) emit_offset.z),
                    ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_2A.s16, 0);
            }
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            motion->unk_14.half.unk_16 = 0x16;
            rise_speed = motion->unk_14.word;
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            M2C_SFIELD(motion, 8) = (s32) (motion->unk_08.word + motion->unk_14.word);
            if ((s16) motion->unk_08.half.unk_0A.u16 > ((S_819835AC_5 *) (*(void **)((u8 *)&D_800E3D7C
                + 0)))->unk_88.s16) {
                motion->unk_08.half.unk_0A.u16 =
                    (u16) ((S_819835AC_5 *) ((S_819835AC_11 *) &D_800E3D7C)->unk_00)->unk_88.s16;
            }
            launch_ticks = effect->unk_34.u16 - 1;
            effect->unk_34.u16 = launch_ticks;
            if ((launch_ticks << 0x10) > 0) {
                break;
            }
            tile_base = &D_80082E80;
            tile_coord = tile_base->tileX;
            tile_call_arg = 0x300;
            effect->unk_40 = (s16) tile_coord;
            effect->unk_98 = (u8) tile_coord;
            tile_coord = tile_base->tileY;
            effect->unk_30 = 5;
            effect->unk_46 = 3U;
            effect->unk_34.u16 = 0U;
            effect->unk_42 = (s16) tile_coord;
            effect->unk_99 = (u8) tile_coord;
            func_800A56E0(tile_call_arg, rise_speed);
            break;
        case 5:
            motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
            motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            motion->unk_14.word = 0;
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            world_x = motion->unk_00.half.unk_02.s16;
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
            if (world_x < 0) {
                world_x += 0x3F;
            }
            tile_div = world_x >> 6;
            effect->unk_40 = (s16) tile_div;
            world_y = motion->unk_04.half.unk_06.s16;
            next_tile_y = (world_y / 64);
            effect->unk_42 = (s16) next_tile_y;
            if (effect->unk_98 == effect->unk_40) {
                if (effect->unk_99 == next_tile_y) {
                    break;
                }
            }
            hit_actor = ((S_819835AC_11 *) &D_800814A8)->unk_00;
            hit_origin = (s32)(hit_actor);
            coord_delta = hit_actor->unk_5C;
            hit_actor = coord_delta + 0x20;
            if (hit_actor != (void *)hit_origin) {
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
                            func_8009CE1C(hit_actor, 0xC, D_80027C96, 0xA, (s32) (s16) (effect->unk_44 << 9),
                                D_80027C98, 2);
                            related_motion = ((S_819835AC_8 *) ((u8 *) hit_actor - 0x20))->unk_08;
                            func_80024938(related_motion->unk_00.half.unk_02.s16,
                                related_motion->unk_04.half.unk_06.s16, related_motion->unk_08.half.unk_0A.s16,
                                (s16) effect->unk_38, (func_80069EF8() & 3) | 4);
                            actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                        }
                    }
                    coord_delta = hit_actor->unk_5C;
                    hit_actor = coord_delta + 0x20;
                } while (hit_actor != ((S_819835AC_11 *) &D_800814A8)->unk_00);
            }
            tile_x = (u8) effect->unk_40;
            tile_counter = effect->unk_46;
            tile_y = (u8) effect->unk_42;
            tile_counter -= 1;
            effect->unk_46 = tile_counter;
            effect->unk_98 = tile_x;
            effect->unk_99 = tile_y;
            if ((tile_counter << 0x10) > 0) {
                break;
            }
            effect->unk_8A = (u16) ((func_80069EF8() & 0x1F) + 0x10);
            effect->unk_9C = NULL;
            effect->unk_30 = (s16) ((u16) effect->unk_30 + 1);
            break;
        case 6:
            target = effect->unk_9C;
            if (target != NULL) {
                related_motion = ((S_819835AC_8 *) ((u8 *) target - 0x20))->unk_08;
                aim_angle = func_800A07D0((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
                    related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16);
                homing_heading = effect->unk_38;
                if (homing_heading & 0x800) {
                    homing_signed_angle = homing_heading | 0xF800;
                } else {
                    homing_signed_angle = homing_heading & 0x7FF;
                }
                effect->unk_38 = homing_signed_angle;
                if (aim_angle & 0x800) {
                    angle_mask = ~0x7FF;
                    normalized_angle = aim_angle | angle_mask;
                } else {
                    normalized_angle = aim_angle & 0x7FF;
                }
                aim_angle = normalized_angle;
                homing_wrap_gap = (s16) effect->unk_38 - aim_angle;
                if (homing_wrap_gap < 0) {
                    homing_wrap_gap = 0 - homing_wrap_gap;
                }
                if (homing_wrap_gap >= 0x801) {
                    effect->unk_38 = (u16) ((aim_angle & ~0xFFF) | (effect->unk_38 & 0xFFF));
                }
                aim_ticks = effect->unk_9A - 1;
                effect->unk_9A = aim_ticks;
                if ((aim_ticks << 0x10) <= 0) {
                    effect->unk_9A = 0x1EU;
                    effect->unk_38 = aim_angle;
                }
                homing_angle = (s16) effect->unk_38;
                homing_turn_gap = aim_angle - homing_angle;
                if (homing_turn_gap < 0) {
                    homing_turn_gap = 0 - homing_turn_gap;
                }
                if (homing_turn_gap >= 0x81) {
                    if (effect->unk_96 != 0) {
                        homing_next_angle = homing_angle + 0x80;
                    } else {
                        homing_next_angle = homing_angle - 0x80;
                    }
                    effect->unk_38 = homing_next_angle;
                } else {
                    effect->unk_38 = aim_angle;
                }
                state6_timer_signed = effect->unk_34.s16;

                state6_timer = effect->unk_34.u16;
                if (state6_timer_signed != 0) {
                    state6_next = state6_timer - 1;
                    effect->unk_34.u16 = state6_next;
                    if ((state6_next << 0x10) == 0) {
                        state6_height = related_motion->unk_08.half.unk_0A.u16;
                        motion->unk_14.word = 0;
                        state6_height -= 0x40;
                        motion->unk_08.half.unk_0A.u16 = state6_height;
                        effect->unk_8A = 0U;
                    }
                } else {
                    bob_phase = effect->unk_8A + 1;
                    state6_spin_arg = (s32) (bob_phase << 0x10);

                    state6_spin_arg >>= 9;
                    effect->unk_8A = bob_phase;
                    motion->unk_14.half.unk_16 = (s16) (func_800644B8(state6_spin_arg) >> 9);
                }
                target_gap_x = motion->unk_00.half.unk_02.s16;
                target_coord = related_motion->unk_00.half.unk_02.s16;
                target_gap_x -= target_coord;
                if (target_gap_x < 0) {
                    target_gap_x = 0 - target_gap_x;
                }
                if (target_gap_x < 0x20) {
                    target_gap_y = motion->unk_04.half.unk_06.s16;
                    target_coord = related_motion->unk_04.half.unk_06.s16;
                    target_gap_y -= target_coord;
                    if (target_gap_y < 0) {
                        target_gap_y = 0 - target_gap_y;
                    }
                    if (target_gap_y < 0x20) {
                        actor_data = effect->unk_9C - 0x20;
                        func_8009CE1C(effect->unk_9C, 0xC, D_80027C96, 0xA, (s32) (s16) (effect->unk_44 << 9),
                            D_80027C98, 2);
                        func_800A56E0(0x300);
                        func_80024938(related_motion->unk_00.half.unk_02.s16, related_motion->unk_04.half.unk_06.s16,
                            (s16) related_motion->unk_08.half.unk_0A.u16, (s16) effect->unk_38,
                            (func_80069EF8() & 3) | 4);
                        actor_data->unk_1E = (u16) (actor_data->unk_1E | 0x2000);
                        effect->unk_9C = NULL;
                        effect->unk_8A = (u16) ((func_80069EF8() & 0x1F) + 0x10);
                    }
                }
                motion->unk_0C.word = func_80064584((s16) effect->unk_38) << 8;
                motion->unk_10.word = func_800644B8((s16) effect->unk_38) << 8;

                if ((s16) effect->unk_38 == aim_angle) {
                    motion->unk_0C.word += motion->unk_0C.word >> 1;
                    motion->unk_10.word += motion->unk_10.word >> 1;
                }
            } else {
                motion->unk_14.word = 0;
                search_ticks = effect->unk_8A - 1;
                effect->unk_8A = search_ticks;
                if ((search_ticks << 0x10) <= 0) {
                    new_target = func_80026444(&D_80082E80.unk_000);
                    effect->unk_9C = new_target;
                    if (new_target == NULL) {
                        effect->unk_30 = 0x10;
                        effect->unk_8A = 8U;
                    } else {
                        related_motion = ((S_819835AC_8 *) ((u8 *) new_target - 0x20))->unk_08;
                        effect->unk_34.u16 = 0x10U;
                        state6_target_base = motion->unk_08.half.unk_0A.s16;
                        height_value = related_motion->unk_08.half.unk_0A.s16;
                        state6_target_base += 0x40;
                        height_numerator = (height_value - state6_target_base) << 0x10;
                        height_frames = 16;
                        motion->unk_14.word = height_numerator / height_frames;
                        effect->unk_9A = 0x3CU;
                    }
                } else {
                    effect->unk_38 = (u16) (effect->unk_38 + 0x80);
                }
                motion->unk_0C.word = (s32) (func_80064584((s16) effect->unk_38) << 8);
                motion->unk_10.word = (s32) (func_800644B8((s16) effect->unk_38) << 8);
            }
            motion->unk_00.word = (s32) (motion->unk_00.word + motion->unk_0C.word);
            motion->unk_04.word = (s32) (motion->unk_04.word + motion->unk_10.word);
            motion->unk_08.word = (s32) (motion->unk_08.word + motion->unk_14.word);
            break;
        case 16:
            fade_speed_x = motion->unk_0C.word;
            fade_speed_y = motion->unk_10.word;
            motion->unk_0C.word = (s32) (fade_speed_x - (fade_speed_x >> 3));
            motion->unk_10.word = (s32) (fade_speed_y - (fade_speed_y >> 3));
            if ((effect->unk_3E - 0x10) < (s16) motion->unk_08.half.unk_0A.u16) {
                motion->unk_08.half.unk_0A.u16 = (u16) ((u16) effect->unk_3E - 0x10);
            }
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
                return;
            }
            D_80027C94 = 0;
            goto block_139;
        }
        visual->unk_1A = (u16) (func_800A07D0(0, 0, motion->unk_0C.half.unk_0E, motion->unk_10.half.unk_12) - 0x400);
        boost_speed_x = motion->unk_14.half.unk_16;
        step_y = (*(u16 *)((u8 *)visual + 0x1C));
        coord_delta = visual->unk_0C.half.unk_0C;
        aim_angle = boost_speed_x * 4;
        boost_speed_x = aim_angle + 0x400;
        visual->unk_16 = (u16) boost_speed_x;
        boost_speed_x = 0x2000;
        boost_speed_x -= step_y;
        boost_speed_x >>= 2;
        step_y += boost_speed_x;
        coord_delta += 8;
        visual->unk_0C.half.unk_0C = coord_delta;
        visual->unk_1C = (u16) step_y;
        visual->unk_20 = (u16) step_y;
        visual->unk_1E = (u16) step_y;
        coord_delta &= 0xFF;
        coord_delta = (u32)coord_delta < 0x81U;
        if (!coord_delta) {
            visual->unk_0C.word = 0x808080;
        } else {
            visual->unk_0C.half.unk_0D = (u8) (visual->unk_0C.half.unk_0D + 8);
            visual->unk_0C.half.unk_0E = (u8) (visual->unk_0C.half.unk_0E + 8);
        }
        func_80026694((u8 *) effect - 0x20, motion, 8, 0x300);
        func_800262F4(visual, (u8 *) effect + 0x36, effect->unk_3C, effect->unk_3A);
        func_80026240(effect, visual->unk_00);
        frame = visual->unk_04;
        if ((s8) frame == effect->unk_3A) {
            frame_step = -1;
            effect->unk_36 = frame_step;
        } else if ((s8) frame == effect->unk_3C) {
            frame_step = 1;
            effect->unk_36 = frame_step;
        }
        func_8002470C((s16) motion->unk_00.half.unk_02.u16, (s16) motion->unk_04.half.unk_06.u16,
            (s16) motion->unk_08.half.unk_0A.u16, (s16) effect->unk_38, D_80026BD4[(s8) visual->unk_04]);
        effect->unk_94 = (u16) (effect->unk_94 + 1);
        return;
    }
    owner_ptr = owner_ref | 0x80000000;
    if (!(((S_819835AC_8 *) owner_ptr)->unk_1E & 0x8000)) {
        goto block_140;
    }
block_139:
    ((S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E = (u16) (((S_819835AC_8 *) ((u8 *) effect - 0x20))->unk_1E
        | 0x8000);
    (*(s32 *)&objectFlagBlock.flags) = (s32) (((S_819835AC_12 *) &objectFlagBlock.flags)->unk_00 | 0x8000);
    return;
block_140:
    actor_data = ((S_819835AC_8 *) owner_ptr)->unk_0C;
    related_motion = ((S_819835AC_8 *) owner_ptr)->unk_08;
    if (owner_ref & 0x80000000) {
        owner_state = owner_ptr + 0x20;
        visual->unk_1A = (u16) (func_800A07D0((s16) motion->unk_00.half.unk_02.u16,
            (s16) motion->unk_04.half.unk_06.u16, related_motion->unk_00.half.unk_02.s16,
            related_motion->unk_04.half.unk_06.s16) - 0x400);
        alternate_delta = related_motion->unk_08.half.unk_0A.s16;
        alternate_value = motion->unk_08.half.unk_0A.s16;
        alternate_delta -= alternate_value;
        alternate_scale = alternate_delta << 2;
        alternate_scale += alternate_delta;
        aim_angle = alternate_scale << 1;
        alternate_value = aim_angle + 0x400;
        visual->unk_16 = (u16) alternate_value;
        visual->unk_14 = (u16) actor_data->unk_14;
        motion->unk_00.half.unk_02.u16 = (u16) owner_state->unk_50;
        motion->unk_04.half.unk_06.u16 = (u16) owner_state->unk_52;
        motion->unk_08.half.unk_0A.u16 = (u16) owner_state->unk_54;
    } else {
        motion->unk_00.half.unk_02.u16 = (u16) related_motion->unk_00.half.unk_02.s16;
        motion->unk_04.half.unk_06.u16 = (u16) related_motion->unk_04.half.unk_06.s16;
        motion->unk_08.half.unk_0A.u16 = (u16) related_motion->unk_08.half.unk_0A.s16;
        visual->unk_16 = (u16) actor_data->unk_16;
        visual->unk_18 = (u16) actor_data->unk_18;
        visual->unk_1A = (u16) actor_data->unk_1A;
        visual->unk_14 = (u16) actor_data->unk_14;
    }
    visual->unk_1C = (u16) actor_data->unk_1C;
    visual->unk_1E = (u16) actor_data->unk_1E;
    visual->unk_20 = (u16) actor_data->unk_20;
    visual->unk_0C.word = actor_data->unk_0C;
    if (D_80026BC8[effect->unk_88] != 0) {
        func_800263C0(visual, actor_data->unk_04);
        func_80026240(effect, visual->unk_00);
    }
    effect->unk_94 = (u16) (effect->unk_94 + 1);
    return;
}
