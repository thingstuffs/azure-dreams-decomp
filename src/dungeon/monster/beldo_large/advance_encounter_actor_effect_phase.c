/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "slus.h"
#include "dungeon/system.h"
#include "engine/texture.h"
extern u8 encounter_overlay_work[];

typedef struct S_8016FC4C_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016FC4C_0;

typedef struct S_8016FC4C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016FC4C_2;

typedef struct S_8016FC4C_3 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_8016FC4C_3;   /* arg0 in advance_encounter_actor_effect_phase */

typedef struct S_8016FC4C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FC4C_4;

typedef struct S_8016FC4C_6 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_8016FC4C_6;   /* entity in advance_encounter_actor_effect_phase */

typedef struct S_8016FC4C_7 {
    s16 unk_00;
    s16 unk_02;
} S_8016FC4C_7;   /* (u8 *)table_ptr in advance_encounter_actor_effect_phase */

typedef struct S_8016FC4C_8 {
    u8 pad_00[0x3228];
    s16 unk_3228;
    u8 pad_322A[0x2B26];
    void * unk_5D50;
} S_8016FC4C_8;   /* (u8 *)common_page in advance_encounter_actor_effect_phase */

s32 rand(void);
u16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
void create_random_velocity_child_effect();
void create_offset_half_scale_spark(void *, s32, s32, s32);
extern s16 beldo_large_direction_offsets[16];
extern void *beldo_actor_nodes[3];

/* Updates the effect phases, particle bursts, movement, and directional sprite. */
/* Shrinks Beldo while emitting particles, sustains spark bursts, then turns, moves, and hides the
 * encounter sprite. */
void advance_encounter_actor_effect_phase(void *effect, S_8016FC4C_6 *entity, SpriteFrameState *object) {
    u16 distance;
    s32 burst_y;
    s16 sustain_y;
    s32 direction;
    s16 burst_x;
    s16 sustain_x;
    s32 random_bits;
    s32 count;
    s32 phase_active;
    s32 rounded_step;
    u16 height;
    u16 burst_ticks;
    u16 width;
    u16 sustain_ticks;
    u16 turn_ticks;
    u16 move_ticks;
    s16 turned_angle;
    u16 angle;
    u8 phase;
    S_8016FC4C_4 *heading;
    void *linked_entity;
    S_8016FC4C_2 *linked_object;
    void *link_slot;
    void *shrink_source;
    void *burst_source;
    u32 common_page;
    u32 table_page;
    u16 table_angle;
    u32 table_ptr;
    u8 turn_phase;

    count = 1;
    heading = beldo_actor_nodes[0] + 0x20;
    link_slot = ((u8 *)dungeon_actor_ring_anchor) + 4;
    do {
        linked_entity = ((S_8016FC4C_0 *)link_slot)->unk_AC;
        if (linked_entity != NULL) {
            linked_object = ((SpriteLinkPrefixView *)linked_entity)[-1].sprite;
            linked_object->unk_14 = (u16)(linked_object->unk_14 & 0xFFBF);
        }
        count -= 1;
        link_slot -= 4;
    } while (count >= 0);
    phase = ((S_8016FC4C_3 *)effect)->unk_9A;
    switch (phase) {
    case 0:
    {
        s32 shrink_step;
        s32 scaled_step;
        heading->unk_2A = get_rounded_facing_and_rounding_flag(
            object->tile_x, object->tile_y,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
        ((S_8016FC4C_3 *)effect)->unk_96 = (u16)(((S_8016FC4C_3 *)effect)->unk_96 + 1);
        height = object->scale_y;
        height = (u16)(height - 0x14);
        object->scale_y = height;
        width = object->scale_x;
        scaled_step = object->scale_y;
        width = (u16)(width - 0x14);
        scaled_step <<= 6;
        scaled_step = 0 - scaled_step;
        object->scale_x = width;
        if (scaled_step < 0)
            scaled_step += 0xFFF;
        rounded_step = scaled_step;
        count = 0;
        shrink_step = rounded_step >> 0xC;
        shrink_source = effect - 0x20;
        do {
            create_random_velocity_child_effect(shrink_source, 0xFFFFFF, 0xE, 0, 0, shrink_step);
            count += 1;
            shrink_source = effect - 0x20;
        } while (count < 6);
        if ((s16)((S_8016FC4C_3 *)effect)->unk_96 == 1)
            play_sound_if_enabled(0xB1);
        phase_active = ((s16)((S_8016FC4C_3 *)effect)->unk_96 < 120);
        if (phase_active == 0) {
            ((S_8016FC4C_3 *)effect)->unk_9A = (u8)(((S_8016FC4C_3 *)effect)->unk_9A + 1);
            ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        }
        break;
    }
    case 1:
    {
        s32 burst_step;
        s32 scaled_step;
        heading->unk_2A = get_rounded_facing_and_rounding_flag(
            object->tile_x, object->tile_y,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
        scaled_step = 0 - (object->scale_y << 6);
        if (scaled_step < 0)
            scaled_step += 0xFFF;
        count = 0;
        burst_step = scaled_step >> 0xC;
        burst_source = effect - 0x20;
        do {
            create_random_velocity_child_effect(burst_source, 0xFFFFFF, 0xE, 0, 0, burst_step);
            count += 1;
            burst_source = effect - 0x20;
        } while (count < 6);
        burst_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = burst_ticks;
        if (!(burst_ticks & 1)) {
            burst_x = (rand() & 0x1F) - 0xF;
            burst_x = (s16)(((s32)burst_x << 16) >> 16);
            burst_y = (s16)((rand() & 0x1F) - 0xF);
            create_offset_half_scale_spark(entity, burst_x, burst_y, (s16)((0 - (rand() & 0x1F)) - 0xA));
        }
        if (!(((S_8016FC4C_3 *)effect)->unk_96 & 7))
            play_sound_if_enabled(0x817);
        phase_active = ((s16)((S_8016FC4C_3 *)effect)->unk_96 < 20);
        if (phase_active == 0) {
            ((S_8016FC4C_3 *)effect)->unk_9A = (u8)(((S_8016FC4C_3 *)effect)->unk_9A + 1);
            ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        }
        break;
    }
    case 2:
        sustain_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = sustain_ticks;
        if (!(sustain_ticks & 7))
            play_sound_if_enabled(0x817);
        if (!(((S_8016FC4C_3 *)effect)->unk_96 & 1)) {
            random_bits = rand();
            sustain_x = (random_bits & 0x1F) - 0xF;
            sustain_x = (s16)(((s32)sustain_x << 16) >> 16);
            sustain_y = (rand() & 0x1F) - 0xF;
            sustain_y = (s16)(((s32)sustain_y << 16) >> 16);
            create_offset_half_scale_spark(entity, sustain_x, sustain_y, (s16)((0 - (rand() & 0x1F)) - 0xA));
        }
        break;
    case 4:
        turn_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = turn_ticks;
        if (((s16)turn_ticks == 3) || ((s16)turn_ticks == 6) || ((s16)turn_ticks == 9) || ((s16)turn_ticks == 0xC)) {
            angle = heading->unk_2A;
            turned_angle = angle - 0x200;
            angle = turned_angle;
            if (turned_angle < 0)
                angle += 0x1000;
            heading->unk_2A = angle;
        }
        if ((s16)((S_8016FC4C_3 *)effect)->unk_96 < 0xE)
            break;
        turn_phase = ((S_8016FC4C_3 *)effect)->unk_9A;
        ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        table_page = (u32)beldo_large_direction_offsets;
        turn_phase = (u8)(turn_phase + 1);
        ((S_8016FC4C_3 *)effect)->unk_9A = turn_phase;
        table_angle = heading->unk_2A;
        table_ptr = ((table_angle >> 7) & 0x1C);
        table_ptr += table_page;
        entity->unk_0C = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_00 * 0x30000);
        table_ptr = (((u16)heading->unk_2A >> 7) & 0x1C);
        table_ptr += table_page;
        entity->unk_10 = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_02 * 0x30000);
        break;
    case 5:
        entity->unk_00.at00.v = (s32)(entity->unk_00.at00.v + entity->unk_0C);
        entity->unk_04.at00.v = (s32)(entity->unk_04.at00.v + entity->unk_10);
        move_ticks = ((S_8016FC4C_3 *)effect)->unk_96 + 1;
        ((S_8016FC4C_3 *)effect)->unk_96 = move_ticks;
        if ((s16)move_ticks < 6)
            break;
        ((S_8016FC4C_3 *)effect)->unk_96 = 0U;
        ((S_8016FC4C_3 *)effect)->unk_9A = (u8)(((S_8016FC4C_3 *)effect)->unk_9A + 1);
        break;
    case 7:
        object->flags = (u16)(object->flags | 0x80);
        entity->unk_04.at02.v = 1;
        entity->unk_00.at02.v = 1;
        break;
    default:
        break;
    }
    if (((S_8016FC4C_8 *)encounter_overlay_work)->unk_5D50 != 0) {
        s16 sprite_direction;
        s32 old_direction;
        common_page = (u32)(s32)g_game_work.view.camera_rotation.parts.viewAngle;
        direction = (((s32)common_page + (s16)heading->unk_2A + 0x100) >> 9) & 7;
        old_direction = ((S_8016FC4C_3 *)effect)->unk_94;
        sprite_direction = direction;
        if (old_direction != sprite_direction) {
            select_indirect_table_entry(object, *(*(u8 **)&object->frameTable + sprite_direction), object->unk_04);
            ((S_8016FC4C_3 *)effect)->unk_94 = direction;
        }
        advance_sprite_animation_and_textures(object);
    }
}
