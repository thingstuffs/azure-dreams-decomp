#include "engine/graphics/select_sprite_entry_api.h"
#include "slus.h"
#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "engine/texture.h"
#include "dungeon/actor.h"
#include "sdk/libgte.h"
#include "dungeon/data.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);

extern void D_8016B4D4(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg);
extern Callback D_8016E168[];



/* Updates entity behavior, movement, directional animation, and ground-relative height. */
/* Runs Hikewne state callbacks from D_8016E168, alternates its bobbing idle frames, and resolves ground
 * contact. */
void update_entity_behavior_movement_and_height(ActorRecord *entity, ObjectPosition *motion, SpriteFrameState *sprite)
{
    ActorRecord *entity_state = entity;
    s16 previous_state;
    s16 sprite_direction;
    s16 anim_direction;
    s32 height_offset;
    s32 signed_tick;
    u32 bob_angle;
    s16 ground_height;
    s16 ground_delta;
    u16 sprite_flags;
    register s32 bob_tick;
    u32 entity_flags;
    s32 bob_offset;
    ActorActionHandler pause_callback;
    ActorActionHandler update_callback;

    if (g_dungeon_status.flags & 0x2000) {
        pause_callback = entity->unk_8C.handler;
        if (pause_callback == (ActorActionHandler)D_8016B4D4) {
            pause_callback(entity, motion, sprite, entity);
            return;
        }
        entity->movement_queue_state &= 0x7F;
        return;
    }

    previous_state = entity->pending_turn_updates;
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = entity->unk_8C.handler;
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    D_8016E168[entity->action_id](entity, motion, sprite, entity);
    if ((s16)previous_state != entity->pending_turn_updates) {
        try_move_actor_to_valid_position(entity, motion, sprite, entity);
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (!(entity->flags1C & 0x40000) &&
        !(entity->action_state_flags & 8)) {
        motion->velocity_z += entity->fall_ticks * 0x14000;
        entity->fall_ticks++;
    } else {
        entity->fall_ticks = 0;
    }
    entity->unk_90.value += motion->velocity_z;
    sprite_flags = sprite->flags;

    if (!(sprite_flags & 0x8000)) {
        sprite_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_state->facing + 0x100) >> 9) & 7;
        anim_direction = sprite_direction;
        if (entity->sprite_direction != anim_direction) {
            select_indirect_table_entry(sprite,
                (*((*(u8 **)&sprite->frameTable) + (anim_direction))),
                sprite->unk_04);
            entity->sprite_direction = sprite_direction;
        }
        {
            u32 flip_flags;
            if (dir_sprite_flag[anim_direction] != 0) {
                flip_flags = sprite->flags | 1;
            } else {
                flip_flags = sprite->flags & 0xFFFE;
            }
            sprite->flags = flip_flags;
        }
        apply_monster_koyaw_data(entity_state->flags1C, (u8 *)sprite + 0xC);
        if (!(entity_state->flags1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            entity_state->flags1C &= 0xFFFBFFFF;
        }

        {
            u32 airborne_flags;
            airborne_flags = entity_state->flags1C & 0xF7FFFFFF;
            entity_state->flags1C = airborne_flags;
            airborne_flags &= 0x40000;
            if (!airborne_flags) {
                s32 offset = entity->unk_A0.value;
                entity->unk_9E = 0;
                entity->unk_A0.value = 0;
                entity->unk_90.value -= offset;
                if (!(entity->action_state_flags & 8)) {
                    ground_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                        ((u16) motion->y.w.i),
                        (s16)(entity_state->ground_height - 0x20));
                    ground_delta = ground_height - entity_state->ground_height;
                    if (ground_delta < entity->unk_90.parts.high) {
                        entity->unk_90.parts.high = ground_delta;
                        entity->fall_ticks = 0;
                        motion->velocity_z = 0;
                        entity_state->flags1C |= 0x08000000;
                    }
                }
            } else {
                if (!(sprite->flags & 0x40)) {
                    if (*(u8 **)&sprite->frameTable == hikewne_frame_set_14) {
                        if (*(u16 *)&sprite->unk_04 == 0x100) {
                            entity->unk_9E = 0;
                        }
                        bob_tick = entity->unk_9E++;
                        signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = signed_tick * 0xE3;
                        entity->unk_A0.value = rsin(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_frame_set_15;
                            select_sprite_entry(sprite, hikewne_frame_set_15[((g_game_work.view.camera_rotation.parts.viewAngle
                                + entity_state->facing + 0x100) >> 9) & 7], 0);
                        }
                    } else if (*(u8 **)&sprite->frameTable == hikewne_frame_set_15) {
                        bob_tick = entity->unk_9E++;
                        signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = signed_tick * 0xE3;
                        entity->unk_A0.value = rsin(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_frame_set_14;
                            select_sprite_entry(sprite, hikewne_frame_set_14[((g_game_work.view.camera_rotation.parts.viewAngle
                                + entity_state->facing + 0x100) >> 9) & 7], 0);
                        }
                    }
                }

                if (!(entity->action_state_flags & 8)) {
                    s32 height_adjust = -0x20;
                    height_offset = entity->unk_90.parts.high;
                    entity_flags = (u16)entity->unk_90.parts.high;
                    if (height_adjust < height_offset) {
                        height_adjust = entity_flags - 8;
                        entity->unk_90.parts.high = height_adjust;
                    } else {
                        height_adjust = height_offset < -0x28;
                        if (height_adjust) {
                            height_adjust = entity_flags + 8;
                            entity->unk_90.parts.high = height_adjust;
                        }
                    }
                }
            }
        }
    } else {
        sprite->flags = (sprite_flags & 0x800)
            ? (sprite_flags & 0x8FFF)
        : (sprite_flags | 0x7000);
        entity_state->flags1C &= 0xF7FFFFFF;
        if (!(entity_state->flags1C & 0x40000)) {
            bob_offset = entity->unk_A0.value;
            entity->unk_9E = 0;
            entity->unk_A0.value = 0;
            entity->unk_90.value -= bob_offset;
            if (!(entity->action_state_flags & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                    ((u16) motion->y.w.i),
                    (s16)(entity_state->ground_height - 0x20));
                ground_delta = ground_height - entity_state->ground_height;
                if (ground_delta < entity->unk_90.parts.high) {
                    entity->unk_90.parts.high = ground_delta;
                    entity->fall_ticks = 0;
                    motion->velocity_z = 0;
                    entity_state->flags1C |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                if (*(u8 **)&sprite->frameTable == hikewne_frame_set_14) {
                    if (*(u16 *)&sprite->unk_04 == 0x100) {
                        entity->unk_9E = 0;
                    }
                    bob_tick = entity->unk_9E++;
                    signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = signed_tick * 0xE3;
                    entity->unk_A0.value = rsin(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_frame_set_15;
                        select_sprite_entry(sprite, hikewne_frame_set_15[((g_game_work.view.camera_rotation.parts.viewAngle
                            + entity_state->facing + 0x100) >> 9) & 7], 0);
                    }
                } else if (*(u8 **)&sprite->frameTable == hikewne_frame_set_15) {
                    bob_tick = entity->unk_9E++;
                    signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = signed_tick * 0xE3;
                    entity->unk_A0.value = rsin(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_frame_set_14;
                        select_sprite_entry(sprite, hikewne_frame_set_14[((g_game_work.view.camera_rotation.parts.viewAngle
                            + entity_state->facing + 0x100) >> 9) & 7], 0);
                    }
                }
            }

            if (!(entity->action_state_flags & 8)) {
                s32 height_adjust = -0x20;
                height_offset = entity->unk_90.parts.high;
                entity_flags = (u16)entity->unk_90.parts.high;
                if (height_adjust < height_offset) {
                    height_adjust = entity_flags - 8;
                    entity->unk_90.parts.high = height_adjust;
                } else {
                    height_adjust = height_offset < -0x28;
                    if (height_adjust) {
                        height_adjust = entity_flags + 8;
                        entity->unk_90.parts.high = height_adjust;
                    }
                }
            }
        }
    }

    entity_flags = entity_state->flags1C;
    if (entity_flags & 0x40000000) {
        entity_state->flags1C = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (sprite->tile_x << 6) | 0x20,
            (sprite->tile_y << 6) | 0x20,
            (s16)(entity_state->ground_height - 0x20));
        if (ground_height < 0x200) {
            entity->unk_90.parts.high =
                (entity_state->ground_height - ground_height) +
                entity->unk_90.parts.high;
            entity_state->ground_height = ground_height;
        }
    }

    motion->z.w.i = entity_state->ground_height +
        entity->unk_90.parts.high - entity->unk_A0.parts.high;
    sprite->flags |= 0x40;
}
