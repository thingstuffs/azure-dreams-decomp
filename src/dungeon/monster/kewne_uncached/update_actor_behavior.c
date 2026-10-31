#include "dungeon/monster/kewne_uncached.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))


extern void select_sprite_entry(void *, u8, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);

extern u8 kewne_uncached_action_resume_address[];
extern u8 D_80175C78[];
extern u8 resident_globals_page[];

/* Updates action movement and directional animation through three states. */
void update_actor_behavior_2(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *object, ActorRecord *actor)
{
    s32 delta_x;
    s32 delta_y;
    s32 direction_off;
    s32 facing_idx;
    s32 object_type;
    s32 anim_table;
    s32 next_tick;
    u16 flags;
    s32 state;

    state = action->action_phase.u;
    switch (state) {
    case 0:
    {
        u8 *facing_ptr;

        flags = object->flags;
        if (flags & 0x8000) {
            object->flags = flags | 0x6000;
            action->action_phase.u = 2;
            resolve_attack_damage_and_effects(actor, object, actor->facing, 1);
            return;
        }
        if ((flags & 0x6000) == 0) {
            return;
        }
        if (action->unk_90.parts.high.s != 0) {
            return;
        }
        object->frameTable = D_80175C78;
        facing_ptr = &D_80175C78[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7];
        select_sprite_entry(object, *facing_ptr, 0);
        action->action_timer.u = 0;
        play_sound_if_enabled(0x808);
        action->action_phase.u++;
        return;
    }

    case 1:
    {
        u8 *direction_base;
        u8 *direction_base_2;
        s32 motion_x;
        s32 motion_y;
        s32 signed_value;

        anim_table = action->action_timer.u;
        direction_base = (u8 *)&dir_step_x;
        next_tick = anim_table + 1;
        anim_table -= 3;
        action->action_timer.u = next_tick;
        direction_off = ((u16)actor->facing >> 8) & 0xE;
        anim_table = (u32)anim_table < 8U;
        direction_base = (direction_off + (u8 *)direction_base);
        delta_x = *(s16 *)direction_base;
        direction_base_2 = (u8 *)&dir_step_y;
        signed_value = *(s16 *)((direction_off + (u8 *)direction_base_2));
        delta_x = -delta_x;
        delta_x <<= 16;
        signed_value = -signed_value;
        delta_y = signed_value << 16;
        if (anim_table) {
            motion_x = motion->velocity_x - delta_x;
            motion_y = motion->velocity_y - delta_y;
            motion->velocity_x = motion_x;
            motion->velocity_y = motion_y;
        } else {
            signed_value = (s16)next_tick;
            if (signed_value < 0x12) {
                motion_x = motion->velocity_x + delta_x;
                motion_y = motion->velocity_y + delta_y;
                motion->velocity_x = motion_x;
                motion->velocity_y = motion_y;
            } else {
                motion->velocity_z = 0;
                motion->velocity_y = 0;
                motion->velocity_x = 0;
            }
        }
        object_type = object->unk_04;
        if (object_type == 5 && (object->flags & 0x9000)) {
            resolve_attack_damage_and_effects(actor, object, actor->facing, 1);
            anim_table = 0x80170000;
        } else {
            anim_table = 0x80170000;
        }
        {
            u8 *facing_ptr;

            if ((object->flags & 0x6000) == 0) {
                return;
            }
            anim_table += 0x5CA8;
            facing_ptr = resident_globals_page;
            PTR(object, 0x2C) = (void *)anim_table;
            facing_idx = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
            facing_idx &= 7;
            facing_ptr = (u8 *)(facing_idx + anim_table);
            select_sprite_entry(object, *facing_ptr, 0);
        }
        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0xC) = 0;
        set_record_integer_tile_center(motion, object->tile_x, object->tile_y);
        U8(action, 0x9B)++;
        return;
    }

    case 2:
    {
        void *actor_arg;

        if ((object->flags & 0xE000) == 0) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        actor_arg = actor;
        PTR(action, 0x8C) = kewne_uncached_action_resume_address;
        S32(resident_globals_page, 0x346C) = 0;
        advance_status_timers(actor_arg);
        U16(actor, 0x46) &= 0x7FFF;
    }

    }
    return;
}
