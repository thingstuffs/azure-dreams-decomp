#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_80100D98.h"

typedef struct S_800C035C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x6];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    s16 unk_12;
    u8 pad_14[0x8];
    void * unk_1C;
    u8 pad_20[0x28];
    s32 unk_48;
    s32 unk_4C;
    u8 pad_50[0x4];
    void * unk_54;
    s32 unk_58;
    s32 unk_5C;
} S_800C035C_0;   /* arg0 in update_player_minigame_motion */

typedef struct S_800C035C_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800C035C_1;   /* arg1 in update_player_minigame_motion */

typedef struct S_800C035C_2 {
    u8 pad_00[0x2E];
    u16 unk_2E;
    u8 pad_30[0x8];
    s16 unk_38;
    u8 pad_3A[0x2];
    s16 unk_3C;
} S_800C035C_2;

typedef struct S_800C035C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xB4];
    union { s16 s; s16 u; u16 p; } unk_C8;   /* accessed as both */
} S_800C035C_3;

typedef struct S_800C035C_5 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_800C035C_5;

typedef struct S_800C035C_6 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800C035C_6;

typedef struct S_800C035C_7 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_800C035C_7;

typedef struct S_800C035C_10 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800C035C_10;

typedef struct {
    s32 w[6];
} Blk24;

typedef struct {
    s32 w[5];
} Blk20;

void advance_bounded_entry_index();              /* extern */
void fill_eligible_negative_slots();     /* extern */
void set_resident_bit(s16 value);              /* extern */
typedef struct InputRecord InputRecord;
void change_map(InputRecord *input);                       /* extern */
void texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags();     /* extern */
typedef struct {
    u8 pad[0x14];
    u16 unk14;
} S_80048AC8;
void step_actor_animation(S_80048AC8 *entity, void *slot_index);             /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
void reserve_tw_mon_load(s32 reservation_value);     /* extern */
void add_motion_deltas_to_position();                      /* extern */
struct IntVector3; void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(struct IntVector3 *);                      /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                      /* extern */
struct Rec_D_800FE490; void update_the_s_field_10_using_callee_8008_fe_90(struct Rec_D_800FE490 *);                   /* extern */
struct ObjectPosition; struct S_800A48B0_0; void copy_entity_record_fields(struct S_800A48B0_0 *, struct ObjectPosition *);           /* extern */
void spawn_person_radial_effects(void *);                      /* extern */
s16 query_lowered_transform_position();                      /* extern */
extern s32 D_800135B4;
extern u8 D_8006CCF8[];
extern M2C_UNK D_80089960;
extern u8 town_blocked_directions;
#include "records/Rec_D_800FE490.h"
#include "shared/minigame_body.h"
extern Rec_D_800FE490 town_motion_list;
extern Rec_D_80100D98 town_position_reference_state;

/* Updates movement, jumping, course progress, and sprite orientation from player input. */
void update_player_minigame_motion(void *actor, S_800C035C_1 *motion, SpriteFrameState *sprite) {
    Blk24 ground_probe;
    Blk20 event_params;
    s32 prev_stage;
    s16 course_type;
    s32 wait_stage;
    s32 stage_time;
    s32 active_stage;
    s16 ground_height;
    s16 view_angle;
    s32 speed;
    s32 angle_base;
    s32 angle_value;
    s32 motion_adjustment;
    s32 state;
    s32 held_buttons;
    s32 angle_delta;
    s32 heading_or_speed;
    s32 view_error;
    s32 turn_size;
    s32 motion_flags;
    u16 elapsed_time;
    S_800C035C_3 *controls;
    MinigameProgressPair16 *progress;
    S_800C035C_2 *course;

    controls = ((s32 *)&g_game_work.draw_buffer);
    course = ((S_800C035C_0 *)actor)->unk_54;
    progress = (s8 *)actor + 0x50;
    apply_the_enabled_movement_offsets_adding_z_offset_only_positive((struct IntVector3 *)(motion));
    update_the_s_field_10_using_callee_8008_fe_90(&town_motion_list);
    add_motion_deltas_to_position(motion);
    motion->unk_00 = (s32) (motion->unk_00 + ((S_800C035C_0 *)actor)->unk_58);
    motion->unk_04 = (s32) (motion->unk_04 + ((S_800C035C_0 *)actor)->unk_5C);
    ((S_800C035C_0 *)actor)->unk_58 = (s32) ((s32) ((S_800C035C_0 *)actor)->unk_58 >> 1);
    ((S_800C035C_0 *)actor)->unk_5C = (s32) ((s32) ((S_800C035C_0 *)actor)->unk_5C >> 1);
    ground_probe = *(Blk24 *) motion;
    course_type = course->unk_3C;
    if ((course_type == 2) || (course_type == 6)) {
        ground_probe.w[2] = 0xFE000000;
    }
    ground_height = query_lowered_transform_position(&ground_probe);
    if ((ground_height << 0x10) > 0) {
        ground_height = 0;
    }
    if ((controls->unk_10 & 0x20) && (((S_800C035C_0 *)actor)->unk_48 <= 0x200000)) {
        spawn_person_radial_effects(motion);
        ((S_800C035C_0 *)actor)->unk_48 = (s32) (((S_800C035C_0 *)actor)->unk_48 + 0x80000);
    }
    if (controls->unk_10 & 0x40) {
        motion_adjustment = ((S_800C035C_0 *)actor)->unk_48;
        if (motion_adjustment >= (s32) 0xFFE00000) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (motion_adjustment + 0xFFF80000);
        }
    }
    held_buttons = controls->unk_08;
    if (held_buttons & 0x20) {
        speed = ((S_800C035C_0 *)actor)->unk_48;
        if (speed < 0) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0x20000);
        } else if (speed <= 0xFFFFF) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0x18000);
        }
    } else if (held_buttons & 0x40) {
        speed = ((S_800C035C_0 *)actor)->unk_48;
        if (speed > 0) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0xFFFE0000);
        } else if (speed > (s32) 0xFFF00000) {
            ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0xFFFE8000);
        }
    }
    speed = ((S_800C035C_0 *)actor)->unk_48;
    if (speed < (s32) 0xFFFF0000) {
        ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed + 0x10000);
    } else if (speed > 0x10000) {
        ((S_800C035C_0 *)actor)->unk_48 = (s32) (speed - 0x10000);
    } else {
        ((S_800C035C_0 *)actor)->unk_48 = 0;
    }
    held_buttons = controls->unk_08;
    if (held_buttons & 0x8000) {
        heading_or_speed = ((S_800C035C_0 *)actor)->unk_10.s + 0x20;
        ((S_800C035C_0 *)actor)->unk_10.s = (u16) (heading_or_speed & 0xFFF);
    } else if (held_buttons & 0x2000) {
        heading_or_speed = ((S_800C035C_0 *)actor)->unk_10.s + 0xFE0;
        ((S_800C035C_0 *)actor)->unk_10.s = (u16) (heading_or_speed & 0xFFF);
    }
    motion->unk_0C =
        (s32) (func_800644B8((s16) ((S_800C035C_0 *)actor)->unk_10.s) * ((s32) ((S_800C035C_0 *)actor)->unk_48 >> 0xC));
    motion->unk_10 =
        (s32) (func_80064584((s16) ((S_800C035C_0 *)actor)->unk_10.s) * ((s32) ((S_800C035C_0 *)actor)->unk_48 >> 0xC));
    angle_base = controls->unk_C8.s - 0x800;
    angle_value = ((S_800C035C_0 *)actor)->unk_10.u;
    angle_delta = angle_value - angle_base;
    for (;;) {
        if (angle_delta >= 0x801) {
            angle_delta -= 0x1000;
            continue;
        }
        if (angle_delta < -0x800) {
            angle_delta += 0x1000;
            continue;
        }
        break;
    }
    motion_adjustment = 0x30000;
    heading_or_speed = ((S_800C035C_0 *)actor)->unk_48;
    motion_adjustment |= 0xFFFF;
    heading_or_speed = abs(heading_or_speed);
    motion_adjustment = motion_adjustment < heading_or_speed;
    if (motion_adjustment && (controls->unk_08 & 0xA000)) {
        if (angle_delta < -0x180) {
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x980;
        } else if (angle_delta >= 0x181) {
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x680;
        } else if (angle_delta < 0) {
            view_angle = (u16) controls->unk_C8.s - 0x10;
        } else if (angle_delta > 0) {
            view_angle = (u16) controls->unk_C8.s + 0x10;
        } else {
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x800;
        }
    } else {
        view_error = abs(angle_delta);
        if (view_error >= 8) {
            motion_adjustment = angle_delta >> 3;
            view_angle = (u16) controls->unk_C8.s + motion_adjustment;
        } else {
            view_angle = ((S_800C035C_0 *)actor)->unk_10.s + 0x800;
        }
    }
    controls->unk_C8.s = view_angle;
    {
    s32 view_mask;
    view_mask = controls->unk_C8.p;
    controls->unk_C8.u = (s16) ((view_mask + 0x1000) & 0xFFF);
    }
    turn_size = abs(angle_delta);
    if (turn_size >= 0xA0) {
        if (ground_height <= (motion->unk_08.at02.v + 2)) {
            if (((S_800C035C_0 *)actor)->unk_48 > 0xC0000) {
                spawn_person_radial_effects(motion);
            }
        }
    }
    if (town_blocked_directions != 0) {
        motion->unk_14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(motion));
    }
    if (motion->unk_08.at02.v > ground_height) {
        motion->unk_08.at02.v = ground_height;
        if (motion->unk_14 >= 0) {
            motion->unk_14 = 0;
        }
        if (((S_800C035C_0 *)actor)->unk_4C & 1) {
            spawn_person_radial_effects(motion);
        }
        motion_adjustment = -2;
        motion_flags = ((S_800C035C_0 *)actor)->unk_4C & motion_adjustment;
    } else {
        motion_flags = ((S_800C035C_0 *)actor)->unk_4C | 1;
    }
    ((S_800C035C_0 *)actor)->unk_4C = motion_flags;
    if ((controls->unk_10 & 0x10) && (ground_height == motion->unk_08.at02.v)) {
        motion->unk_14 = -0x140000;
    }
    motion->unk_14 = (s32) (motion->unk_14 + 0x20000);
    state = ((S_800C035C_0 *)actor)->unk_08;
    switch (state) {
    case 0:
        ((S_800C035C_0 *)actor)->unk_10.s = 0xC00U;
        motion->unk_08.at00.v = 0;
        progress->unk_02 = 0;
        progress->unk_00 = 0;
        controls->unk_C8.s = 0xC00;
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        break;
    case 1:
        controls->unk_C8.s = (s16) (((0x20 - course->unk_2E) << 5) + 0xC00);
        ((S_800C035C_0 *)actor)->unk_10.s = 0xC00U;
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        break;
    case 2:
        controls->unk_C8.s = (s16) ((0x10 - course->unk_2E) << 5);
        wait_stage = progress->unk_00;
        if (wait_stage < 4) {
            ((S_800C035C_5 *)(((wait_stage * 2) + (s8 *) course)))->unk_30 =
                (u16) (((S_800C035C_5 *)(((wait_stage * 2) + (s8 *) course)))->unk_30 + 1);
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        break;
    case 3:
        prev_stage = progress->unk_00;
        advance_bounded_entry_index(motion, progress);
        fill_eligible_negative_slots(course, progress, 0);
        if (progress->unk_00 != prev_stage) {
            s32 *best_time;

            best_time = (s32 *)0x800135B4;
            stage_time = ((S_800C035C_6 *)(((prev_stage * 2) + (s8 *) course)))->unk_30;
            if (stage_time < *best_time) {
                *best_time = (s32) stage_time;
                course->unk_38 = stage_time;
                set_resident_bit(0x596);
            }
        }
        active_stage = progress->unk_00;
        if (active_stage < 4) {
            elapsed_time = ((S_800C035C_7 *)(((active_stage * 2) + (s8 *) course)))->unk_30;
            ((S_800C035C_7 *)(((active_stage * 2) + (s8 *) course)))->unk_30 = (u16) (elapsed_time + 1);
            if ((s16) elapsed_time >= 0x7530) {
                ((S_800C035C_10 *)(((progress->unk_00 * 2) + (s8 *) course)))->unk_30 = 0x7530;
            }
        }
        break;
    case 4:
        event_params = *(Blk20 *) &D_80089960;
        reserve_tw_mon_load(2);
        change_map(&event_params);
        ((S_800C035C_0 *)actor)->unk_08 = (s16) ((u16) ((S_800C035C_0 *)actor)->unk_08 + 1);
    }
    {
        s32 sprite_angle;
        angle_base = (s32) ((S_800C035C_0 *)actor)->unk_10.u - 0x1500;
        angle_value = controls->unk_C8.s;
        sprite_angle = angle_value - angle_base;
        angle_delta = (sprite_angle & 0xFFF) >> 9;
    }
    ((S_800C035C_0 *)actor)->unk_10.s = (u16) ((((S_800C035C_0 *)actor)->unk_10.s + 0x2000) & 0xFFF);
    if (((S_800C035C_0 *)actor)->unk_12 != angle_delta) {
        if (*(s32 *)&sprite->frameTable != 0) {
            texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(sprite, ((u8 *)((S_800C035C_0 *)actor)->unk_1C)[angle_delta], sprite->unk_04, 0);
        }
        ((S_800C035C_0 *)actor)->unk_12 = (s16) angle_delta;
    }
    if (((u8 *)&D_8006CCF8)[angle_delta] != 0) {
        sprite->flags |= 1;
    } else {
        sprite->flags &= 0xFFFE;
    }
    step_actor_animation(sprite, 0);
    copy_entity_record_fields((struct S_800A48B0_0 *)(&town_position_reference_state), (struct ObjectPosition *)(motion));
    ((Rec_D_80100D98 *)(&town_position_reference_state))->unk_08 = 0;
}
