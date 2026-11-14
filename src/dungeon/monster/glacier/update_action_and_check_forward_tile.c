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
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "sdk/libc.h"

typedef struct {
    s16 x;
    s16 y;
} Pair16;

void select_record_entry_and_value(void *state_data, void *entry_data, short index);

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);


extern void * find_species_actor_on_tile(ActorRecord *node, u16 key_a, u16 key_b, s16 range_center);
extern void create_facing_offset_object(ActorRecord *, ObjectPosition *, SpriteFrameState *);

extern u8 D_80170B48[];

#include "dungeon/monster/glacier.h"
#include "dungeon/monster/glacier_frames.h"
extern Pair16 glacier_direction_offsets[];



   /* work in update_action_and_check_forward_tile */

   /* transform in update_action_and_check_forward_tile */

/* Update the action sequence, spawning particles and checking the tile ahead. */
/* Emits particles, checks the tile ahead before creating a moving effect, spins while it runs, then spends
 * MP. */
void update_action_and_check_forward_tile(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *entity) {
    GteOffset offsets;
    u16 collision_flags;
    s16 timer;
    s16 floor_height;
    s32 particle_index;
    s32 x;
    s32 y;
    s32 target_x;
    s32 target_y;
    ObjectNodeHeader *particle;
    CollidingSpriteParticleBody *particle_work;
    SpriteFrameState *sprite;
    ObjectPosition *particle_transform;
    SpriteFrameState *owner;
    Pair16 *directions;
    s32 spin_angle;

#define motion motion

    switch (actor->action_phase) {
    case 0:
        if (animation->flags & 0x8000) {
            actor->action_phase = 2;
            animation->flags |= 0x6000;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        actor->action_timer = 0xE;
        actor->unk_AC.byte = 0;
        actor->unk_AC.bytes[1] = 0;
        actor->action_phase++;
        play_sound_if_enabled(0x80A);
        return;

    case 1:
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle = allocate_flagged_object_node(0x212);
            if (particle != 0) {

                particle_work = NODE_BODY(particle);
                particle_work->remaining.u = 0x28;
                particle->update_callback = D_80170B48;
                register_node(particle, project_sprite_chain);

                sprite = particle->sprite;
                sprite->flags |= 0x0C;
                sprite->tpage_abr = 0x60;
                sprite->flags |= 2;

                owner = NODE_HEADER(actor)->sprite;
                particle_transform = particle->position;
                if (resolve_record_orientation_or_fallback(owner->source, owner, &offsets.orientation, 1)) {
                    particle_transform->x.w.i = ((u16) motion->x.w.i);
                    particle_transform->y.w.i = ((u16) motion->y.w.i);
                    particle_transform->z.w.i = ((u16) motion->z.w.i);
                    particle_transform->x.w.i = (u16)particle_transform->x.w.i + (offsets.distance[0]);
                    particle_transform->y.w.i = (u16)particle_transform->y.w.i + (offsets.distance[1]);
                    particle_transform->z.w.i = (u16)particle_transform->z.w.i + (offsets.distance[2]);
                }

                x = (rand() & 0x1F) - 0x10;
                y = (rand() & 0x1F) - 0x10;
                particle_transform->x.w.i = (u16)particle_transform->x.w.i + (x);
                particle_transform->y.w.i = (u16)particle_transform->y.w.i + (y);
                particle_work->velocity_x = x << 12;
                particle_work->velocity_y = y << 12;
                particle_work->velocity_x += glacier_direction_offsets[(entity->facing >> 9) & 7].x << 16;
                particle_work->velocity_y += glacier_direction_offsets[(entity->facing >> 9) & 7].y << 16;
                particle_work->velocity_z = -(rand() + 0x50000);
                particle_work->acceleration_z = 0x6000;

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

        timer = actor->action_timer - 1;
        actor->action_timer = timer;
        if (timer > 0 && !(animation->flags & 0x8000)) {
            return;
        }
        actor->action_timer = 0x78;
        actor->action_phase++;
        return;

    case 2:
        if ((animation->unk_04 == 2 &&
             (animation->flags & 0x1000)) ||
            (animation->flags & 0x8000)) {
            animation->flags |= 0x800;
            actor->action_timer = 0x23;
        }

        timer = actor->action_timer - 1;
        actor->action_timer = timer;
        if (timer <= 0 || (animation->flags & 0x8000)) {
            actor->action_timer = 0;
            animation->flags &= 0xF7FF;
        }

        if (!(actor->action_timer != 0x0A && !(animation->flags & 0x8000))) {
            directions = glacier_direction_offsets;
            actor->unk_AC.bytes[1] = 0;
            x = motion->x.w.i +
                (directions[(((u16)entity->facing) >> 9) & 7].x << 6);
            y = motion->y.w.i +
                (directions[(((u16)entity->facing) >> 9) & 7].y << 6);
            target_x = (u16)x;
            target_y = (u16)y;

            if ((s16)check_left_tile_and_center_height(target_x, target_y,
                                   motion->z.w.i) != 0) {
                actor->unk_AC.bytes[1] = 1;
            }
            if (((s8)actor->unk_AC.bytes[1]) == 0) {
                get_offset_map_cell_value_and_flags(animation->tile_x,
                              animation->tile_y,
                              (entity->facing >> 9) & 7,
                              &collision_flags);
                if (collision_flags & 0x8400) {
                    actor->unk_AC.bytes[1] = 1;
                }
            }
            if (((s8)actor->unk_AC.bytes[1]) == 0) {
                if (find_species_actor_on_tile(entity,
                        animation->tile_x +
                            directions[(((u16)entity->facing) >> 9) & 7].x,
                        animation->tile_y +
                            directions[(((u16)entity->facing) >> 9) & 7].y,
                        motion->z.w.i) != 0) {
                    actor->unk_AC.bytes[1] = 1;
                }
            }
            if (((s8)actor->unk_AC.bytes[1]) == 0) {
                floor_height = sample_terrain_surface_height(target_x, target_y,
                                     motion->z.w.i - 0x20);
                if (floor_height >= 0x200 ||
                    floor_height > motion->z.w.i + 0x20 ||
                    floor_height < motion->z.w.i - 0x20) {
                    actor->unk_AC.bytes[1] = 1;
                }
            }
            if (((s8)actor->unk_AC.bytes[1]) == 0) {
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
        actor->action_timer = 0;
        if (((s8)actor->unk_AC.bytes[1]) == 0) {
            actor->action_phase++;
            return;
        }
        actor->action_phase = 0x10;
        return;

    case 3:
    {
        s16 spin_timer = actor->action_timer + 1;

        actor->action_timer = spin_timer;
        if ((spin_timer & 3) == 0) {

            spin_angle = entity->facing;
            spin_angle += 0x200;

            if (spin_angle >= 0x1000) {
                spin_angle -= 0x1000;
            }
            entity->facing = spin_angle;
        }
    }
        if (actor->action_timer != 0x13) {
            return;
        }
        actor->action_timer = 0;
        actor->action_phase++;
        return;

    case 4:
        timer = actor->action_timer + 1;
        actor->action_timer = timer;
        if (timer < 0x0A && !(animation->flags & 0x8000)) {
            return;
        }
        actor->action_timer = 0;
        actor->action_phase++;
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
            actor->action_timer = 0;
            actor->action_phase++;
        }
        return;

    case 6:
        timer = actor->action_timer + 1;
        actor->action_timer = timer;
        if (timer < 0x14 && !(animation->flags & 0x8000)) {
            return;
        }
        actor->action_timer = 0;
        actor->action_phase++;
        return;

    case 7:
    {
        s16 spin_timer = actor->action_timer + 1;

        actor->action_timer = spin_timer;
        if ((spin_timer & 3) == 0) {

            spin_angle = entity->facing;
            spin_angle += 0x200;

            if (spin_angle >= 0x1000) {
                spin_angle -= 0x1000;
            }
            entity->facing = spin_angle;
        }
    }
        if (actor->action_timer != 0x13) {
            return;
        }
        actor->action_timer = 0;
        actor->action_phase++;
        return;

    case 8:
        if (actor->unk_AC.signed_byte != 0x4D) {
            return;
        }
        actor->action_timer = 0;
        actor->action_phase++;
        return;

    case 9:
        spend_actor_mp(entity, 0x800);
        actor->unk_8C.address = update_glacier_actor_behavior;
        g_dungeon_status.active_actor = 0;
        (entity->action_flags) &= 0x7FFF;

    case 16:
        timer = actor->action_timer + 1;
        actor->action_timer = timer;
        if (timer >= 0x1E) {
            actor->action_phase = 9;
            actor->action_timer = 0;
        }
        return;

    default:
        break;
    }

    return;
}
