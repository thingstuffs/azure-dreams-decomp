#include "common.h"
#include "dungeon/monster/nyuel.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"

void *resolve_attack_damage_and_effects();
void set_record_integer_tile_center();
s32 advance_status_timers();
s32 play_sound_if_enabled();
void spend_actor_mp();
void update_entity_actions_facing_and_animation(void *entity, s32 context, void *sprite, void *state);
extern u8 nyuel_frame_set_9;
extern u8 nyuel_frame_set_10;
extern u8 nyuel_frame_set_4;

typedef struct S_80172524_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
} S_80172524_0;   /* arg0 in advance_action_phases_and_animation */

/* Advance the action phases, updating movement and directional animation. */
void advance_action_phases_and_animation(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 move_ticks;
    u16 settle_ticks;
    u8 phase;

    phase = ((S_80172524_0 *)action)->unk_9B.n;
    switch (phase) {
    case 0:
        ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 | 8);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (sprite->flags & 0x8000) {
            ((S_80172524_0 *)action)->unk_9B.n = 5U;
            ((S_80172524_0 *)action)->unk_96.u = 0U;
            sprite->flags = (u16) (sprite->flags
                | 0x6000);
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        motion->velocity_x = (s32) (*(s16 *)(((u8 *)dir_step_x) + (((u16) actor->facing >> 8) & 0xE)) << 0x14);
        motion->velocity_y = (s32) (*(s16 *)(((u8 *)dir_step_y) + (((u16) actor->facing >> 8) & 0xE)) << 0x14);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 1:
        motion->velocity_x = (s32) ((s32) motion->velocity_x >> 1);
        motion->velocity_y = (s32) ((s32) motion->velocity_y >> 1);
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = (u8 *)&nyuel_frame_set_9;
        select_sprite_entry(sprite, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7) + (u32)&nyuel_frame_set_9), 0);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 2:
        motion->velocity_x = (s32) ((s32) motion->velocity_x >> 1);
        motion->velocity_y = (s32) ((s32) motion->velocity_y >> 1);
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        play_sound_if_enabled(0x808);
        sprite->frameTable = (u8 *)&nyuel_frame_set_10;
        select_sprite_entry(sprite, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7) + (u32)&nyuel_frame_set_10), 0);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 3:
        if (sprite->unk_04 == 2) {
            if (sprite->flags & 0x1000) {
                resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
                {
                    u16 move_duration = 6;
                    ((S_80172524_0 *)action)->unk_96.u = move_duration;
                }
                ((S_80172524_0 *)action)->unk_9B.n++;
                return;
            }
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = &nyuel_frame_set_4;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
            + &nyuel_frame_set_4), 0);
        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        ((S_80172524_0 *)action)->unk_9B.n = 5U;
        ((S_80172524_0 *)action)->unk_96.u = 0;
        return;
    case 4:
        move_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
        ((S_80172524_0 *)action)->unk_96.u = move_ticks;
        if ((s16) move_ticks > 0) {
            {
                s32 target_coord = sprite->tile_x << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->velocity_x = ((target_coord - current_coord) << 0x10) / (s16) move_ticks;
            }
            {
                s32 target_coord = sprite->tile_y << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->velocity_y = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
            }
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        sprite->frameTable = (u8 *)&nyuel_frame_set_4;
        select_sprite_entry(sprite, *(u8 *)((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7) + (u32)&nyuel_frame_set_4), 0);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 5:
        settle_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
        ((S_80172524_0 *)action)->unk_96.u = settle_ticks;
        if ((s16) settle_ticks > 0) {
            {
                s32 target_coord = sprite->tile_x << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->velocity_x = ((target_coord - current_coord) << 0x10) / (s16) settle_ticks;
            }
            {
                s32 target_coord = sprite->tile_y << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->velocity_y = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
            }
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 & 0xFFF7);
        spend_actor_mp(actor, 0x100);
        ((S_80172524_0 *)action)->unk_8C = &update_entity_actions_facing_and_animation;
        g_dungeon_status.active_actor = 0;
        actor->action_flags = (u16) ((actor->action_flags) & 0x7FFF);
        advance_status_timers(actor);
        return;
    default:
        return;
    }
}
