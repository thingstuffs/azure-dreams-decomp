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
#include "dungeon/item.h"
extern u8 encounter_overlay_work[];

typedef struct S_8016FC4C_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8016FC4C_0;

typedef struct S_8016FC4C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016FC4C_2;

typedef struct S_8016FC4C_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FC4C_4;

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
void create_random_velocity_child_effect(); /* Unprototyped: canonical s16 parameters change this caller's argument setup; no shared prototype keeps it */
void create_offset_half_scale_spark(void *, s32, s32, s32);
extern s16 beldo_large_direction_offsets[16];
extern void *beldo_actor_nodes[3];

/* Updates the effect phases, particle bursts, movement, and directional sprite. */
/* Shrinks Beldo while emitting particles, sustains spark bursts, then turns, moves, and hides the
 * encounter sprite. */
void advance_encounter_actor_effect_phase(ActorRecord *effect, ObjectPosition *position, SpriteFrameState *sprite) {
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
    SpriteLinkPrefixView *linked_entity;
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
            linked_object = linked_entity[-1].sprite;
            linked_object->unk_14 = (u16)(linked_object->unk_14 & 0xFFBF);
        }
        count -= 1;
        link_slot -= 4;
    } while (count >= 0);
    phase = effect->action_id.u;
    switch (phase) {
    case 0:
    {
        s32 shrink_step;
        s32 scaled_step;
        heading->unk_2A = get_rounded_facing_and_rounding_flag(
            sprite->tile_x, sprite->tile_y,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
        effect->action_timer.u = (u16)(effect->action_timer.u + 1);
        height = sprite->scale_y;
        height = (u16)(height - 0x14);
        sprite->scale_y = height;
        width = sprite->scale_x;
        scaled_step = sprite->scale_y;
        width = (u16)(width - 0x14);
        scaled_step <<= 6;
        scaled_step = 0 - scaled_step;
        sprite->scale_x = width;
        if (scaled_step < 0)
            scaled_step += 0xFFF;
        rounded_step = scaled_step;
        count = 0;
        shrink_step = rounded_step >> 0xC;
        shrink_source = ((void *)effect) - 0x20;
        do {
            create_random_velocity_child_effect(shrink_source, 0xFFFFFF, 0xE, 0, 0, shrink_step);
            count += 1;
            shrink_source = ((void *)effect) - 0x20;
        } while (count < 6);
        if ((s16)effect->action_timer.u == 1)
            play_sound_if_enabled(0xB1);
        phase_active = ((s16)effect->action_timer.u < 120);
        if (phase_active == 0) {
            effect->action_id.u = (u8)(effect->action_id.u + 1);
            effect->action_timer.u = 0U;
        }
        break;
    }
    case 1:
    {
        s32 burst_step;
        s32 scaled_step;
        heading->unk_2A = get_rounded_facing_and_rounding_flag(
            sprite->tile_x, sprite->tile_y,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
        scaled_step = 0 - (sprite->scale_y << 6);
        if (scaled_step < 0)
            scaled_step += 0xFFF;
        count = 0;
        burst_step = scaled_step >> 0xC;
        burst_source = ((void *)effect) - 0x20;
        do {
            create_random_velocity_child_effect(burst_source, 0xFFFFFF, 0xE, 0, 0, burst_step);
            count += 1;
            burst_source = ((void *)effect) - 0x20;
        } while (count < 6);
        burst_ticks = effect->action_timer.u + 1;
        effect->action_timer.u = burst_ticks;
        if (!(burst_ticks & 1)) {
            burst_x = (rand() & 0x1F) - 0xF;
            burst_x = (s16)(((s32)burst_x << 16) >> 16);
            burst_y = (s16)((rand() & 0x1F) - 0xF);
            create_offset_half_scale_spark(position, burst_x, burst_y, (s16)((0 - (rand() & 0x1F)) - 0xA));
        }
        if (!(effect->action_timer.u & 7))
            play_sound_if_enabled(0x817);
        phase_active = ((s16)effect->action_timer.u < 20);
        if (phase_active == 0) {
            effect->action_id.u = (u8)(effect->action_id.u + 1);
            effect->action_timer.u = 0U;
        }
        break;
    }
    case 2:
        sustain_ticks = effect->action_timer.u + 1;
        effect->action_timer.u = sustain_ticks;
        if (!(sustain_ticks & 7))
            play_sound_if_enabled(0x817);
        if (!(effect->action_timer.u & 1)) {
            random_bits = rand();
            sustain_x = (random_bits & 0x1F) - 0xF;
            sustain_x = (s16)(((s32)sustain_x << 16) >> 16);
            sustain_y = (rand() & 0x1F) - 0xF;
            sustain_y = (s16)(((s32)sustain_y << 16) >> 16);
            create_offset_half_scale_spark(position, sustain_x, sustain_y, (s16)((0 - (rand() & 0x1F)) - 0xA));
        }
        break;
    case 4:
        turn_ticks = effect->action_timer.u + 1;
        effect->action_timer.u = turn_ticks;
        if (((s16)turn_ticks == 3) || ((s16)turn_ticks == 6) || ((s16)turn_ticks == 9) || ((s16)turn_ticks == 0xC)) {
            angle = heading->unk_2A;
            turned_angle = angle - 0x200;
            angle = turned_angle;
            if (turned_angle < 0)
                angle += 0x1000;
            heading->unk_2A = angle;
        }
        if ((s16)effect->action_timer.u < 0xE)
            break;
        turn_phase = effect->action_id.u;
        effect->action_timer.u = 0U;
        table_page = (u32)beldo_large_direction_offsets;
        turn_phase = (u8)(turn_phase + 1);
        effect->action_id.u = turn_phase;
        table_angle = heading->unk_2A;
        table_ptr = ((table_angle >> 7) & 0x1C);
        table_ptr += table_page;
        position->velocity_x = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_00 * 0x30000);
        table_ptr = (((u16)heading->unk_2A >> 7) & 0x1C);
        table_ptr += table_page;
        position->velocity_y = (s32)(((S_8016FC4C_7 *)((u8 *)table_ptr))->unk_02 * 0x30000);
        break;
    case 5:
        position->x.v = (s32)(position->x.v + position->velocity_x);
        position->y.v = (s32)(position->y.v + position->velocity_y);
        move_ticks = effect->action_timer.u + 1;
        effect->action_timer.u = move_ticks;
        if ((s16)move_ticks < 6)
            break;
        effect->action_timer.u = 0U;
        effect->action_id.u = (u8)(effect->action_id.u + 1);
        break;
    case 7:
        sprite->flags = (u16)(sprite->flags | 0x80);
        position->y.w.i = 1;
        position->x.w.i = 1;
        break;
    default:
        break;
    }
    if (((S_8016FC4C_8 *)encounter_overlay_work)->unk_5D50 != 0) {
        s16 sprite_direction;
        s32 old_direction;
        common_page = (u32)(s32)g_game_work.view.camera_rotation.parts.viewAngle;
        direction = (((s32)common_page + (s16)heading->unk_2A + 0x100) >> 9) & 7;
        old_direction = effect->unk_94;
        sprite_direction = direction;
        if (old_direction != sprite_direction) {
            select_indirect_table_entry(sprite, *(*(u8 **)&sprite->frameTable + sprite_direction), sprite->unk_04);
            effect->unk_94 = direction;
        }
        advance_sprite_animation_and_textures(sprite);
    }
}
