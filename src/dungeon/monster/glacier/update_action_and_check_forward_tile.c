#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/level.h"
#include "engine/node.h"
#include "dungeon/player/object.h"

typedef struct {
    s16 x;
    s16 y;
} Pair16;

extern void select_record_entry_and_value(void *, void *, s32);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 rand(void);
extern void get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void * find_first_entry_matching_keys(void *node, u16 key_a, u16 key_b, s16 range_center);
extern void create_facing_offset_object(void *, void *, void *);

extern u8 D_80170B48[];

#include "dungeon/monster/glacier.h"
extern u8 glacier_frame_set_1[];
extern Pair16 glacier_direction_offsets[];

typedef struct S_801757E0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801757E0_0_pre;   /* the 0x14 bytes before arg0 in update_action_and_check_forward_tile, addressed as arg0[-1] */

typedef struct S_801757E0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u8 u; s8 s; } unk_AC;   /* accessed as both */
    union { u8 u; s8 s; } unk_AD;   /* accessed as both */
} S_801757E0_0;   /* arg0 in update_action_and_check_forward_tile */

typedef struct S_801757E0_3 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    u8 pad_20[0x30];
    union { s32 n; s32 v; } unk_50;   /* accessed as both */
    union { s32 n; s32 v; } unk_54;   /* accessed as both */
    s32 unk_58;
    u8 pad_5C[0x8];
    s32 unk_64;
} S_801757E0_3;   /* work in update_action_and_check_forward_tile */

typedef struct S_801757E0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801757E0_6;   /* owner in update_action_and_check_forward_tile */

   /* transform in update_action_and_check_forward_tile */

/* Update the action sequence, spawning particles and checking the tile ahead. */
/* Emits particles, checks the tile ahead before creating a moving effect, spins while it runs, then spends
 * MP. */
void update_action_and_check_forward_tile(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *entity) {
    u16 offsets[3];
    u16 collision_flags;
    s16 timer;
    s16 floor_height;
    s32 particle_index;
    s32 x;
    s32 y;
    s32 target_x;
    s32 target_y;
    ObjectNodeHeader *particle;
    void *particle_work;
    SpriteFrameState *sprite;
    ObjectPosition *particle_transform;
    void *owner;
    Pair16 *directions;
    s32 spin_angle;

#define motion motion

    switch (actor->action_phase.u) {
    case 0:
        if (animation->flags & 0x8000) {
            actor->action_phase.u = 2;
            animation->flags |= 0x6000;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        ((S_801757E0_0 *)actor)->unk_96.u = 0xE;
        ((S_801757E0_0 *)actor)->unk_AC.u = 0;
        ((S_801757E0_0 *)actor)->unk_AD.u = 0;
        actor->action_phase.u++;
        play_sound_if_enabled(0x80A);
        return;

    case 1:
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle = allocate_flagged_object_node(0x212);
            if (particle != 0) {

                particle_work = (u8 *)particle;
                particle_work += 0x20;
                ((ObjectNodeHeader *)particle_work)->flags = 0x28;
                particle->update_callback = D_80170B48;
                register_node(particle, project_sprite_chain);

                sprite = particle->sprite;
                sprite->flags |= 0x0C;
                sprite->tpage_abr = 0x60;
                sprite->flags |= 2;

                owner = ((S_801757E0_0_pre *)actor)[-1].unk_00;
                particle_transform = particle->position;
                if (resolve_record_orientation_or_fallback(((S_801757E0_6 *)owner)->unk_08, owner, offsets, 1)) {
                    particle_transform->x.w.i = ((u16) motion->x.w.i);
                    particle_transform->y.w.i = ((u16) motion->y.w.i);
                    particle_transform->z.w.i = ((u16) motion->z.w.i);
                    particle_transform->x.w.i = (u16)particle_transform->x.w.i + (offsets[0]);
                    particle_transform->y.w.i = (u16)particle_transform->y.w.i + (offsets[1]);
                    particle_transform->z.w.i = (u16)particle_transform->z.w.i + (offsets[2]);
                }

                x = (rand() & 0x1F) - 0x10;
                y = (rand() & 0x1F) - 0x10;
                particle_transform->x.w.i = (u16)particle_transform->x.w.i + (x);
                particle_transform->y.w.i = (u16)particle_transform->y.w.i + (y);
                ((S_801757E0_3 *)particle_work)->unk_50.n = x << 12;
                ((S_801757E0_3 *)particle_work)->unk_54.n = y << 12;
                ((S_801757E0_3 *)particle_work)->unk_50.n += glacier_direction_offsets[(((u16)entity->facing) >> 9) & 7].x << 16;
                ((S_801757E0_3 *)particle_work)->unk_54.n += glacier_direction_offsets[(((u16)entity->facing) >> 9) & 7].y << 16;
                ((S_801757E0_3 *)particle_work)->unk_58 = -(rand() + 0x50000);
                ((S_801757E0_3 *)particle_work)->unk_64 = 0x6000;

                sprite = particle->sprite;
                sprite->scale_x = 0x800;
                sprite->scale_y = 0x800;
                sprite->color.c.b = 0x80;
                sprite->color.c.g = 0x80;
                sprite->color.c.r = 0x80;
                sprite->clut = 0x7DCF;
                sprite->flags |= 0x100;
                select_record_entry_and_value(sprite, effect_sprite_sources, 0);
            }
        }

        timer = ((S_801757E0_0 *)actor)->unk_96.u - 1;
        ((S_801757E0_0 *)actor)->unk_96.u = timer;
        if (timer > 0 && !(animation->flags & 0x8000)) {
            return;
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0x78;
        actor->action_phase.u++;
        return;

    case 2:
        if ((animation->unk_04 == 2 &&
             (animation->flags & 0x1000)) ||
            (animation->flags & 0x8000)) {
            animation->flags |= 0x800;
            ((S_801757E0_0 *)actor)->unk_96.u = 0x23;
        }

        timer = ((S_801757E0_0 *)actor)->unk_96.u - 1;
        ((S_801757E0_0 *)actor)->unk_96.u = timer;
        if (timer <= 0 || (animation->flags & 0x8000)) {
            ((S_801757E0_0 *)actor)->unk_96.u = 0;
            animation->flags &= 0xF7FF;
        }

        if (!(((S_801757E0_0 *)actor)->unk_96.s != 0x0A && !(animation->flags & 0x8000))) {
            directions = glacier_direction_offsets;
            ((S_801757E0_0 *)actor)->unk_AD.s = 0;
            x = motion->x.w.i +
                (directions[(((u16)entity->facing) >> 9) & 7].x << 6);
            y = motion->y.w.i +
                (directions[(((u16)entity->facing) >> 9) & 7].y << 6);
            target_x = (u16)x;
            target_y = (u16)y;

            if ((s16)check_left_tile_and_center_height(target_x, target_y,
                                   motion->z.w.i) != 0) {
                ((S_801757E0_0 *)actor)->unk_AD.s = 1;
            }
            if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
                get_offset_map_cell_value_and_flags(animation->tile_x,
                              animation->tile_y,
                              (((u16)entity->facing) >> 9) & 7,
                              &collision_flags);
                if (collision_flags & 0x8400) {
                    ((S_801757E0_0 *)actor)->unk_AD.s = 1;
                }
            }
            if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
                if (find_first_entry_matching_keys(entity,
                        animation->tile_x +
                            directions[(((u16)entity->facing) >> 9) & 7].x,
                        animation->tile_y +
                            directions[(((u16)entity->facing) >> 9) & 7].y,
                        motion->z.w.i) != 0) {
                    ((S_801757E0_0 *)actor)->unk_AD.s = 1;
                }
            }
            if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
                floor_height = sample_terrain_surface_height(target_x, target_y,
                                     motion->z.w.i - 0x20);
                if (floor_height >= 0x200 ||
                    floor_height > motion->z.w.i + 0x20 ||
                    floor_height < motion->z.w.i - 0x20) {
                    ((S_801757E0_0 *)actor)->unk_AD.s = 1;
                }
            }
            if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
                create_facing_offset_object(actor, motion, animation);
            }
        }
        if (!(animation->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, animation->tile_x, animation->tile_y);

        if (animation->frameTable != glacier_direction_frames) {
            animation->frameTable = glacier_direction_frames;
            animation->flags &= 0xF7FF;
            select_sprite_entry(animation,
                (*(u8 **)&animation->frameTable)
                    [((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        if (((S_801757E0_0 *)actor)->unk_AD.s == 0) {
            actor->action_phase.u++;
            return;
        }
        actor->action_phase.u = 0x10;
        return;

    case 3:
    {
        s16 spin_timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;

        ((S_801757E0_0 *)actor)->unk_96.u = spin_timer;
        if ((spin_timer & 3) == 0) {

            spin_angle = entity->facing;
            spin_angle += 0x200;

            if (spin_angle >= 0x1000) {
                spin_angle -= 0x1000;
            }
            entity->facing = spin_angle;
        }
    }
        if (((S_801757E0_0 *)actor)->unk_96.s != 0x13) {
            return;
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        actor->action_phase.u++;
        return;

    case 4:
        timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;
        ((S_801757E0_0 *)actor)->unk_96.u = timer;
        if (timer < 0x0A && !(animation->flags & 0x8000)) {
            return;
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        actor->action_phase.u++;
        (animation->frameTable) = glacier_frame_set_1;
        select_sprite_entry(animation,
            glacier_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;

    case 5:
        if (animation->flags & 0xE000) {
            (animation->frameTable) = glacier_direction_frames;
            select_sprite_entry(animation,
                glacier_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            ((S_801757E0_0 *)actor)->unk_96.u = 0;
            actor->action_phase.u++;
        }
        return;

    case 6:
        timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;
        ((S_801757E0_0 *)actor)->unk_96.u = timer;
        if (timer < 0x14 && !(animation->flags & 0x8000)) {
            return;
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        actor->action_phase.u++;
        return;

    case 7:
    {
        s16 spin_timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;

        ((S_801757E0_0 *)actor)->unk_96.u = spin_timer;
        if ((spin_timer & 3) == 0) {

            spin_angle = entity->facing;
            spin_angle += 0x200;

            if (spin_angle >= 0x1000) {
                spin_angle -= 0x1000;
            }
            entity->facing = spin_angle;
        }
    }
        if (((S_801757E0_0 *)actor)->unk_96.s != 0x13) {
            return;
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        actor->action_phase.u++;
        return;

    case 8:
        if (((S_801757E0_0 *)actor)->unk_AC.s != 0x4D) {
            return;
        }
        ((S_801757E0_0 *)actor)->unk_96.u = 0;
        actor->action_phase.u++;
        return;

    case 9:
        spend_actor_mp(entity, 0x800);
        ((S_801757E0_0 *)actor)->unk_8C = update_actor_timed_effects;
        g_dungeon_status.active_actor = 0;
        (entity->action_flags) &= 0x7FFF;

    case 16:
        timer = ((S_801757E0_0 *)actor)->unk_96.u + 1;
        ((S_801757E0_0 *)actor)->unk_96.u = timer;
        if (timer >= 0x1E) {
            actor->action_phase.u = 9;
            ((S_801757E0_0 *)actor)->unk_96.u = 0;
        }
        return;

    default:
        break;
    }

    return;
}
