#include "common.h"
#include "dungeon/monster/baloon.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern u8 D_800E2380[8];
extern u8 baloon_fall_frames[8];

typedef struct S_801737F8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737F8_0;   /* arg0 in advance_actor_animation_and_fall */

/* Advance the actor animation state, timers, and downward movement. */
void advance_actor_animation_and_fall(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 state;

    state = ((S_801737F8_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (sprite->flags & 0x8000) {
            ((S_801737F8_0 *)action)->unk_9B = 4;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        if (((S_801737F8_0 *)action)->unk_92.s !=
            (s16)(sample_terrain_surface_height(((u16) motion->x.w.i),
                                ((u16) motion->y.w.i),
                                (s16)(((u16)actor->ground_height) - 0x20)) -
                  ((u16)actor->ground_height))) {
            return;
        }
        ((S_801737F8_0 *)action)->unk_9B++;
        sprite->tpage_abr = 0x20;
        sprite->flags = sprite->flags | 0x000C;
        return;

    case 1:
        sprite->frameTable = D_800E2380;
        select_sprite_entry(sprite,
            D_800E2380[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801737F8_0 *)action)->unk_96.u = 0;
        ((S_801737F8_0 *)action)->unk_9B++;
        return;

    case 2:
        {
            s32 duration = 10;
            u16 timer = ((S_801737F8_0 *)action)->unk_96.u + 1;

            ((S_801737F8_0 *)action)->unk_96.u = timer;
            if ((s16)timer == duration || (sprite->flags & 0x8000)) {
                resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
                ((S_801737F8_0 *)action)->unk_96.u = duration;
                ((S_801737F8_0 *)action)->unk_9B++;
                sprite->flags |= 0x0800;
            }
            if (((S_801737F8_0 *)action)->unk_96.s == 9) {
                play_sound_if_enabled(0x809);
                return;
            }
            return;
        }

    case 3:
        if (((S_801737F8_0 *)action)->unk_96.s > 0) {
            u16 timer = ((S_801737F8_0 *)action)->unk_96.u - 1;

            ((S_801737F8_0 *)action)->unk_96.u = timer;
            if ((timer << 16) != 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            ((S_801737F8_0 *)action)->unk_98 |= 8;
            sprite->frameTable = baloon_fall_frames;
            select_sprite_entry(sprite,
                baloon_fall_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        }

        if (((S_801737F8_0 *)action)->unk_92.s >= -0x1F) {
            ((S_801737F8_0 *)action)->unk_92.u -= 4;
            return;
        }
        ((S_801737F8_0 *)action)->unk_9B++;
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        ((S_801737F8_0 *)action)->unk_8C = update_actor_turn_behavior;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        actor->flags1C |= 0x40000;
        ((S_801737F8_0 *)action)->unk_98 |= 8;
        sprite->flags = sprite->flags & 0xFFF3;
    }
}
