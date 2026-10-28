#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/kid.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"
#include "engine/node.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"

typedef u32 az_uptr;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172790_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172790_0;   /* arg3 in update_staged_actor_movement */

typedef struct S_80172790_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
} S_80172790_1;   /* arg0 in update_staged_actor_movement */

typedef struct S_80172790_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x2E];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_80172790_3;   /* part in update_staged_actor_movement */


extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern u8 directional_effect_entries[];
extern void *actor_update_node_cursor;
extern u8 kid_action_resume_address[];
extern u8 D_801743EC[];
extern u8 kid_alt_direction_frames[];
extern u8 D_80175160[];

/* Updates an actor's staged movement, particle effects, and return to its tile. */
/* Animates a backward leap and forward strike with particle trails, resolves damage, then recenters and
 * spends MP. */
void update_staged_actor_movement(void *action, ObjectPosition *motion, SpriteFrameState *tile, void *actor)
{
    s32 particle_x_offset;
    u8 *move_frames;
    s32 move_angle;
    s32 move_direction;
    u8 *idle_frames;
    s32 idle_angle;
    s32 idle_direction;
    s32 heading_byte;
    s32 direction_offset;
    s32 return_speed;
    s32 return_speed_2;
    s32 state;
    s32 random_offset;
    u16 flags;
    s32 vertical_speed;
    s32 origin_x;
    s32 origin_y;
    s32 x_speed;
    s32 y_speed;
    s32 z_speed;
    u32 color;
    s32 sprite_params;
    u8 *sprite_data;
    s32 x_step;
    s32 y_step;
    s32 particle_y;
    s32 heading_raw;
    ObjectNodeHeader *particle;
    S_80172790_3 *particle_motion;
    SpriteFrameState *sprite;
    u8 *x_step_entry;
    u8 *x_step_base;

    heading_raw = ((S_80172790_0 *)actor)->unk_2A.s;
    x_step_entry = (u8 *)dir_step_x;
    heading_byte = (u32)heading_raw >> 8;
    direction_offset = heading_byte & 0xE;
    x_step_base = x_step_entry;
    x_step = *(s16 *)((u8 *)((az_uptr)direction_offset + (az_uptr)x_step_base));
    y_step = *(s16 *)(direction_offset + (u8 *)dir_step_y);
    ((S_80172790_1 *)action)->unk_96.s--;

    if ((u32)(((S_80172790_1 *)action)->unk_9B - 1) < 3U) {
        heading_byte = 15;
        particle_x_offset = (x_step << 5) - 8;
        do {
            particle = allocate_list_node(0x312, &scene_object_list_anchor.next);
            if (particle != NULL) {
                register_node(particle, project_sprite_chain);
                particle_motion = (u8 *)particle + 0x20;
                particle->update_callback = D_801743EC;
                sprite = particle->sprite;
                if (((S_80172790_1 *)action)->unk_9B < 3U) {
                    particle_motion->unk_0C = ((u16) motion->x.w.i) + (rand() & 0xF) - 8;
                    random_offset = rand();
                    origin_x = -0x500;
                    particle_y = ((u16) motion->y.w.i);
                    random_offset &= 0xF;
                    particle_motion->unk_16 = origin_x;
                    particle_y += random_offset;
                    particle_y -= 8;
                } else {
                    particle_motion->unk_0C = ((u16) motion->x.w.i) + (rand() & 0xF) + particle_x_offset;
                    random_offset = rand();
                    origin_x = -0x200;
                    particle_y = ((u16) motion->y.w.i);
                    random_offset &= 0xF;
                    particle_motion->unk_16 = origin_x;
                    particle_y += random_offset;
                    random_offset = (y_step << 5) - 8;
                    particle_y += random_offset;
                }
                particle_motion->unk_0E = particle_y;
                particle_motion->unk_10 = ((u16) motion->z.w.i) + 8;
                particle_motion->unk_14 = rand();
                heading_raw = ((S_80172790_0 *)actor)->unk_2A.s;
                color = 0x00C00000;
                particle_motion->unk_4C = 0;
                particle_motion->unk_48 = 0;
                particle_motion->unk_18 = heading_raw;
                (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
                (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
                (*(s16 *)((u8 *)sprite + 0x10)) = 0x60;
                sprite_data = directional_effect_entries;
                (*(void **)((u8 *)sprite + 0)) = sprite_data;
                (*(u16 *)((u8 *)sprite + 0x14)) |= 0xC;
                sprite_params = *(s32 *)(sprite_data + 4);
                color |= 0xC0C0;
                sprite->unk_04 = 0;
                sprite->frame_ticks = 0;
                (*(s32 *)((u8 *)sprite + 0xC)) = color;
                sprite->source = sprite_params;
            }
            heading_byte--;
        } while (heading_byte >= 0);
    }

    state = ((S_80172790_1 *)action)->unk_9B;
    switch (state) {
    case 0:
        flags = tile->flags;
        if (flags & 0x8000) {
            ((S_80172790_1 *)action)->unk_9B = 0xFF;
            tile->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, tile, ((S_80172790_0 *)actor)->unk_2A.u, 1);
            return;
        }
        if (flags & 0xE000) {
            move_frames = D_80175160;
            (tile->frameTable) = move_frames;
            move_angle = g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172790_0 *)actor)->unk_2A.u;
            move_direction = ((move_angle + 0x100) >> 9) & 7;
            select_sprite_entry(tile, move_frames[move_direction], 0);
            motion->velocity_x = (-x_step) << 0x12;
            motion->velocity_y = (-y_step) << 0x12;
            ((S_80172790_1 *)action)->unk_98 |= 8;
            ((S_80172790_0 *)actor)->unk_1C &= ACTOR_GROUNDED_CLEAR_MASK;
            ((S_80172790_0 *)actor)->unk_1C &= 0xFFFBFFFF;
            ((S_80172790_1 *)action)->unk_96.s = 4;
            motion->velocity_z = 0xFFFC0000;
            ((S_80172790_1 *)action)->unk_9B++;
            return;
        }
        return;

    case 1:
        vertical_speed = motion->velocity_z;
        motion->velocity_z = vertical_speed + (vertical_speed >> 2);
        if (((S_80172790_1 *)action)->unk_96.u <= 0) {
            ((S_80172790_1 *)action)->unk_96.u = 3;
            ((S_80172790_1 *)action)->unk_9B++;
            return;
        }
        return;

    case 2:
        x_speed = motion->velocity_x;
        y_speed = motion->velocity_y;
        motion->velocity_x = x_speed - (x_speed >> 2);
        z_speed = motion->velocity_z;
        motion->velocity_y = y_speed - (y_speed >> 2);
        motion->velocity_z = z_speed - (z_speed >> 2);
        if (((S_80172790_1 *)action)->unk_96.u <= 0) {
            ((S_80172790_1 *)action)->unk_96.u = 7;
            motion->velocity_x = x_step << 0x12;
            motion->velocity_y = y_step << 0x12;
            motion->velocity_z = 0x30000;
            play_sound_if_enabled(0x80E);
        } else {
            return;
        }
        ((S_80172790_1 *)action)->unk_9B++;
        return;

    case 3:
        motion->velocity_x += x_step << 0x12;
        motion->velocity_y += y_step << 0x12;
        if (((S_80172790_1 *)action)->unk_96.u < 2) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        }
        if (((S_80172790_1 *)action)->unk_96.u == 1) {
            resolve_attack_damage_and_effects(actor, tile, ((S_80172790_0 *)actor)->unk_2A.u, 1);
            play_sound_if_enabled(0x808);
        }
        if (((S_80172790_1 *)action)->unk_96.u <= 0) {
            motion->velocity_z = 0xFFF60000;
            ((S_80172790_1 *)action)->unk_96.u = 0x14;
            ((S_80172790_1 *)action)->unk_9B = 0xFF;
        }
        return;

    case 0xFF:
        return_speed_2 = tile->tile_x << 6;
        origin_x = motion->x.w.i - 0x20;
        return_speed_2 -= origin_x;
        return_speed_2 <<= 0xF;
        return_speed_2 >>= 1;
        motion->velocity_x = return_speed_2;
        return_speed = tile->tile_y << 6;
        origin_y = motion->y.w.i - 0x20;
        return_speed -= origin_y;
        return_speed <<= 0xF;
        return_speed >>= 1;
        motion->velocity_y = return_speed;
        if (((S_80172790_1 *)action)->unk_96.u >= 0xA) {
            motion->velocity_z += 0x10000;
        } else {
            motion->velocity_z = -((S_80172790_1 *)action)->unk_92 << 0xD;
        }
        if (((S_80172790_1 *)action)->unk_96.u > 0 && !(tile->flags & 0x8000)) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        ((S_80172790_0 *)actor)->unk_1C |= 0x40000;
        set_record_integer_tile_center(motion, tile->tile_x, tile->tile_y);
        spend_actor_mp(actor, 0x100);
        ((S_80172790_1 *)action)->unk_8C = kid_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        motion->velocity_z = 0;
        ((S_80172790_1 *)action)->unk_98 &= 0xFFF7;
        ((S_80172790_0 *)actor)->unk_1C |= ACTOR_GROUNDED;
        ((S_80172790_1 *)action)->unk_A8 = 7;
        idle_frames = kid_alt_direction_frames;
        (tile->frameTable) = idle_frames;
        idle_angle = g_game_work.view.camera_rotation.parts.viewAngle + ((S_80172790_0 *)actor)->unk_2A.u;
        idle_direction = ((idle_angle + 0x100) >> 9) & 7;
        select_sprite_entry(tile, idle_frames[idle_direction], 2);
        if (((S_80172790_0 *)actor)->unk_6D == 0) {
            ((S_80172790_0 *)actor)->unk_46 &= 0x7FFF;
        } else {
            actor_update_node_cursor = (u8 *)actor - 0x20;
        }
        return;

    default:
        return;
    }
    return;
}
