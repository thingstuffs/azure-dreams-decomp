#include "dungeon/monster/baloon_frames.h"
#include "shared/actor_status_flags.h"
#include "dungeon/monster/baloon.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800D6DC0_arg2.h"
#include "dungeon/level.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "shared/entity.h"
#include "dungeon/actor/state.h"
#include "sdk/libc.h"
#include "dungeon/effect/sprite.h"





extern u8 D_800E23B8[];
extern u8 D_800E23C0[];

void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);

extern void create_anchored_directional_object(void *, void *, void *, ActorRecord *, s32);
extern void create_origin_motion_effect(ActorRecord *, ObjectPosition *, SpriteFrameState *, s32, s32, s32);

/* Advances the entity animation sequence and relocates it to a distant tile. */
/* Animates Baloon's rising effect, tries to relocate at least 33 tile steps from the player, then spends
 * MP and restores idle. */
void relocate_entity_after_animation(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, void *object)
{
    s32 particle_index;
    s32 tries_left;
    s32 burst_x;
    s32 scatter_x;
    s16 random_y;
    s16 ground_z;
    s16 tile_result;
    s32 height_offset;
    s32 dx;
    s32 dy;
    u8 old_x;
    u8 old_y;
    u8 *animations;

    switch (body->action_phase) {
    case 0:
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        if (sprite->flags & 0x8000) {
            body->action_phase = 7;
            sprite->flags |= 0x6000;
            return;
        }
        if (body->unk_A0.value <= 0x6FFFF) {
            return;
        }
        body->action_state_flags |= 8;
        ((ActorRecord *)object)->flags1C &= ~0x40000;
        body->unk_A0.value = 0;
        body->unk_90.parts.high.u -= 8;
        body->action_phase++;
        body->unk_B4.halves.high.u =
            position->z.unsigned_parts.integer + body->unk_90.parts.high.u;
        return;

    case 1:
        (sprite->frameTable) = D_800E23B8;
        select_sprite_entry(sprite,
            D_800E23B8[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)object)->facing + 0x100) >> 9) & 7],
            0);
        body->action_timer = 0;
        body->action_phase++;
        return;

    case 2:
        if ((s16)(++body->action_timer) < 9) {
            return;
        }
        (sprite->frameTable) = D_800E23C0;
        select_sprite_entry(sprite,
            D_800E23C0[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)object)->facing + 0x100) >> 9) & 7],
            0);
        body->action_timer = 0;
        body->action_phase++;
        return;

    case 3:
        if ((s16)(body->action_timer++) < 3) {
            return;
        }
        body->action_timer = 0;
        body->action_phase++;
        return;

    case 4:
        if ((s16)(body->action_timer++) < 0xB) {
            return;
        }
        particle_index = 0;
        body->action_timer = 0;
        body->action_phase++;
        position->velocity_z = 0;
        body->unk_AC.value = 0;
        do {
            burst_x = (s16)(random_below_limit(0x2C) - 0x16);
            random_y = random_below_limit(0x2C) - 0x16;
            create_origin_motion_effect(body, position, sprite, burst_x, random_y, 0x1E);
            particle_index++;
        } while (particle_index < 6);
        create_radial_effect_segments(body, position, sprite, object);
        return;

    case 5:
        switch ((s16)body->action_timer) {
        case 0:
            position->velocity_z = -0x140000;
            body->unk_AC.value = 0x30000;
            break;
        case 6:
            position->velocity_z = -0x180000;
            body->unk_AC.value = -0x10000;
            break;
        case 12:
            body->unk_AC.value = -0x20000;
            break;
        }
        position->velocity_z += body->unk_AC.value;

        if ((s16)body->action_timer < 2) {
            particle_index = 0;
            do {
                scatter_x = (s16)((rand() & 0x1F) - 0x10);
                random_y = (rand() & 0x1F) - 0x10;
                create_origin_motion_effect(body, position, sprite, scatter_x, random_y, 0x1E);
                particle_index++;
            } while (particle_index < 4);
        }
        if ((s16)body->action_timer == 1) {
            create_anchored_directional_object(body, position, sprite, object, 1);
            play_sound_if_enabled(0x80A);
        }
        if ((s16)body->action_timer == 2) {
            create_directional_template_effect(body, (BaloonTemplateAnchor *)position, sprite, object);
        }
        if ((s16)body->action_timer == 6) {
            create_anchored_directional_object(body, position, sprite, object, 0x1A);
            play_sound_if_enabled(0x705);
        }
        if ((s16)(body->action_timer++) < 0x2E) {
            return;
        }
        body->action_timer = 0;
        body->action_phase++;
        return;

    case 6:
        position->z.unsigned_parts.integer = body->unk_B4.halves.high.u;

        body->action_timer = 0;
        body->action_phase++;
        return;

    case 7:
        update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y,
            (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        tries_left = 0x20;
        old_x = sprite->tile_x;
        old_y = sprite->tile_y;
        for (;;) {
            do {
                tile_result = select_dungeon_spawn_tile((u8 *)sprite + 0x24, (u8 *)sprite + 0x25);
            } while (tile_result < 0);

            dx = abs(reference_tile_object.tile_position.parts.tile_x - sprite->tile_x);
            dy = abs(reference_tile_object.tile_position.parts.tile_y - sprite->tile_y);
            if (dx + dy >= 0x21) {
                break;
            }
            if (--tries_left < 0) {
                sprite->tile_x = old_x;
                sprite->tile_y = old_y;
                break;
            }
        }

        position->x.w.i = (sprite->tile_x << 6) + 0x20;
        position->y.w.i = (sprite->tile_y << 6) + 0x20;
        ground_z = sample_terrain_surface_height(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            -0x200);
        ground_z -= 0x11;
        height_offset = -0x20;
        position->z.w.i = ground_z;
        body->unk_90.parts.high.s = height_offset;
        body->unk_A0.value = 0;
        ((ActorRecord *)object)->ground_height = -0x200;
        ground_z = sample_terrain_surface_height(
            (sprite->tile_x << 6) | 0x20,
            (sprite->tile_y << 6) | 0x20,
            -0x200);
        ((ActorRecord *)object)->ground_height = ground_z;

        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
            (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        refresh_actor_proximity_state(object);
        spend_actor_mp(object, 0x1000);
        body->unk_8C.address = update_actor_turn_behavior;
        g_dungeon_status.active_actor = 0;
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        body->unk_90.parts.high.s = height_offset;
        ((ActorRecord *)object)->flags1C |= 0x40000;
        body->action_state_flags |= 8;

        animations = baloon_default_frames;
        if (*(u8 **)&sprite->frameTable != animations) {
            (sprite->frameTable) = animations;
            select_sprite_entry(sprite,
                animations[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)object)->facing + 0x100) >> 9) & 7],
                0);
            sprite->frame_ticks = 1;
            body->unk_A0.parts.high = 0;
            body->unk_9E = 0;
        }
        ((ActorRecord *)object)->action_flags &= 0x7FFF;

    default:
        return;
    }
}

#undef FIELD
