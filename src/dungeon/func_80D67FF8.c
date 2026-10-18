#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern u8 D_800E2380[8];
extern u8 D_800E2388[8];
extern s32 D_80171F1C;


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

typedef struct S_801737F8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801737F8_1;   /* arg1 in advance_actor_animation_and_fall */


/* Advance the actor animation state, timers, and downward movement. */
void advance_actor_animation_and_fall(void *action, void *motion, void *sprite, EntityRec *actor)
{
    u8 state;

    state = ((S_801737F8_0 *)action)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        ((S_801737F8_1 *)motion)->unk_14 = 0;
        ((S_801737F8_1 *)motion)->unk_10 = 0;
        ((S_801737F8_1 *)motion)->unk_0C = 0;
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_801737F8_0 *)action)->unk_9B = 4;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }
        if (((S_801737F8_0 *)action)->unk_92.s !=
            (s16)(sample_terrain_surface_height(((S_801737F8_1 *)motion)->unk_02,
                                ((S_801737F8_1 *)motion)->unk_06,
                                (s16)(((u16)actor->unk_88) - 0x20)) -
                  ((u16)actor->unk_88))) {
            return;
        }
        ((S_801737F8_0 *)action)->unk_9B++;
        ((Rec_D_80082E80 *)sprite)->unk_10.as_s16 = 0x20;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x000C;
        return;

    case 1:
        (*(u8 **)((u8 *)sprite + 0x2C)) = D_800E2380;
        func_80047784(sprite,
            D_800E2380[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801737F8_0 *)action)->unk_96.u = 0;
        ((S_801737F8_0 *)action)->unk_9B++;
        return;

    case 2:
        {
            s32 duration = 10;
            u16 timer = ((S_801737F8_0 *)action)->unk_96.u + 1;

            ((S_801737F8_0 *)action)->unk_96.u = timer;
            if ((s16)timer == duration || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
                resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
                ((S_801737F8_0 *)action)->unk_96.u = duration;
                ((S_801737F8_0 *)action)->unk_9B++;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x0800;
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
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
            ((S_801737F8_0 *)action)->unk_98 |= 8;
            (*(u8 **)((u8 *)sprite + 0x2C)) = D_800E2388;
            func_80047784(sprite,
                D_800E2388[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        }

        if (((S_801737F8_0 *)action)->unk_92.s >= -0x1F) {
            ((S_801737F8_0 *)action)->unk_92.u -= 4;
            return;
        }
        ((S_801737F8_0 *)action)->unk_9B++;
    case 4:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        reduce_actor_food_meter(actor, 0x100);
        ((S_801737F8_0 *)action)->unk_8C = &D_80171F1C;
        g_dungeon_status.unk_0C = 0;
        advance_status_timers(actor);
        actor->unk_46 &= 0x7FFF;
        actor->flags1C |= 0x40000;
        ((S_801737F8_0 *)action)->unk_98 |= 8;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xFFF3;
    }
}
