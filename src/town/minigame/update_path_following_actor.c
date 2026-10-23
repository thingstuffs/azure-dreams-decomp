#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80023260_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { s32 s; s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; s32 u; } unk_10;   /* accessed as both */
    u8 pad_14[0x4];
    union { u16 s; s16 u; u16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    s16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x4];
    s16 unk_2A;
} S_80023260_0;   /* arg0 in update_path_following_actor */


typedef struct S_80023260_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u16 unk_06;
    u8 pad_08[0x6];
    u16 unk_0E;
} S_80023260_3;

typedef struct S_80023260_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80023260_4;

typedef struct S_80023260_5 {
    u8 pad_00[0x3C];
    s16 unk_3C;
} S_80023260_5;

void update_directional_record();      /* extern */
void advance_bounded_entry_index();              /* extern */
void fill_eligible_negative_slots();            /* extern */
void select_sprite_entry();         /* extern */
void advance_sprite_animation_and_textures();                      /* extern */
s32 rsin();                             /* extern */
s32 rcos();                             /* extern */
s32 rand();              /* extern */
void add_motion_deltas_to_position();                      /* extern */
void spawn_person_radial_effects();                 /* extern */
s16 query_lowered_transform_position();                      /* extern */
typedef struct {
    void *ptr;
    s16 field4;
    u16 flags;
    s16 field8;
    s16 padA;
} Record12;

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} Stack24;

extern Record12 town_minigame_path_records[];
extern s32 loaded_town_resource_attributes[];
extern u8 path_actor_direction_frames[];

/* Updates path following, turning, sprite state, and ground movement. */
void update_path_following_actor(void *actor, ObjectPosition *motion, void *sprite) {
    s16 target_x;
    s16 steer_y;
    s16 target_y;
    s16 steer_x;
    s16 ground_height;
    s32 state;
    s16 pos_y;
    s16 pos_x;
    s16 turn_bias;
    s32 damped_bias;
    s32 surface_kind;
    s32 turn_limit;
    s32 abs_bias;
    s32 bias_step;
    s32 heading_error;
    s32 model_base;
    s32 path_flag;
    s32 path_speed;
    s32 speed;
    s32 idle_state;
    s32 offset_x;
    s32 offset_y;
    s32 heading;
    s32 path_heading;
    s32 final_state;
    s32 sprite_config;
    s32 angle_delta;
    s32 turn_step;
    s32 reached_point;
    s32 distance_y;
    s32 distance_x;
    u16 old_state;
    u16 path_ticks;
    s32 path_flags;
    s16 clamp_value;
    Record12 *paths;
    void *position_ref;
    void *waypoint;
    void *actor_ref;
    u8 *directions;

    actor_ref = actor;
    paths = town_minigame_path_records;
    model_base = ((S_80023260_0 *)actor)->unk_00;
    waypoint = paths[((S_80023260_0 *)actor)->unk_22].ptr + (((S_80023260_0 *)actor)->unk_1C * 8);
    advance_sprite_animation_and_textures(sprite);
    position_ref = actor + 0x14;
    advance_bounded_entry_index(motion, position_ref);
    fill_eligible_negative_slots(model_base, position_ref, ((S_80023260_0 *)actor)->unk_24);
    add_motion_deltas_to_position(motion);
    reached_point = 0;
    motion->x.v = (s32) (motion->x.v
        + ((S_80023260_0 *)actor)->unk_0C.s);
    motion->y.v = (s32) (motion->y.v
        + ((S_80023260_0 *)actor)->unk_10.s);
    offset_x = ((S_80023260_0 *)actor)->unk_0C.u;
    offset_y = ((S_80023260_0 *)actor)->unk_10.u;
    old_state = ((S_80023260_0 *)actor)->unk_18.s;
    ((S_80023260_0 *)actor)->unk_0C.s = offset_x >> 1;
    ((S_80023260_0 *)actor)->unk_10.s = offset_y >> 1;
    state = ((S_80023260_0 *)actor)->unk_18.u;
    idle_state = 2;
    switch (state) {
    case 0:
        ((S_80023260_0 *)actor)->unk_18.p = old_state + 1;
        return;
    case 1:
        ((S_80023260_0 *)actor)->unk_2A = 0x800;
        sprite_config = loaded_town_resource_attributes[0];
        directions = path_actor_direction_frames;
        ((SpriteFrameState *)sprite)->frameTable = directions;
        ((SpriteFrameState *)sprite)->animation_resource = sprite_config;
        select_sprite_entry(sprite, path_actor_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80023260_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80023260_0 *)actor)->unk_18.p = (u16) (((S_80023260_0 *)actor)->unk_18.p + 1);
        break;
    case 3:
        ((SpriteFrameState *)sprite)->frameTable = path_actor_direction_frames - 8;
        select_sprite_entry(sprite, (path_actor_direction_frames - 8)[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80023260_0 *)actor)->unk_2A + 0x100)
            >> 9) & 7], 0);
        ((S_80023260_0 *)actor)->unk_18.p = idle_state;
        break;
    case 0x100:
        path_ticks = ((S_80023260_0 *)actor)->unk_1A + 1;
        ((S_80023260_0 *)actor)->unk_1A = path_ticks;
        if ((((S_80023260_0 *)actor)->unk_04 <= 0x200000) && (((S_80023260_3 *)waypoint)->unk_06 & 2)) {
            if (((s16) path_ticks % (s16) paths[((S_80023260_0 *)actor)->unk_22].flags) == 0) {
                spawn_person_radial_effects(motion);
                ((S_80023260_0 *)actor)->unk_04 = (s32) (((S_80023260_0 *)actor)->unk_04 + 0x80000);
            }
        }
        path_speed = ((S_80023260_0 *)actor)->unk_04;
        if ((path_speed <= 0xFFFFF) && (((S_80023260_3 *)waypoint)->unk_06 & 1)) {
            ((S_80023260_0 *)actor)->unk_04 = (s32) (path_speed + 0x20000);
        }
        heading = ((S_80023260_4 *)actor_ref)->unk_2A;
        path_heading = ((S_80023260_3 *)waypoint)->unk_04;
        angle_delta = heading - path_heading;
        turn_step = 0;
        while (angle_delta >= 0x801) {
            angle_delta -= 0x1000;
        }
        while (angle_delta < -0x800) {
            angle_delta += 0x1000;
        }
        heading_error = angle_delta;
        path_flags = ((S_80023260_3 *)waypoint)->unk_06;
        path_flag = path_flags & 8;
        if (path_flag != 0) {
            path_flag = path_flags & 0x10;
            if (path_flag != 0) {
                target_x = ((S_80023260_3 *)waypoint)->unk_00;
                turn_limit = town_minigame_path_records[((S_80023260_0 *)actor)->unk_22].field8;
                if (motion->x.w.i >= target_x) {
                    reached_point = 1;
                }
            } else {
                turn_limit = 0 - town_minigame_path_records[((S_80023260_0 *)actor)->unk_22].field8;
                if (motion->x.w.i <= ((S_80023260_3 *)waypoint)->unk_00) {
                    reached_point = 1;
                }
            }
            steer_y = ((S_80023260_3 *)waypoint)->unk_02;
            pos_y = motion->y.w.i;
            distance_y = steer_y - pos_y;
            if (distance_y < 0) {
                distance_y = 0 - distance_y;
            }
            if (distance_y >= 5) {
                turn_step = 0x20;
                if (pos_y >= steer_y) {
                    if ((0 - turn_limit) < heading_error) {
                        turn_step = -0x20;
                    }
                } else if (turn_limit < heading_error) {
                    turn_step = -0x20;
                }
            }
        } else {
            path_flag = path_flags & 0x10;
            if (path_flag != 0) {
                target_y = ((S_80023260_3 *)waypoint)->unk_02;
                turn_limit = town_minigame_path_records[((S_80023260_0 *)actor)->unk_22].field8;
                if (motion->y.w.i >= target_y) {
                    reached_point = 1;
                }
            } else {
                turn_limit = 0 - town_minigame_path_records[((S_80023260_0 *)actor)->unk_22].field8;
                if (motion->y.w.i <= ((S_80023260_3 *)waypoint)->unk_02) {
                    reached_point = 1;
                }
            }
            steer_x = ((S_80023260_3 *)waypoint)->unk_00;
            pos_x = motion->x.w.i;
            distance_x = steer_x - pos_x;
            if (distance_x < 0) {
                distance_x = 0 - distance_x;
            }
            if (distance_x >= 5) {
                turn_step = 0x20;
                if (pos_x < steer_x) {
                    if ((0 - turn_limit) < heading_error) {
                        turn_step = -0x20;
                    }
                } else if (turn_limit < heading_error) {
                    turn_step = -0x20;
                }
            }
        }
        if ((((S_80023260_3 *)waypoint)->unk_06 & 4) && (reached_point != 0)) {
            motion->velocity_z = -0x140000;
        }
        bias_step = turn_step >> 4;
        ((S_80023260_4 *)actor_ref)->unk_2A = (s16) ((u16) ((S_80023260_4 *)actor_ref)->unk_2A + turn_step);
        ((S_80023260_0 *)actor)->unk_1E = (u16) (((S_80023260_0 *)actor)->unk_1E + bias_step);
        ((S_80023260_0 *)actor)->unk_1C = (s16) ((u16) ((S_80023260_0 *)actor)->unk_1C + reached_point);
        if ((reached_point != 0) && (((S_80023260_3 *)waypoint)->unk_06 & 0x20)) {
            if (rand(bias_step, heading_error, turn_limit, turn_step) & 1) {
                ((S_80023260_3 *)waypoint)->unk_0E = (u16) (((S_80023260_3 *)waypoint)->unk_0E | 2);
            } else {
                ((S_80023260_3 *)waypoint)->unk_0E = (u16) (((S_80023260_3 *)waypoint)->unk_0E & 0xFFFD);
            }
        }
        if (((S_80023260_0 *)actor)->unk_1C >= 0xF) {
            ((S_80023260_0 *)actor)->unk_1A = 0U;
            ((S_80023260_0 *)actor)->unk_1C = 0;
        }
        break;
    case 2:
    case 0x101: /* states with no per-frame setup */
        break;
    }
    turn_bias = (s16) ((S_80023260_0 *)actor)->unk_1E;
    if (turn_bias > 0) {
        ((S_80023260_0 *)actor)->unk_1E = (u16) (((S_80023260_0 *)actor)->unk_1E - 1);
    } else if (turn_bias < 0) {
        ((S_80023260_0 *)actor)->unk_1E = (u16) (((S_80023260_0 *)actor)->unk_1E + 1);
    }
    damped_bias = (s16) ((S_80023260_0 *)actor)->unk_1E;
    if (damped_bias < -9) {
        clamp_value = -9;
        ((S_80023260_0 *)actor)->unk_1E = clamp_value;
    } else {
        clamp_value = damped_bias < 0xA;
        if (clamp_value == 0) {
            clamp_value = 9;
            ((S_80023260_0 *)actor)->unk_1E = clamp_value;
        }
    }
    abs_bias = (s16) ((S_80023260_0 *)actor)->unk_1E;
    if (abs_bias < 0) {
        abs_bias = 0 - abs_bias;
    }
    if ((abs_bias >= 6) && (((u16) ((S_80023260_0 *)actor)->unk_1A >> 1) & 1)) {
        spawn_person_radial_effects(motion);
    }
    {
        Stack24 ground_probe = *(Stack24 *)motion;
        surface_kind = ((S_80023260_5 *)(((((S_80023260_0 *)actor)->unk_24 * 2) + model_base)))->unk_3C;
        if ((surface_kind == 2) || (surface_kind == 6)) {
            ground_probe.field8 = 0xFE000000;
        }
        ground_height = query_lowered_transform_position(&ground_probe);
        motion->velocity_x =
            (s32) (rcos(((S_80023260_4 *)actor_ref)->unk_2A) * ((s32) ((S_80023260_0 *)actor)->unk_04 >> 0xC));
        motion->velocity_y =
            (s32) (rsin(((S_80023260_4 *)actor_ref)->unk_2A) * ((s32) ((S_80023260_0 *)actor)->unk_04 >> 0xC));
        if (ground_height < motion->z.w.i) {
            motion->z.w.i = ground_height;
            if (motion->velocity_z >= 0) {
                motion->velocity_z = 0;
            }
            if (((S_80023260_0 *)actor)->unk_08 & 1) {
                spawn_person_radial_effects(motion);
            }
            ((S_80023260_0 *)actor)->unk_08 = (s32) (((S_80023260_0 *)actor)->unk_08 & -2);
        } else {
            ((S_80023260_0 *)actor)->unk_08 = (s32) (((S_80023260_0 *)actor)->unk_08 | 1);
        }
        speed = ((S_80023260_0 *)actor)->unk_04;
        if (speed < -0x10000) {
            ((S_80023260_0 *)actor)->unk_04 = speed + 0x10000;
        } else if (speed > 0x10000) {
            ((S_80023260_0 *)actor)->unk_04 = speed - 0x10000;
        } else {
            ((S_80023260_0 *)actor)->unk_04 = 0;
        }
        motion->velocity_z = (s32) (motion->velocity_z + 0x20000);
        final_state = ((S_80023260_0 *)actor)->unk_18.u;
        if (final_state != 0) {
            update_directional_record(actor_ref, actor, sprite);
        }
    }
}
