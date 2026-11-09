#include "common.h"
#include "shared/object_node.h"
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
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "sdk/libgte.h"

extern void create_parent_attached_effect(void *, void *, void *);

extern u8 kewne_uncached_action_resume_address[9];
extern u8 D_80175C68[8];
extern u8 D_80175C70[8];



/* Updates the actor's staged movement, height, and directional animation. */
void update_staged_movement_height_and_animation(ActorRecord *motion, ObjectPosition *velocity, SpriteFrameState *sprite, ActorRecord *actor)
{
    u8 state;

    state = motion->action_phase;
    switch (state) {

    case 0:
        if (!(sprite->flags & 0x8000)) {
            play_sound_if_enabled(0x80E);
        }
        motion->action_phase++;

    case 1:
        if (sprite->flags & 0x8000) {
            motion->action_timer = 0x100;
            motion->action_phase = 5;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        sprite->frame_ticks -= 2;
        {
            u32 direction_offset = ((u16)actor->facing >> 8) & 0xE;
            velocity->velocity_x -=
                (s32)dir_step_x[direction_offset >> 1] << 16;
            velocity->velocity_y -=
                (s32)dir_step_y[direction_offset >> 1] << 16;
        }
        if (sprite->flags & 0x6000) {
            sprite->frameTable = D_80175C68;
            select_sprite_entry(
                sprite,
                D_80175C68[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            motion->action_phase++;
        }

    case 2:
    {
        u16 height = motion->unk_A0.parts.high + 0x10;

        motion->unk_A0.parts.high = height;
        if ((s16)height >= 0x31) {
            motion->unk_A0.parts.high = 0x30;
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
        if (motion->unk_A0.parts.high < 0x30) {
            return;
        }
        {
            s32 current_state = motion->action_phase;

            motion->action_timer = 0;
            if (current_state == 0) {
                return;
            }
        }
        play_sound_if_enabled(0x808);
        motion->action_phase++;
        create_parent_attached_effect(NODE_HEADER(motion), &actor->facing,
                      &motion->action_phase);
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

        motion->unk_A0.value -= (s32)(motion->action_timer) << 17;
        frame = motion->action_timer + 1;
        motion->action_timer = frame;
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
        (*(s32 *)&motion->unk_A8) = velocity->velocity_x / 6;
        motion->unk_AC.value = velocity->velocity_y / 6;
        motion->action_timer = 0;
        motion->action_phase++;
        return;
    }

    case 4:
        velocity->velocity_x -= (*(s32 *)&motion->unk_A8);
        velocity->velocity_y -= motion->unk_AC.value;
        motion->unk_A0.value =
            rsin((motion->action_timer) * 146) * 160 + 0x100000;

    case 5:
    {
        u16 frame = motion->action_timer + 1;

        motion->action_timer = frame;
        if ((s16)frame < 7 && !(sprite->flags & 0x8000)) {
            return;
        }
    }
        velocity->velocity_z = 0;
        velocity->velocity_y = 0;
        velocity->velocity_x = 0;
        set_record_integer_tile_center(velocity, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        motion->unk_8C.byte_ptr = kewne_uncached_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        break;
    default:
        return;
    }
}
