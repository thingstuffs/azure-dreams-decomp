#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void create_three_linked_palette_objects(void *, void *);

extern s32 D_801710EC;
extern u8 D_80175E58[];
extern u8 D_80175E60[];
extern u8 D_80175E68[];

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
} S_801728A8_0;   /* arg0 in update_movement_height_and_animation */

typedef struct S_801728A8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801728A8_2;   /* call_a0 in update_movement_height_and_animation */

typedef struct S_801728A8_4 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_801728A8_4;   /* arg3 in update_movement_height_and_animation */

/* Updates movement, height, and animation through the action states. */
void update_movement_height_and_animation(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
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
            if (sprite->flags & 0x8000) {
                ((S_801728A8_0 *)action)->unk_9B.n = 4;
                sprite->flags |= 0x6000;
                resolve_attack_damage_and_effects(actor, sprite, ((S_801728A8_2 *)actor)->unk_2A, 1);
                return;
            }
        }

        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
        ((S_801728A8_0 *)action)->unk_A0.at00.v += 0x60000;
        if (((S_801728A8_0 *)action)->unk_A0.at02.v >= 0x31) {
            ((S_801728A8_0 *)action)->unk_A0.at02.v = 0x30;
        }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (((S_801728A8_0 *)action)->unk_A0.at02.v < 0x30) {
            return;
        }
        sprite->frameTable = D_80175E58;
        select_sprite_entry(sprite,
            D_80175E58[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        create_three_linked_palette_objects((u8 *)action - 0x20, (u8 *)actor + 0x2A);
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
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -func_800644B8(((S_801728A8_0 *)action)->unk_96.s * 170);
            ((S_801728A8_0 *)action)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
            timer = ((S_801728A8_0 *)action)->unk_96.u + 1;
            ((S_801728A8_0 *)action)->unk_96.u = timer;
            if (timer < 9) {
                return;
            }
        }
        sprite->frameTable = D_80175E60;
        select_sprite_entry(sprite,
            D_80175E60[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
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
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -func_800644B8(((S_801728A8_0 *)action)->unk_96.s * 170);
            ((S_801728A8_0 *)action)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
            timer = ((S_801728A8_0 *)action)->unk_96.u + 1;
            ((S_801728A8_0 *)action)->unk_96.u = timer;
            if (timer < 13) {
                return;
            }
            sprite->frameTable = D_80175E68;
            select_sprite_entry(sprite,
                D_80175E68[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801728A8_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                0);

            velocity_x = -*(s16 *)((u8 *)directions_x +
                (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
            velocity_x += velocity_x >> 2;
            motion->velocity_x = velocity_x;

            velocity_y = -*(s16 *)((u8 *)directions_y +
                (((u16)((S_801728A8_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
            velocity_y += velocity_y >> 2;
            motion->velocity_y = velocity_y;
            ((S_801728A8_0 *)action)->unk_A8 = motion->velocity_x / 24;
            ((S_801728A8_0 *)action)->unk_AC = motion->velocity_y / 24;
        }
        ((S_801728A8_0 *)action)->unk_96.s = 12;
        ((S_801728A8_0 *)action)->unk_9B.n++;
        return;

    case 3:
        motion->velocity_x -= ((S_801728A8_0 *)action)->unk_A8;
        motion->velocity_y -= ((S_801728A8_0 *)action)->unk_AC;
        if (((S_801728A8_0 *)action)->unk_A0.at02.v > 0) {
            ((S_801728A8_0 *)action)->unk_A0.at02u.v -= 0x10;
        } else {
            ((S_801728A8_0 *)action)->unk_A0.at02.v = 0;
        }
    case 4:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        spend_actor_mp(actor, 0x100);
        ((S_801728A8_0 *)action)->unk_8C = &D_801710EC;
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)actor + (0x46))) &= 0x7FFF;
        ((S_801728A8_0 *)action)->unk_98 &= 0xFFF7;
        advance_status_timers(actor);
    }
}
