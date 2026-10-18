/* Relink of matched dungeon/func_809A10A8; every changed retail word is a paired relocation. */
#define update_movement_height_and_animation func_8014E8A8
#define D_801710EC D_8014D0EC
#define D_80175E58 D_80151E58
#define D_80175E60 D_80151E60
#define D_80175E68 D_80151E68
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void reduce_actor_food_meter(void *, s32);
extern void func_80150910(void *, s32);

extern s32 D_8014D0EC;
extern u8 D_80151E58[];
extern u8 D_80151E60[];
extern u8 D_80151E68[];


typedef struct S_801728A8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    union { u8 n; u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_801728A8_0;   /* arg0 in func_8014E8A8 */


typedef struct S_801728A8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801728A8_2;   /* call_a0 in func_8014E8A8 */


typedef struct S_801728A8_4 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_801728A8_4;   /* arg3 in func_8014E8A8 */

/* Updates movement, height, and animation through the action states. */
void func_8014E8A8(void *action, EntityRec *motion, void *sprite, void *actor)
{
    s32 direction_x_2;
    u32 step_x;
    s32 step_y;
    u8 state;

    state = ((S_801728A8_0 *)action)->unk_9B.n;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        {
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
                ((S_801728A8_0 *)action)->unk_9B.n = 4;
                ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x6000;
                resolve_attack_damage_and_effects(actor, sprite, ((S_801728A8_2 *)actor)->unk_2A, 1);
                return;
            }
        }

        motion->unk_0C -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
        motion->unk_10 -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
        ((S_801728A8_0 *)action)->unk_A0.at00.v += 0x60000;
        if (((S_801728A8_0 *)action)->unk_A0.at02.v >= 0x31) {
            ((S_801728A8_0 *)action)->unk_A0.at02.v = 0x30;
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        if (((S_801728A8_0 *)action)->unk_A0.at02.v < 0x30) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80151E58;
        func_80047784(sprite,
            D_80151E58[((g_game_work.view.viewAngle + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        func_80150910((u8 *)action - 0x20, (u8 *)actor + 0x2A);
        state = ((S_801728A8_0 *)action)->unk_9B.n;
        ((S_801728A8_0 *)action)->unk_96.s = 0;
        ((S_801728A8_0 *)action)->unk_9B.n = state + 1;
        return;

    case 1:
        {
            s32 direction_offset;
            s32 arc;
            s16 timer;

            direction_offset = ((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE;
            step_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset) << 16;
            step_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset) << 16;
            motion->unk_0C += step_x;
            motion->unk_10 += step_y;
            arc = -func_800644B8(((S_801728A8_0 *)action)->unk_96.s * 170);
            ((S_801728A8_0 *)action)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
            timer = ((S_801728A8_0 *)action)->unk_96.u + 1;
            ((S_801728A8_0 *)action)->unk_96.u = timer;
            if (timer < 9) {
                return;
            }
        }
        (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80151E60;
        func_80047784(sprite,
            D_80151E60[((g_game_work.view.viewAngle + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x808);
        state = ((S_801728A8_0 *)action)->unk_9B.n;
        ((S_801728A8_0 *)action)->unk_9B.n = state + 1;
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

            if (((S_801728A8_0 *)action)->unk_96.s == 10) {
                resolve_attack_damage_and_effects(actor, sprite, ((S_801728A8_4 *)actor)->unk_2A.s, 1);
            }
            directions_x = (s16 *)((s8 *)dir_step_x);
            direction_offset = ((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE;
            direction_x_ptr = (s16 *)(direction_offset + (u8 *)directions_x);
            directions_y = (s16 *)((s8 *)dir_step_y);
            direction_y_ptr = (s16 *)(direction_offset + (u8 *)directions_y);
            direction_x_2 = *direction_x_ptr;
            arc = *direction_y_ptr;
            step_x = direction_x_2 << 16;
            step_y = arc << 16;
            motion->unk_0C += step_x;
            motion->unk_10 += step_y;
            arc = -func_800644B8(((S_801728A8_0 *)action)->unk_96.s * 170);
            ((S_801728A8_0 *)action)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
            timer = ((S_801728A8_0 *)action)->unk_96.u + 1;
            ((S_801728A8_0 *)action)->unk_96.u = timer;
            if (timer < 13) {
                return;
            }
            (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80151E68;
            func_80047784(sprite,
                D_80151E68[((g_game_work.view.viewAngle + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                0);

            velocity_x = -*(s16 *)((u8 *)directions_x +
                (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
            velocity_x += velocity_x >> 2;
            motion->unk_0C = velocity_x;

            velocity_y = -*(s16 *)((u8 *)directions_y +
                (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
            velocity_y += velocity_y >> 2;
            motion->unk_10 = velocity_y;
            ((S_801728A8_0 *)action)->unk_A8 = motion->unk_0C / 24;
            ((S_801728A8_0 *)action)->unk_AC = motion->unk_10 / 24;
        }
        ((S_801728A8_0 *)action)->unk_96.s = 12;
        ((S_801728A8_0 *)action)->unk_9B.n++;
        return;

    case 3:
        motion->unk_0C -= ((S_801728A8_0 *)action)->unk_A8;
        motion->unk_10 -= ((S_801728A8_0 *)action)->unk_AC;
        if (((S_801728A8_0 *)action)->unk_A0.at02.v > 0) {
            ((S_801728A8_0 *)action)->unk_A0.at02u.v -= 0x10;
        } else {
            ((S_801728A8_0 *)action)->unk_A0.at02.v = 0;
        }
    case 4:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        reduce_actor_food_meter(actor, 0x100);
        ((S_801728A8_0 *)action)->unk_8C = &D_8014D0EC;
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)actor + (0x46))) &= 0x7FFF;
        ((S_801728A8_0 *)action)->unk_98 &= 0xFFF7;
        advance_status_timers(actor);
    }
}
