#include "common.h"
#include "town/map/course.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_80100D98.h"




typedef struct S_800C035C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xB4];
    union { s16 s; s16 u; u16 p; } unk_C8;   /* accessed as both */
} S_800C035C_3;





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
s32 rsin();                             /* extern */
s32 rcos();                             /* extern */
void reserve_tw_mon_load(s32 reservation_value);     /* extern */
void add_motion_deltas_to_position();                      /* extern */
struct IntVector3; void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(struct IntVector3 *);                      /* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                      /* extern */
struct Rec_D_800FE490; void update_the_s_field_10_using_callee_8008_fe_90(struct Rec_D_800FE490 *);                   /* extern */
struct ObjectPosition; struct ObjectPosition; void copy_entity_record_fields(struct ObjectPosition *, struct ObjectPosition *);           /* extern */
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
void update_player_minigame_motion(TownCourseActor *actor, ObjectPosition *motion, SpriteFrameState *sprite) {
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
    TownCourse *course;

    controls = ((s32 *)&g_game_work.draw_buffer);
    course = actor->course;
    progress = &actor->progress;
    apply_the_enabled_movement_offsets_adding_z_offset_only_positive((struct IntVector3 *)(motion));
    update_the_s_field_10_using_callee_8008_fe_90(&town_motion_list);
    add_motion_deltas_to_position(motion);
    motion->x.v = (s32) (motion->x.v + actor->impulse_x);
    motion->y.v = (s32) (motion->y.v + actor->impulse_y);
    actor->impulse_x = (s32) ((s32) actor->impulse_x >> 1);
    actor->impulse_y = (s32) ((s32) actor->impulse_y >> 1);
    ground_probe = *(Blk24 *) motion;
    course_type = course->surface_kind;
    if ((course_type == 2) || (course_type == 6)) {
        ground_probe.w[2] = 0xFE000000;
    }
    ground_height = query_lowered_transform_position(&ground_probe);
    if ((ground_height << 0x10) > 0) {
        ground_height = 0;
    }
    if ((controls->unk_10 & 0x20) && (actor->speed <= 0x200000)) {
        spawn_person_radial_effects(motion);
        actor->speed = (s32) (actor->speed + 0x80000);
    }
    if (controls->unk_10 & 0x40) {
        motion_adjustment = actor->speed;
        if (motion_adjustment >= (s32) 0xFFE00000) {
            actor->speed = (s32) (motion_adjustment + 0xFFF80000);
        }
    }
    held_buttons = controls->unk_08;
    if (held_buttons & 0x20) {
        speed = actor->speed;
        if (speed < 0) {
            actor->speed = (s32) (speed + 0x20000);
        } else if (speed <= 0xFFFFF) {
            actor->speed = (s32) (speed + 0x18000);
        }
    } else if (held_buttons & 0x40) {
        speed = actor->speed;
        if (speed > 0) {
            actor->speed = (s32) (speed + 0xFFFE0000);
        } else if (speed > (s32) 0xFFF00000) {
            actor->speed = (s32) (speed + 0xFFFE8000);
        }
    }
    speed = actor->speed;
    if (speed < (s32) 0xFFFF0000) {
        actor->speed = (s32) (speed + 0x10000);
    } else if (speed > 0x10000) {
        actor->speed = (s32) (speed - 0x10000);
    } else {
        actor->speed = 0;
    }
    held_buttons = controls->unk_08;
    if (held_buttons & 0x8000) {
        heading_or_speed = actor->facing.u + 0x20;
        actor->facing.u = (u16) (heading_or_speed & 0xFFF);
    } else if (held_buttons & 0x2000) {
        heading_or_speed = actor->facing.u + 0xFE0;
        actor->facing.u = (u16) (heading_or_speed & 0xFFF);
    }
    motion->velocity_x =
        (s32) (rsin((s16) actor->facing.u) * ((s32) actor->speed >> 0xC));
    motion->velocity_y =
        (s32) (rcos((s16) actor->facing.u) * ((s32) actor->speed >> 0xC));
    angle_base = controls->unk_C8.s - 0x800;
    angle_value = actor->facing.s;
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
    heading_or_speed = actor->speed;
    motion_adjustment |= 0xFFFF;
    heading_or_speed = abs(heading_or_speed);
    motion_adjustment = motion_adjustment < heading_or_speed;
    if (motion_adjustment && (controls->unk_08 & 0xA000)) {
        if (angle_delta < -0x180) {
            view_angle = actor->facing.u + 0x980;
        } else if (angle_delta >= 0x181) {
            view_angle = actor->facing.u + 0x680;
        } else if (angle_delta < 0) {
            view_angle = (u16) controls->unk_C8.s - 0x10;
        } else if (angle_delta > 0) {
            view_angle = (u16) controls->unk_C8.s + 0x10;
        } else {
            view_angle = actor->facing.u + 0x800;
        }
    } else {
        view_error = abs(angle_delta);
        if (view_error >= 8) {
            motion_adjustment = angle_delta >> 3;
            view_angle = (u16) controls->unk_C8.s + motion_adjustment;
        } else {
            view_angle = actor->facing.u + 0x800;
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
        if (ground_height <= (motion->z.w.i + 2)) {
            if (actor->speed > 0xC0000) {
                spawn_person_radial_effects(motion);
            }
        }
    }
    if (town_blocked_directions != 0) {
        motion->velocity_z = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2((s32 *)(motion));
    }
    if (motion->z.w.i > ground_height) {
        motion->z.w.i = ground_height;
        if (motion->velocity_z >= 0) {
            motion->velocity_z = 0;
        }
        if (actor->flags & 1) {
            spawn_person_radial_effects(motion);
        }
        motion_adjustment = -2;
        motion_flags = actor->flags & motion_adjustment;
    } else {
        motion_flags = actor->flags | 1;
    }
    actor->flags = motion_flags;
    if ((controls->unk_10 & 0x10) && (ground_height == motion->z.w.i)) {
        motion->velocity_z = -0x140000;
    }
    motion->velocity_z = (s32) (motion->velocity_z + 0x20000);
    state = actor->state;
    switch (state) {
    case 0:
        actor->facing.u = 0xC00U;
        motion->z.v = 0;
        progress->unk_02 = 0;
        progress->unk_00 = 0;
        controls->unk_C8.s = 0xC00;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        break;
    case 1:
        controls->unk_C8.s = (s16) (((0x20 - course->unk_2E) << 5) + 0xC00);
        actor->facing.u = 0xC00U;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        break;
    case 2:
        controls->unk_C8.s = (s16) ((0x10 - course->unk_2E) << 5);
        wait_stage = progress->unk_00;
        if (wait_stage < 4) {
            (wait_stage + course->lap_times)->u =
                (u16) ((wait_stage + course->lap_times)->u + 1);
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        break;
    case 3:
        prev_stage = progress->unk_00;
        advance_bounded_entry_index(motion, progress);
        fill_eligible_negative_slots(course, progress, 0);
        if (progress->unk_00 != prev_stage) {
            s32 *best_time;

            best_time = (s32 *)0x800135B4;
            stage_time = (prev_stage + course->lap_times)->s;
            if (stage_time < *best_time) {
                *best_time = (s32) stage_time;
                course->best_time = stage_time;
                set_resident_bit(0x596);
            }
        }
        active_stage = progress->unk_00;
        if (active_stage < 4) {
            elapsed_time = (active_stage + course->lap_times)->u;
            (active_stage + course->lap_times)->u = (u16) (elapsed_time + 1);
            if ((s16) elapsed_time >= 0x7530) {
                (progress->unk_00 + course->lap_times)->s = 0x7530;
            }
        }
        break;
    case 4:
        event_params = *(Blk20 *) &D_80089960;
        reserve_tw_mon_load(2);
        change_map(&event_params);
        actor->state = (s16) ((u16) actor->state + 1);
    }
    {
        s32 sprite_angle;
        angle_base = (s32) actor->facing.s - 0x1500;
        angle_value = controls->unk_C8.s;
        sprite_angle = angle_value - angle_base;
        angle_delta = (sprite_angle & 0xFFF) >> 9;
    }
    actor->facing.u = (u16) ((actor->facing.u + 0x2000) & 0xFFF);
    if (actor->sprite_direction != angle_delta) {
        if (*(s32 *)&sprite->frameTable != 0) {
            texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(sprite, actor->direction_frames[angle_delta], sprite->unk_04, 0);
        }
        actor->sprite_direction = (s16) angle_delta;
    }
    if (((u8 *)&D_8006CCF8)[angle_delta] != 0) {
        sprite->flags |= 1;
    } else {
        sprite->flags &= 0xFFFE;
    }
    step_actor_animation(sprite, 0);
    copy_entity_record_fields((struct ObjectPosition *)(&town_position_reference_state), (struct ObjectPosition *)(motion));
    ((Rec_D_80100D98 *)(&town_position_reference_state))->unk_08 = 0;
}
