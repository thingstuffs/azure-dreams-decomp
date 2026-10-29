#include "common.h"
#include "dungeon/monster/kewne_uncached.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void play_sound_if_enabled(s32);

extern void create_parent_attached_effect(void *, void *, void *);

extern u8 kewne_uncached_action_resume_address[9];
extern u8 D_80175C68[8];
extern u8 D_80175C70[8];

typedef struct S_80173930_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_80173930_0;   /* arg0 in update_staged_movement_height_and_animation */

/* Updates the actor's staged movement, height, and directional animation. */
void update_staged_movement_height_and_animation(void *motion, ObjectPosition *velocity, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 state;

    state = ((S_80173930_0 *)motion)->unk_9B;
    switch (state) {

    case 0:
        if (!(sprite->flags & 0x8000)) {
            play_sound_if_enabled(0x80E);
        }
        ((S_80173930_0 *)motion)->unk_9B++;

    case 1:
        if (sprite->flags & 0x8000) {
            ((S_80173930_0 *)motion)->unk_96.u = 0x100;
            ((S_80173930_0 *)motion)->unk_9B = 5;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        sprite->frame_ticks -= 2;
        {
            u32 direction_offset = ((u16)actor->facing >> 8) & 0xE;
            velocity->velocity_x -=
                (s32)*(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset) << 16;
            velocity->velocity_y -=
                (s32)*(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset) << 16;
        }
        if (sprite->flags & 0x6000) {
            sprite->frameTable = D_80175C68;
            select_sprite_entry(
                sprite,
                D_80175C68[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80173930_0 *)motion)->unk_9B++;
        }

    case 2:
    {
        u16 height = ((S_80173930_0 *)motion)->unk_A0.at02.v + 0x10;

        ((S_80173930_0 *)motion)->unk_A0.at02.v = height;
        if ((s16)height >= 0x31) {
            ((S_80173930_0 *)motion)->unk_A0.at02.v = 0x30;
            velocity->velocity_y = 0;
            velocity->velocity_x = 0;
        }
    }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        velocity->velocity_z = 0;
        velocity->velocity_y = 0;
        velocity->velocity_x = 0;
        if (((S_80173930_0 *)motion)->unk_A0.at02u.v < 0x30) {
            return;
        }
        {
            s32 current_state = ((S_80173930_0 *)motion)->unk_9B;

            ((S_80173930_0 *)motion)->unk_96.u = 0;
            if (current_state == 0) {
                return;
            }
        }
        play_sound_if_enabled(0x808);
        ((S_80173930_0 *)motion)->unk_9B++;
        create_parent_attached_effect((u8 *)motion - 0x20, (u8 *)actor + 0x2A,
                      (u8 *)motion + 0x9B);
        return;

    case 3:
    {
        u8 *direction_x = (u8 *)((s8 *)dir_step_x);
        u8 *direction_y = (u8 *)((s8 *)dir_step_y);
        u16 frame;

        velocity->velocity_x +=
            (s32)*(s16 *)(direction_x +
                (((u16)actor->facing >> 8) & 0xE)) << 17;

        velocity->velocity_y +=
            (s32)*(s16 *)(direction_y +
                (((u16)actor->facing >> 8) & 0xE)) << 17;

        ((S_80173930_0 *)motion)->unk_A0.at00.v -= (s32)((S_80173930_0 *)motion)->unk_96.s << 17;
        frame = ((S_80173930_0 *)motion)->unk_96.u + 1;
        ((S_80173930_0 *)motion)->unk_96.u = frame;
        if ((s16)frame < 9) {
            return;
        }

        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        sprite->frameTable = D_80175C70;
        select_sprite_entry(
            sprite,
            D_80175C70[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        velocity->velocity_x =
            -*(s16 *)(direction_x +
                (((u16)actor->facing >> 8) & 0xE)) << 20;

        velocity->velocity_y =
            -*(s16 *)(direction_y +
                (((u16)actor->facing >> 8) & 0xE)) << 20;
        ((S_80173930_0 *)motion)->unk_A8 = velocity->velocity_x / 6;
        ((S_80173930_0 *)motion)->unk_AC = velocity->velocity_y / 6;
        ((S_80173930_0 *)motion)->unk_96.u = 0;
        ((S_80173930_0 *)motion)->unk_9B++;
        return;
    }

    case 4:
        velocity->velocity_x -= ((S_80173930_0 *)motion)->unk_A8;
        velocity->velocity_y -= ((S_80173930_0 *)motion)->unk_AC;
        ((S_80173930_0 *)motion)->unk_A0.at00.v =
            rsin(((S_80173930_0 *)motion)->unk_96.s * 146) * 160 + 0x100000;

    case 5:
    {
        u16 frame = ((S_80173930_0 *)motion)->unk_96.u + 1;

        ((S_80173930_0 *)motion)->unk_96.u = frame;
        if ((s16)frame < 7 && !(sprite->flags & 0x8000)) {
            return;
        }
    }
        velocity->velocity_z = 0;
        velocity->velocity_y = 0;
        velocity->velocity_x = 0;
        set_record_integer_tile_center(velocity, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        ((S_80173930_0 *)motion)->unk_8C = kewne_uncached_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        break;
    default:
        return;
    }
}
