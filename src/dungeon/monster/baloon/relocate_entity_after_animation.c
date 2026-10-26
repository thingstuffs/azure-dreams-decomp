#include "shared/actor_status_flags.h"
#include "dungeon/monster/baloon.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800D6DC0_arg2.h"
#include "dungeon/level.h"

typedef struct S_80175594_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    union { u16 s; s16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x8];
    s32 unk_AC;
    u8 pad_B0[0x6];
    u16 unk_B6;
} S_80175594_0;   /* arg0 in relocate_entity_after_animation */

typedef struct S_80175594_1 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175594_1;   /* arg1 in relocate_entity_after_animation */

typedef struct S_80175594_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x40];
    s16 unk_88;
} S_80175594_3;   /* object in relocate_entity_after_animation */

extern u8 baloon_default_frames[];
extern u8 D_800E23B8[];
extern u8 D_800E23C0[];

extern void select_sprite_entry(void *, u8, s32);
extern s32 rand(void);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern s16 select_dungeon_spawn_tile(u8 *, u8 *);
extern void play_sound_if_enabled(s32);
extern void refresh_actor_proximity_state(u8 *context);
extern void spend_actor_mp(void *, s32);
extern void create_radial_effect_segments(void *, void *, void *, void *);
extern void create_anchored_directional_object(void *, void *, void *, void *, s32);
extern void create_origin_motion_effect(void *, void *, void *, s32, s32, s32);
extern s32 random_below_limit(s32);
extern int abs(int);

/* Advances the entity animation sequence and relocates it to a distant tile. */
/* Animates Baloon's rising effect, tries to relocate at least 33 tile steps from the player, then spends
 * MP and restores idle. */
void relocate_entity_after_animation(void *motion, void *position, SpriteFrameState *entity, void *object)
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

    switch (((S_80175594_0 *)motion)->unk_9B) {
    case 0:
        ((S_80175594_1 *)position)->unk_14 = 0;
        ((S_80175594_1 *)position)->unk_10 = 0;
        ((S_80175594_1 *)position)->unk_0C = 0;
        if (entity->flags & 0x8000) {
            ((S_80175594_0 *)motion)->unk_9B = 7;
            entity->flags |= 0x6000;
            return;
        }
        if (((S_80175594_0 *)motion)->unk_A0.at00.v <= 0x6FFFF) {
            return;
        }
        ((S_80175594_0 *)motion)->unk_98 |= 8;
        ((S_80175594_3 *)object)->unk_1C &= ~0x40000;
        ((S_80175594_0 *)motion)->unk_A0.at00.v = 0;
        ((S_80175594_0 *)motion)->unk_92.s -= 8;
        ((S_80175594_0 *)motion)->unk_9B++;
        ((S_80175594_0 *)motion)->unk_B6 =
            ((S_80175594_1 *)position)->unk_0A.s + ((S_80175594_0 *)motion)->unk_92.s;
        return;

    case 1:
        (entity->frameTable) = D_800E23B8;
        select_sprite_entry(entity,
            D_800E23B8[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80175594_0 *)motion)->unk_96 = 0;
        ((S_80175594_0 *)motion)->unk_9B++;
        return;

    case 2:
        if (++((S_80175594_0 *)motion)->unk_96 < 9) {
            return;
        }
        (entity->frameTable) = D_800E23C0;
        select_sprite_entry(entity,
            D_800E23C0[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80175594_0 *)motion)->unk_96 = 0;
        ((S_80175594_0 *)motion)->unk_9B++;
        return;

    case 3:
        if (((S_80175594_0 *)motion)->unk_96++ < 3) {
            return;
        }
        ((S_80175594_0 *)motion)->unk_96 = 0;
        ((S_80175594_0 *)motion)->unk_9B++;
        return;

    case 4:
        if (((S_80175594_0 *)motion)->unk_96++ < 0xB) {
            return;
        }
        particle_index = 0;
        ((S_80175594_0 *)motion)->unk_96 = 0;
        ((S_80175594_0 *)motion)->unk_9B++;
        ((S_80175594_1 *)position)->unk_14 = 0;
        ((S_80175594_0 *)motion)->unk_AC = 0;
        do {
            burst_x = (s16)(random_below_limit(0x2C) - 0x16);
            random_y = random_below_limit(0x2C) - 0x16;
            create_origin_motion_effect(motion, position, entity, burst_x, random_y, 0x1E);
            particle_index++;
        } while (particle_index < 6);
        create_radial_effect_segments(motion, position, entity, object);
        return;

    case 5:
        switch (((S_80175594_0 *)motion)->unk_96) {
        case 0:
            ((S_80175594_1 *)position)->unk_14 = -0x140000;
            ((S_80175594_0 *)motion)->unk_AC = 0x30000;
            break;
        case 6:
            ((S_80175594_1 *)position)->unk_14 = -0x180000;
            ((S_80175594_0 *)motion)->unk_AC = -0x10000;
            break;
        case 12:
            ((S_80175594_0 *)motion)->unk_AC = -0x20000;
            break;
        }
        ((S_80175594_1 *)position)->unk_14 += ((S_80175594_0 *)motion)->unk_AC;

        if (((S_80175594_0 *)motion)->unk_96 < 2) {
            particle_index = 0;
            do {
                scatter_x = (s16)((rand() & 0x1F) - 0x10);
                random_y = (rand() & 0x1F) - 0x10;
                create_origin_motion_effect(motion, position, entity, scatter_x, random_y, 0x1E);
                particle_index++;
            } while (particle_index < 4);
        }
        if (((S_80175594_0 *)motion)->unk_96 == 1) {
            create_anchored_directional_object(motion, position, entity, object, 1);
            play_sound_if_enabled(0x80A);
        }
        if (((S_80175594_0 *)motion)->unk_96 == 2) {
            create_directional_template_effect(motion, position, entity, object);
        }
        if (((S_80175594_0 *)motion)->unk_96 == 6) {
            create_anchored_directional_object(motion, position, entity, object, 0x1A);
            play_sound_if_enabled(0x705);
        }
        if (((S_80175594_0 *)motion)->unk_96++ < 0x2E) {
            return;
        }
        ((S_80175594_0 *)motion)->unk_96 = 0;
        ((S_80175594_0 *)motion)->unk_9B++;
        return;

    case 6:
        ((S_80175594_1 *)position)->unk_0A.s = ((S_80175594_0 *)motion)->unk_B6;

        ((S_80175594_0 *)motion)->unk_96 = 0;
        ((S_80175594_0 *)motion)->unk_9B++;
        return;

    case 7:
        update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y,
            (((S_80175594_3 *)object)->unk_1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        tries_left = 0x20;
        old_x = entity->tile_x;
        old_y = entity->tile_y;
        for (;;) {
            do {
                tile_result = select_dungeon_spawn_tile((u8 *)entity + 0x24, (u8 *)entity + 0x25);
            } while (tile_result < 0);

            dx = abs(reference_tile_object.tile_position.parts.tile_x - entity->tile_x);
            dy = abs(reference_tile_object.tile_position.parts.tile_y - entity->tile_y);
            if (dx + dy >= 0x21) {
                break;
            }
            if (--tries_left < 0) {
                entity->tile_x = old_x;
                entity->tile_y = old_y;
                break;
            }
        }

        ((S_80175594_1 *)position)->unk_02.s = (entity->tile_x << 6) + 0x20;
        ((S_80175594_1 *)position)->unk_06.s = (entity->tile_y << 6) + 0x20;
        ground_z = sample_terrain_surface_height(((S_80175594_1 *)position)->unk_02.u, ((S_80175594_1 *)position)->unk_06.u,
            -0x200);
        ground_z -= 0x11;
        height_offset = -0x20;
        ((S_80175594_1 *)position)->unk_0A.u = ground_z;
        ((S_80175594_0 *)motion)->unk_92.u = height_offset;
        ((S_80175594_0 *)motion)->unk_A0.at00.v = 0;
        ((S_80175594_3 *)object)->unk_88 = -0x200;
        ground_z = sample_terrain_surface_height(
            (entity->tile_x << 6) | 0x20,
            (entity->tile_y << 6) | 0x20,
            -0x200);
        ((S_80175594_3 *)object)->unk_88 = ground_z;

        cycle_map_cell_flags(entity->tile_x, entity->tile_y,
            (((S_80175594_3 *)object)->unk_1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        refresh_actor_proximity_state(object);
        spend_actor_mp(object, 0x1000);
        ((S_80175594_0 *)motion)->unk_8C = update_actor_turn_behavior;
        g_dungeon_status.active_actor = 0;
        ((S_80175594_1 *)position)->unk_14 = 0;
        ((S_80175594_1 *)position)->unk_10 = 0;
        ((S_80175594_1 *)position)->unk_0C = 0;
        ((S_80175594_0 *)motion)->unk_92.u = height_offset;
        ((S_80175594_3 *)object)->unk_1C |= 0x40000;
        (*(u16 *)((u8 *)motion + 0x98)) |= 8;

        animations = baloon_default_frames;
        if (*(u8 **)&entity->frameTable != animations) {
            (entity->frameTable) = animations;
            select_sprite_entry(entity,
                animations[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80175594_3 *)object)->unk_2A + 0x100) >> 9) & 7],
                0);
            entity->frame_ticks = 1;
            ((S_80175594_0 *)motion)->unk_A0.at02.v = 0;
            ((S_80175594_0 *)motion)->unk_9E = 0;
        }
        ((S_80175594_3 *)object)->unk_46 &= 0x7FFF;

    default:
        return;
    }
}

#undef FIELD
