#include "common.h"
#include "shared/object_node.h"
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
#include "sdk/libgte.h"

extern void create_three_linked_palette_objects(void *, void *);

extern s32 kewne_action_resume_address;
extern u8 D_80175E58[];
extern u8 D_80175E60[];
extern u8 D_80175E68[];


/* Updates movement, height, and animation through the action states. */
void update_movement_height_and_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 direction_x_2;
    u32 step_x;
    s32 step_y;
    u8 state;

    state = action->action_phase;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        {
            if (sprite->flags & 0x8000) {
                action->action_phase = 4;
                sprite->flags |= 0x6000;
                resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
                return;
            }
        }

        motion->velocity_x -=
            dir_step_x[(actor->facing >> 9) & 7] << 14;
        motion->velocity_y -=
            dir_step_y[(actor->facing >> 9) & 7] << 14;
        action->unk_A0.value += 0x60000;
        if (action->unk_A0.parts.high >= 0x31) {
            action->unk_A0.parts.high = 0x30;
        }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (action->unk_A0.parts.high < 0x30) {
            return;
        }
        sprite->frameTable = D_80175E58;
        select_sprite_entry(sprite,
            D_80175E58[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        create_three_linked_palette_objects(NODE_HEADER(action), &actor->facing);
        state = action->action_phase;
        action->action_timer = 0;
        action->action_phase = state + 1;
        return;

    case 1:
        {
            s32 direction_offset;
            s32 arc;
            s16 timer;

            direction_offset = (actor->facing >> 8) & 0xE;
            step_x = dir_step_x[direction_offset >> 1] << 16;
            step_y = dir_step_y[direction_offset >> 1] << 16;
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -rsin((action->action_timer) * 170);
            action->unk_A0.value = ((arc * 5) << 8) + 0x300000;
            timer = action->action_timer + 1;
            action->action_timer = timer;
            if (timer < 9) {
                return;
            }
        }
        sprite->frameTable = D_80175E60;
        select_sprite_entry(sprite,
            D_80175E60[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x808);
        state = action->action_phase;
        action->action_phase = state + 1;
        return;

    case 2:
        {
            s16 *directions_x;
            s16 *directions_y;
            s16 *direction_x_ptr;
            s16 *direction_y_ptr;
            s32 arc;
            s32 direction_offset;
            s16 timer;
            s32 velocity_x;
            s32 velocity_y;

            if ((action->action_timer) == 10) {
                resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            }
            directions_x = (s16 *)((s8 *)dir_step_x);
            direction_offset = (actor->facing >> 8) & 0xE;
            direction_x_ptr = (s16 *)(direction_offset + (u8 *)directions_x);
            directions_y = (s16 *)((s8 *)dir_step_y);
            direction_y_ptr = (s16 *)(direction_offset + (u8 *)directions_y);
            direction_x_2 = *direction_x_ptr;
            arc = *direction_y_ptr;
            step_x = direction_x_2 << 16;
            step_y = arc << 16;
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -rsin((action->action_timer) * 170);
            action->unk_A0.value = ((arc * 5) << 8) + 0x300000;
            timer = action->action_timer + 1;
            action->action_timer = timer;
            if (timer < 13) {
                return;
            }
            sprite->frameTable = D_80175E68;
            select_sprite_entry(sprite,
                D_80175E68[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);

            velocity_x = -*(s16 *)((u8 *)directions_x +
                ((actor->facing >> 8) & 0xE)) << 18;
            velocity_x += velocity_x >> 2;
            motion->velocity_x = velocity_x;

            velocity_y = -*(s16 *)((u8 *)directions_y +
                ((actor->facing >> 8) & 0xE)) << 18;
            velocity_y += velocity_y >> 2;
            motion->velocity_y = velocity_y;
            (*(s32 *)&action->unk_A8) = motion->velocity_x / 24;
            action->unk_AC.value = motion->velocity_y / 24;
        }
        action->action_timer = 12;
        action->action_phase++;
        return;

    case 3:
        motion->velocity_x -= (*(s32 *)&action->unk_A8);
        motion->velocity_y -= action->unk_AC.value;
        if (action->unk_A0.parts.high > 0) {
            action->unk_A0.parts.high -= 0x10;
        } else {
            action->unk_A0.parts.high = 0;
        }
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 0x100);
        action->unk_8C.word_ptr = &kewne_action_resume_address;
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)actor + (0x46))) &= 0x7FFF;
        action->action_state_flags &= 0xFFF7;
        advance_status_timers(actor);
    }
}
