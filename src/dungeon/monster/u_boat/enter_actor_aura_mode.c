#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80175BA8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
    u8 pad_B0[0x1];
    s8 unk_B1;
    s8 unk_B2;
    s8 unk_B3;
    s8 unk_B4;
    s8 unk_B5;
} S_80175BA8_0;   /* arg0 in enter_actor_aura_mode */

typedef struct S_80175BA8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80175BA8_1;   /* arg1 in enter_actor_aura_mode */

typedef struct S_80175BA8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80175BA8_2;   /* arg3 in enter_actor_aura_mode */

typedef struct S_80175BA8_5 {
    u8 pad_00[0x38];
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
    void * unk_44;
} S_80175BA8_5;

extern void *allocate_list_node();
extern void register_node();
extern void select_sprite_entry();
extern void play_sound_if_enabled();
extern s32 sample_terrain_surface_height();

extern u8 D_80045C34[];
extern u8 uboat_aura_start_frames[];
extern u8 uboat_aura_later_frames[];
extern u8 D_800E2488[];
extern u8 D_80170CEC[];
#include "dungeon/monster/u_boat.h"

/* Updates the actor's height offset, spawns an effect, and advances its animation phases. */
void enter_actor_aura_mode(void *actor_state, void *position, SpriteFrameState *sprite, void *actor_info) {
    s16 target_offset;
    u16 next_offset;
    u16 phase_ticks;
    u16 first_delay;
    u16 second_delay;
    s32 phase;
    SpriteFrameState *effect_sprite;
    ObjectNodeHeader *effect;
    void *effect_state;
    MovingPosition *effect_position;

    phase = ((S_80175BA8_0 *)actor_state)->unk_9B;
    switch (phase) {
    case 0:
        ((S_80175BA8_1 *)position)->unk_14 = 0;
        ((S_80175BA8_1 *)position)->unk_10 = 0;
        ((S_80175BA8_1 *)position)->unk_0C = 0;
        target_offset = sample_terrain_surface_height(((S_80175BA8_1 *)position)->unk_02, ((S_80175BA8_1 *)position)->unk_06,
                                (s16)(((S_80175BA8_2 *)actor_info)->unk_88 - 0x20))
        - ((S_80175BA8_2 *)actor_info)->unk_88;
        if (((S_80175BA8_0 *)actor_state)->unk_92.s < target_offset) {
            next_offset = ((S_80175BA8_0 *)actor_state)->unk_92.u + 0xC;
            ((S_80175BA8_0 *)actor_state)->unk_92.u = next_offset;
            if (target_offset < (s16)next_offset) {
                ((S_80175BA8_0 *)actor_state)->unk_92.s = target_offset;
            }
        } else {
            ((S_80175BA8_0 *)actor_state)->unk_92.s = target_offset;
        }
        if (sprite->flags & 0x8000) {
            ((S_80175BA8_0 *)actor_state)->unk_92.u = 0;
        }
        phase_ticks = ((S_80175BA8_0 *)actor_state)->unk_96 + 1;
        ((S_80175BA8_0 *)actor_state)->unk_96 = phase_ticks;
        if (((s16)phase_ticks == 1) || (sprite->flags & 0x8000)) {
            ((S_80175BA8_0 *)actor_state)->unk_B5 = 1;
            effect = allocate_list_node(0x12, (u8 *)actor_state - 0x20);
            if (effect != NULL) {
                ((S_80175BA8_0 *)actor_state)->unk_AC = effect;
                effect->unk_10 = D_80170CEC;
                register_node(effect, D_80045C34);
                effect_state = (u8 *)effect + 0x20;
                ((S_80175BA8_5 *)effect_state)->unk_38 = 5;
                ((S_80175BA8_5 *)effect_state)->unk_40 = actor_state;
                ((S_80175BA8_5 *)effect_state)->unk_44 = position;
                effect_sprite = effect->sprite;
                effect_sprite->tpage_abr = 0x40;
                effect_sprite->flags |= 0xC;
                effect_position = effect->position;
                effect_position->unk_02 = ((S_80175BA8_1 *)position)->unk_02;
                effect_position->unk_06 = ((S_80175BA8_1 *)position)->unk_06;
                effect_position->unk_0A = ((S_80175BA8_2 *)actor_info)->unk_88;
                effect_sprite = effect->sprite;
                effect_sprite->scale_y = 0xA00;
                effect_sprite->scale_x = 0xA00;
                effect_sprite->color.c.b = 0;
                effect_sprite->color.c.g = 0;
                effect_sprite->color.c.r = 0;
                effect_sprite->source = D_800E2488;
            }
        }
        if (((S_80175BA8_0 *)actor_state)->unk_92.s == 0) {
            (sprite->frameTable) = uboat_aura_start_frames;
            select_sprite_entry(sprite,
                          uboat_aura_start_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80175BA8_2 *)actor_info)->unk_2A + 0x100)
                              >> 9) & 7],
                          0);
            ((S_80175BA8_0 *)actor_state)->unk_96 = 2;
            ((S_80175BA8_0 *)actor_state)->unk_9B++;
            if (!(sprite->flags & 0x8000)) {
                play_sound_if_enabled(0x800);
            }
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }

    case 1:
        first_delay = ((S_80175BA8_0 *)actor_state)->unk_96 - 1;
        ((S_80175BA8_0 *)actor_state)->unk_96 = first_delay;
        if (((first_delay << 0x10) <= 0) || (sprite->flags & 0xE000)) {
            (sprite->frameTable) = uboat_aura_later_frames;
            select_sprite_entry(sprite,
                          uboat_aura_later_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80175BA8_2 *)actor_info)->unk_2A + 0x100)
                              >> 9) & 7],
                          0);
            ((S_80175BA8_0 *)actor_state)->unk_96 = 3;
            ((S_80175BA8_0 *)actor_state)->unk_9B++;
        }
        if (!(sprite->flags & 0x8000)) {
            return;
        }
    case 2:
        second_delay = ((S_80175BA8_0 *)actor_state)->unk_96 - 1;
        ((S_80175BA8_0 *)actor_state)->unk_96 = second_delay;
        if (((second_delay << 0x10) <= 0) || (sprite->flags & 0x8000)) {
            ((S_80175BA8_0 *)actor_state)->unk_96 = 0x1E;
            ((S_80175BA8_0 *)actor_state)->unk_A8 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B1 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B2 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B4 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_B3 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_9B++;
            ((S_80175BA8_0 *)actor_state)->unk_98 &= 0xFFF7;
            sprite->unk_06 = 0;
            ((S_80175BA8_0 *)actor_state)->unk_8C = uboat_behavior_entry;
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)actor_info + 0x46)) &= 0x7FFF;
        }
        return;
    default:
        return;
    }
}
