#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"


extern s32 rsin(s32);

extern void create_parent_position_effect(EntityRec *parent, s32 effect_param, u8 *effect_data);

extern u8 kewne_action_resume_address[9];
extern u8 D_80175E78[8];
extern u8 D_80175E80[8];

typedef struct S_80172DDC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
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
} S_80172DDC_0;   /* arg0 in update_staged_movement_and_idle */

/* Updates the actor's staged movement, animation, and return to idle. */
void update_staged_movement_and_idle(ActorRecord *body, ObjectPosition *movement, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 state;

    state = body->action_phase.u;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x8000)) {
            play_sound_if_enabled(0x80E);
        }
        body->action_phase.u++;

    case 1:
        if (sprite->flags & 0x8000) {
            body->action_timer.u = 0x100;
            body->action_phase.u = 5;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        sprite->frame_ticks -= 2;
        {
            u32 direction_offset = ((u16)actor->facing >> 8) & 0xE;
            movement->velocity_x -=
                (s32)*(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset) << 16;
            movement->velocity_y -=
                (s32)*(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset) << 16;
        }
        if (sprite->flags & 0x6000) {
            sprite->frameTable = D_80175E78;
            select_sprite_entry(
                sprite,
                D_80175E78[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
        }

    case 2:
    {
        u16 height = body->unk_A0.parts.high + 0x10;

        body->unk_A0.parts.high = height;
        if ((s16)height >= 0x31) {
            body->unk_A0.parts.high = 0x30;
            movement->velocity_y = 0;
            movement->velocity_x = 0;
        }
    }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        movement->velocity_z = 0;
        movement->velocity_y = 0;
        movement->velocity_x = 0;
        if (((S_80172DDC_0 *)body)->unk_A0.at02u.v < 0x30) {
            return;
        }
        {
            s32 current_state = body->action_phase.u;

            body->action_timer.u = 0;
            if (current_state == 0) {
                return;
            }
        }
        play_sound_if_enabled(0x808);
        body->action_phase.u++;
        create_parent_position_effect((u8 *)body - 0x20, (u8 *)actor + 0x2A,
                      (u8 *)body + 0x9B);
        return;

    case 3:
    {
        u8 *direction_x = (u8 *)((s8 *)dir_step_x);
        u8 *direction_y = (u8 *)((s8 *)dir_step_y);
        u16 timer;

        movement->velocity_x +=
            (s32)*(s16 *)(direction_x +
                (((u16)actor->facing >> 8) & 0xE)) << 17;

        movement->velocity_y +=
            (s32)*(s16 *)(direction_y +
                (((u16)actor->facing >> 8) & 0xE)) << 17;

        body->unk_A0.value -= (s32)body->action_timer.s << 17;
        timer = body->action_timer.u + 1;
        body->action_timer.u = timer;
        if ((s16)timer < 9) {
            return;
        }

        resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        sprite->frameTable = D_80175E80;
        select_sprite_entry(
            sprite,
            D_80175E80[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        movement->velocity_x =
            -*(s16 *)(direction_x +
                (((u16)actor->facing >> 8) & 0xE)) << 20;

        movement->velocity_y =
            -*(s16 *)(direction_y +
                (((u16)actor->facing >> 8) & 0xE)) << 20;
        ((S_80172DDC_0 *)body)->unk_A8 = movement->velocity_x / 6;
        ((S_80172DDC_0 *)body)->unk_AC = movement->velocity_y / 6;
        body->action_timer.u = 0;
        body->action_phase.u++;
        return;
    }

    case 4:
        movement->velocity_x -= ((S_80172DDC_0 *)body)->unk_A8;
        movement->velocity_y -= ((S_80172DDC_0 *)body)->unk_AC;
        body->unk_A0.value =
            rsin(body->action_timer.s * 146) * 160 + 0x100000;

    case 5:
    {
        u16 timer = body->action_timer.u + 1;

        body->action_timer.u = timer;
        if ((s16)timer < 7 && !(sprite->flags & 0x8000)) {
            return;
        }
    }
        movement->velocity_z = 0;
        movement->velocity_y = 0;
        movement->velocity_x = 0;
        set_record_integer_tile_center(movement, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        body->unk_8C.address = kewne_action_resume_address;
        g_dungeon_status.active_actor = 0;
        actor->action_flags &= 0x7FFF;
        body->action_state_flags &= 0xFFF7;
        advance_status_timers(actor);
    }
}
