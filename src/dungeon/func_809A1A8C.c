#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, u8, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern u8 D_801710EC[];
extern u8 D_80175E88[];
extern u8 D_80080000[];

/* Updates the actor's directional motion and animation across three action states. */
void update_three_state_directional_motion(void *action, void *motion, void *sprite, void *actor)
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

    state = U8(action, 0x9B);
    switch (state) {
    case 0:
    {
        u8 *facing_ptr;

        flags = U16(sprite, 0x14);
        if (flags & 0x8000) {
            U16(sprite, 0x14) = flags | 0x6000;
            U8(action, 0x9B) = 2;
            resolve_attack_damage_and_effects(actor, sprite, S16(actor, 0x2A), 1);
            return;
        }

        if ((flags & 0x6000) == 0) {
            return;
        }
        if (S16(action, 0x92) != 0) {
            return;
        }
        PTR(sprite, 0x2C) = D_80175E88;
        facing_ptr = &D_80175E88[((g_game_work.view.viewAngle + S16(actor, 0x2A) + 0x100) >> 9) & 7];
        func_80047784(sprite, *facing_ptr, 0);
        U16(action, 0x96) = 0;
        play_sound_if_enabled(0x808);
        U8(action, 0x9B)++;
        return;
    }

    case 1:
    {
        u8 *direction_base;
        u8 *direction_base_2;
        s32 next_x;
        s32 next_y;
        s32 signed_value;

        anim_table = U16(action, 0x96);
        direction_base = (u8 *)&dir_step_x;
        next_frame = anim_table + 1;
        anim_table -= 3;
        U16(action, 0x96) = next_frame;
        direction_offset = (U16(actor, 0x2A) >> 8) & 0xE;
        anim_table = (u32)anim_table < 8U;
        direction_base = (u8 *)(direction_offset + (s32)direction_base);
        delta_x = *(s16 *)direction_base;
        direction_base_2 = (u8 *)&dir_step_y;
        signed_value = *(s16 *)((s32)(direction_offset + (s32)direction_base_2));
        delta_x = -delta_x;
        delta_x <<= 16;
        signed_value = -signed_value;
        delta_y = signed_value << 16;
        if (anim_table) {
            next_x = S32(motion, 0xC) - delta_x;
            next_y = S32(motion, 0x10) - delta_y;
            S32(motion, 0xC) = next_x;
            S32(motion, 0x10) = next_y;
        } else {
            signed_value = (s16)next_frame;
            if (signed_value < 0x12) {
                next_x = S32(motion, 0xC) + delta_x;
                next_y = S32(motion, 0x10) + delta_y;
                S32(motion, 0xC) = next_x;
                S32(motion, 0x10) = next_y;
            } else {
                S32(motion, 0x14) = 0;
                S32(motion, 0x10) = 0;
                S32(motion, 0xC) = 0;
            }
        }
        object_type = S8(sprite, 4);
        if ((object_type == 5 && (U16(sprite, 0x14) & 0x1000)) || (U16(sprite, 0x14) & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, S16(actor, 0x2A), 1);
            anim_table = 0x80170000;
        } else {
            anim_table = 0x80170000;
        }
        {
            u8 *facing_ptr;

            if ((U16(sprite, 0x14) & 0xE000) == 0) {
                return;
            }
            anim_table += 0x5EB8;
            facing_ptr = (u8 *)D_80080000;
            PTR(sprite, 0x2C) = (void *)anim_table;
            facing_index = (*(s16 *)(facing_ptr + 0x3228) + S16(actor, 0x2A) + 0x100) >> 9;
            facing_index &= 7;
            facing_ptr = (u8 *)(facing_index + anim_table);
            func_80047784(sprite, *facing_ptr, 0);
        }
        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0xC) = 0;
        set_record_integer_tile_center(motion, U8(sprite, 0x24), U8(sprite, 0x25));
advance_state:
        U8(action, 0x9B)++;
        return;
    }

    case 2:
    {

        if ((U16(sprite, 0x14) & 0xE000) == 0) {
            return;
        }
        reduce_actor_food_meter(actor, 0x100);
        PTR(action, 0x8C) = D_801710EC;
        S32(D_80080000, 0x346C) = 0;
        U16(actor, 0x46) &= 0x7FFF;
        advance_status_timers(actor);
    }

    }
}
