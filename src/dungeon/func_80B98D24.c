#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"



void func_80047784();
void *resolve_attack_damage_and_effects();
void set_record_integer_tile_center();
s32 advance_status_timers();
s32 play_sound_if_enabled();
void reduce_actor_food_meter();
extern M2C_UNK D_80170E9C;
extern u8 D_80174F30;
extern u8 D_80174F38;
extern u8 D_80174F40;


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
void advance_action_phases_and_animation(void *action, EntityRec *motion, void *sprite, void *actor) {
    u16 move_ticks;
    u16 settle_ticks;
    u8 phase;

    phase = ((S_80172524_0 *)action)->unk_9B.n;
    switch (phase) {
    case 0:
        ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 | 8);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172524_0 *)action)->unk_9B.n = 5U;
            ((S_80172524_0 *)action)->unk_96.u = 0U;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v
                | 0x6000);
            resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }
        motion->unk_0C = (s32) (*(s16 *)(((u8 *)dir_step_x) + (((u16) ((EntityRec *)actor)->facing >> 8) & 0xE)) << 0x14);
        motion->unk_10 = (s32) (*(s16 *)(((u8 *)dir_step_y) + (((u16) ((EntityRec *)actor)->facing >> 8) & 0xE)) << 0x14);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 1:
        motion->unk_0C = (s32) ((s32) motion->unk_0C >> 1);
        motion->unk_10 = (s32) ((s32) motion->unk_10 >> 1);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(u8 **)((u8 *)sprite + (0x2C))) = (u8 *)&D_80174F30;
        func_80047784(sprite, *(u8 *)((((s32) (g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7) + (u32)&D_80174F30), 0);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 2:
        motion->unk_0C = (s32) ((s32) motion->unk_0C >> 1);
        motion->unk_10 = (s32) ((s32) motion->unk_10 >> 1);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        play_sound_if_enabled(0x808);
        (*(u8 **)((u8 *)sprite + (0x2C))) = (u8 *)&D_80174F38;
        func_80047784(sprite, *(u8 *)((((s32) (g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7) + (u32)&D_80174F38), 0);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2) {
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000) {
                resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
                {
                    u16 move_duration = 6;
                    ((S_80172524_0 *)action)->unk_96.u = move_duration;
                }
                ((S_80172524_0 *)action)->unk_9B.n++;
                return;
            }
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(u8 **)((u8 *)sprite + (0x2C))) = &D_80174F40;
        func_80047784(sprite, *((((s32) (g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7)
            + &D_80174F40), 0);
        resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
        ((S_80172524_0 *)action)->unk_9B.n = 5U;
        ((S_80172524_0 *)action)->unk_96.u = 0;
        return;
    case 4:
        move_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
        ((S_80172524_0 *)action)->unk_96.u = move_ticks;
        if ((s16) move_ticks > 0) {
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->unk_0C = ((target_coord - current_coord) << 0x10) / (s16) move_ticks;
            }
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->unk_10 = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
            }
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(u8 **)((u8 *)sprite + (0x2C))) = (u8 *)&D_80174F40;
        func_80047784(sprite, *(u8 *)((((s32) (g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7) + (u32)&D_80174F40), 0);
        ((S_80172524_0 *)action)->unk_9B.n++;
        return;
    case 5:
        settle_ticks = ((S_80172524_0 *)action)->unk_96.u - 1;
        ((S_80172524_0 *)action)->unk_96.u = settle_ticks;
        if ((s16) settle_ticks > 0) {
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->unk_0C = ((target_coord - current_coord) << 0x10) / (s16) settle_ticks;
            }
            {
                s32 target_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->unk_10 = ((target_coord - current_coord) << 0x10) / ((S_80172524_0 *)action)->unk_96.s;
            }
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        ((S_80172524_0 *)action)->unk_98 = (u16) (((S_80172524_0 *)action)->unk_98 & 0xFFF7);
        reduce_actor_food_meter(actor, 0x100);
        ((S_80172524_0 *)action)->unk_8C = &D_80170E9C;
        g_dungeon_status.unk_0C = 0;
        ((EntityRec *)actor)->unk_46 = (u16) ((*(u16 *)((u8 *)actor + (0x46))) & 0x7FFF);
        advance_status_timers(actor);
        return;
    default:
        return;
    }
}
