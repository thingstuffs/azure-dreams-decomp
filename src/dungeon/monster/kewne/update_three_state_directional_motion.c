#include "dungeon/monster/kewne.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void select_sprite_entry(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern u8 D_80175E88[];
extern u8 resident_globals_page[];

/* Updates the actor's directional motion and animation across three action states. */
void update_three_state_directional_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 delta_x;
    s32 delta_y;
    s32 direction_offset;
    s32 facing_index;
    s32 object_type;
    s32 anim_table;
    s32 next_frame;
    u16 flags;
    s32 state;

    state = action->action_phase;
    switch (state) {
    case 0:
    {
        u8 *facing_ptr;

        flags = sprite->flags;
        if (flags & 0x8000) {
            sprite->flags = flags | 0x6000;
            action->action_phase = 2;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        if ((flags & 0x6000) == 0) {
            return;
        }
        if (action->unk_90.parts.high.s != 0) {
            return;
        }
        sprite->frameTable = D_80175E88;
        facing_ptr = &D_80175E88[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7];
        select_sprite_entry(sprite, *facing_ptr, 0);
        action->action_timer = 0;
        play_sound_if_enabled(0x808);
        action->action_phase++;
        return;
    }

    case 1:
    {
        u8 *direction_base;
        u8 *direction_base_2;
        s32 next_x;
        s32 next_y;
        s32 signed_value;

        anim_table = action->action_timer;
        direction_base = (u8 *)&dir_step_x;
        next_frame = anim_table + 1;
        anim_table -= 3;
        action->action_timer = next_frame;
        direction_offset = ((u16)actor->facing >> 8) & 0xE;
        anim_table = (u32)anim_table < 8U;
        direction_base = (u8 *)(direction_offset + (u8 *)direction_base);
        delta_x = *(s16 *)direction_base;
        direction_base_2 = (u8 *)&dir_step_y;
        signed_value = *(s16 *)((u8 *)(direction_offset + (u8 *)direction_base_2));
        delta_x = -delta_x;
        delta_x <<= 16;
        signed_value = -signed_value;
        delta_y = signed_value << 16;
        if (anim_table) {
            next_x = motion->velocity_x - delta_x;
            next_y = motion->velocity_y - delta_y;
            motion->velocity_x = next_x;
            motion->velocity_y = next_y;
        } else {
            signed_value = (s16)next_frame;
            if (signed_value < 0x12) {
                next_x = motion->velocity_x + delta_x;
                next_y = motion->velocity_y + delta_y;
                motion->velocity_x = next_x;
                motion->velocity_y = next_y;
            } else {
                motion->velocity_z = 0;
                motion->velocity_y = 0;
                motion->velocity_x = 0;
            }
        }
        object_type = sprite->unk_04;
        if ((object_type == 5 && (sprite->flags & 0x1000)) || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            anim_table = 0x80170000;
        } else {
            anim_table = 0x80170000;
        }
        {
            u8 *facing_ptr;

            if ((sprite->flags & 0xE000) == 0) {
                return;
            }
            anim_table += 0x5EB8;
            facing_ptr = (u8 *)resident_globals_page;
            PTR(sprite, 0x2C) = (void *)anim_table;
            facing_index = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
            facing_index &= 7;
            facing_ptr = (u8 *)(facing_index + anim_table);
            select_sprite_entry(sprite, *facing_ptr, 0);
        }
        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0xC) = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
advance_state:
        U8(action, 0x9B)++;
        return;
    }

    case 2:
    {

        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        PTR(action, 0x8C) = update_actor_animation_and_behavior;
        S32(resident_globals_page, 0x346C) = 0;
        U16(actor, 0x46) &= 0x7FFF;
        advance_status_timers(actor);
    }

    }
}
