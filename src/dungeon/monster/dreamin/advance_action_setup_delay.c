#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void select_sprite_entry(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);

extern void *D_800E3DE8;
extern u8 D_80170E68;
extern u8 D_80173894[];

/* Advances an actor action through animation setup, a delay, and completion. */
void advance_action_setup_delay(void *action, void *motion, void *sprite, void *actor)
{
    s32 phase;
    s32 loaded_phase;
    u16 delay_ticks;

    phase = U8(action, 0x9B);
    switch (phase) {
    case 0:
        if (U16(sprite, 0x14) & 0x8000) {
            U8(action, 0x9B) = 2;
            U16(sprite, 0x14) |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, S16(actor, 0x2A), 1);
            return;
        }

        S32(motion, 0x14) = 0;
        S32(motion, 0x10) = 0;
        S32(motion, 0x0C) = 0;
        PTR(sprite, 0x2C) = D_80173894;
        select_sprite_entry(sprite,
            D_80173894[((g_game_work.view.camera_rotation.parts.viewAngle + S16(actor, 0x2A) + 0x100) >> 9) & 7],
            0);
        loaded_phase = U8(action, 0x9B);
        U16(action, 0x96) = 0;
        U8(action, 0x9B) = loaded_phase + 1;
        return;

    case 1:
        delay_ticks = U16(action, 0x96) + 1;
        U16(action, 0x96) = delay_ticks;
        if ((s16)delay_ticks != 10) {
            return;
        }
        play_sound_if_enabled(0x808);
        resolve_attack_damage_and_effects(actor, sprite, S16(actor, 0x2A), 1);
        loaded_phase = U8(action, 0x9B);

        U8(action, 0x9B) = loaded_phase + 1;
        return;

    case 2:
        if (!(U16(sprite, 0x14) & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(motion, U8(sprite, 0x24), U8(sprite, 0x25));
        reduce_actor_food_meter(actor, 0x100);
        PTR(action, 0x8C) = &D_80170E68;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (S8(actor, 0x6D) == 0) {
            U16(actor, 0x46) &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)actor - 0x20;
        }

        return;
    }
}
