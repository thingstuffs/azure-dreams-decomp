#include "common.h"
#include "town/minigame/keima.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "slus.h"
#include "sdk/libgte.h"
#include "town/minigame/entry_state.h"
#include "town/person/position.h"
#include "town/person/effects.h"






void update_directional_record();      /* extern */
s32 rand();              /* extern */
void add_motion_deltas_to_position();                      /* extern */

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} Stack24;

extern s32 loaded_town_resource_attributes[];
extern u8 path_actor_direction_frames[];

/* Updates path following, turning, sprite state, and ground movement. */
void update_path_following_actor(KeimaPathActor *actor, ObjectPosition *motion, SpriteFrameState *sprite) {
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
    KeimaState *model_base;
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
    KeimaPath *paths;
    void *position_ref;
    KeimaPathPoint *waypoint;
    KeimaPathActor *actor_ref;
    u8 *directions;

    actor_ref = actor;
    paths = town_minigame_path_records;
    model_base = actor->owner;
    waypoint = paths[actor->path_index].points + actor->waypoint_index;
    advance_sprite_animation_and_textures(sprite);
    position_ref = &actor->cycles;
    advance_bounded_entry_index(motion, position_ref);
    fill_eligible_negative_slots(model_base, position_ref, actor->lane);
    add_motion_deltas_to_position(motion);
    reached_point = 0;
    motion->x.v = (s32) (motion->x.v
        + actor->impulse_x);
    motion->y.v = (s32) (motion->y.v
        + actor->impulse_y);
    offset_x = actor->impulse_x;
    offset_y = actor->impulse_y;
    old_state = actor->state.u;
    actor->impulse_x = offset_x >> 1;
    actor->impulse_y = offset_y >> 1;
    state = actor->state.s;
    idle_state = 2;
    switch (state) {
    case 0:
        actor->state.u = old_state + 1;
        return;
    case 1:
        actor->facing.s = 0x800;
        sprite_config = loaded_town_resource_attributes[0];
        directions = path_actor_direction_frames;
        sprite->frameTable = directions;
        sprite->animation_resource = sprite_config;
        select_sprite_entry(sprite, path_actor_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing.s + 0x100) >> 9) & 7],
            0);
        actor->state.u = (u16) (actor->state.u + 1);
        break;
    case 3:
        sprite->frameTable = path_actor_direction_frames - 8;
        select_sprite_entry(sprite, (path_actor_direction_frames - 8)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing.s + 0x100)
            >> 9) & 7], 0);
        actor->state.u = idle_state;
        break;
    case 0x100:
        path_ticks = actor->path_ticks + 1;
        actor->path_ticks = path_ticks;
        if ((actor->speed <= 0x200000) && (waypoint->flags & 2)) {
            if (((s16) path_ticks % (s16) paths[actor->path_index].effect_period) == 0) {
                spawn_person_radial_effects(motion);
                actor->speed = (s32) (actor->speed + 0x80000);
            }
        }
        path_speed = actor->speed;
        if ((path_speed <= 0xFFFFF) && (waypoint->flags & 1)) {
            actor->speed = (s32) (path_speed + 0x20000);
        }
        heading = actor_ref->facing.s;
        path_heading = waypoint->heading;
        angle_delta = heading - path_heading;
        turn_step = 0;
        while (angle_delta >= 0x801) {
            angle_delta -= 0x1000;
        }
        while (angle_delta < -0x800) {
            angle_delta += 0x1000;
        }
        heading_error = angle_delta;
        path_flags = waypoint->flags;
        path_flag = path_flags & 8;
        if (path_flag != 0) {
            path_flag = path_flags & 0x10;
            if (path_flag != 0) {
                target_x = waypoint->x;
                turn_limit = town_minigame_path_records[actor->path_index].turn_limit;
                if (motion->x.w.i >= target_x) {
                    reached_point = 1;
                }
            } else {
                turn_limit = 0 - town_minigame_path_records[actor->path_index].turn_limit;
                if (motion->x.w.i <= waypoint->x) {
                    reached_point = 1;
                }
            }
            steer_y = waypoint->y;
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
                target_y = waypoint->y;
                turn_limit = town_minigame_path_records[actor->path_index].turn_limit;
                if (motion->y.w.i >= target_y) {
                    reached_point = 1;
                }
            } else {
                turn_limit = 0 - town_minigame_path_records[actor->path_index].turn_limit;
                if (motion->y.w.i <= waypoint->y) {
                    reached_point = 1;
                }
            }
            steer_x = waypoint->x;
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
        if ((waypoint->flags & 4) && (reached_point != 0)) {
            motion->velocity_z = -0x140000;
        }
        bias_step = turn_step >> 4;
        actor_ref->facing.s = (s16) ((u16) actor_ref->facing.s + turn_step);
        actor->turn_bias = (u16) (actor->turn_bias + bias_step);
        actor->waypoint_index = (s16) ((u16) actor->waypoint_index + reached_point);
        if ((reached_point != 0) && (waypoint->flags & 0x20)) {
            if (rand(bias_step, heading_error, turn_limit, turn_step) & 1) {
                waypoint[1].flags = (u16) (waypoint[1].flags | 2);
            } else {
                waypoint[1].flags = (u16) (waypoint[1].flags & 0xFFFD);
            }
        }
        if (actor->waypoint_index >= 0xF) {
            actor->path_ticks = 0U;
            actor->waypoint_index = 0;
        }
        break;
    case 2:
    case 0x101: /* states with no per-frame setup */
        break;
    }
    turn_bias = (s16) actor->turn_bias;
    if (turn_bias > 0) {
        actor->turn_bias = (u16) (actor->turn_bias - 1);
    } else if (turn_bias < 0) {
        actor->turn_bias = (u16) (actor->turn_bias + 1);
    }
    damped_bias = (s16) actor->turn_bias;
    if (damped_bias < -9) {
        clamp_value = -9;
        actor->turn_bias = clamp_value;
    } else {
        clamp_value = damped_bias < 0xA;
        if (clamp_value == 0) {
            clamp_value = 9;
            actor->turn_bias = clamp_value;
        }
    }
    abs_bias = (s16) actor->turn_bias;
    if (abs_bias < 0) {
        abs_bias = 0 - abs_bias;
    }
    if ((abs_bias >= 6) && (((u16) actor->path_ticks >> 1) & 1)) {
        spawn_person_radial_effects(motion);
    }
    {
        Stack24 ground_probe = *(Stack24 *)motion;
        surface_kind = model_base->slot[actor->lane];
        if ((surface_kind == 2) || (surface_kind == 6)) {
            ground_probe.field8 = 0xFE000000;
        }
        ground_height = query_lowered_transform_position(&ground_probe);
        motion->velocity_x =
            (s32) (rcos(actor_ref->facing.s) * ((s32) actor->speed >> 0xC));
        motion->velocity_y =
            (s32) (rsin(actor_ref->facing.s) * ((s32) actor->speed >> 0xC));
        if (ground_height < motion->z.w.i) {
            motion->z.w.i = ground_height;
            if (motion->velocity_z >= 0) {
                motion->velocity_z = 0;
            }
            if (actor->flags & 1) {
                spawn_person_radial_effects(motion);
            }
            actor->flags = (s32) (actor->flags & -2);
        } else {
            actor->flags = (s32) (actor->flags | 1);
        }
        speed = actor->speed;
        if (speed < -0x10000) {
            actor->speed = speed + 0x10000;
        } else if (speed > 0x10000) {
            actor->speed = speed - 0x10000;
        } else {
            actor->speed = 0;
        }
        motion->velocity_z = (s32) (motion->velocity_z + 0x20000);
        final_state = actor->state.s;
        if (final_state != 0) {
            update_directional_record(actor_ref, actor, sprite);
        }
    }
}
