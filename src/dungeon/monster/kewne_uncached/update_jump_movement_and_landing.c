#include "common.h"
#include "dungeon/monster/kewne_uncached.h"
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


extern s32 rsin(s32);

extern void func_801753DC(void *, void *);

extern s32 kewne_uncached_action_resume_address;
extern u8 D_80175C48[];
extern u8 D_80175C50[];
extern u8 D_80175C58[];

typedef struct S_80173408_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
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
} S_80173408_0;   /* arg0 in update_jump_movement_and_landing */

typedef struct S_80173408_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80173408_2;   /* call_a0 in update_jump_movement_and_landing */

typedef struct S_80173408_4 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80173408_4;   /* arg3 in update_jump_movement_and_landing */

/* Updates jump movement, animation, and landing across five states. */
/* Animates Kewne's backward windup and arcing strike, applies damage at tick 10, then returns to its tile
 * and spends MP. */
void update_jump_movement_and_landing(void *jump, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    u32 step_x;
    s32 step_y;
    u8 state;

    state = ((S_80173408_0 *)jump)->unk_9B.n;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        {
            if (sprite->flags & 0x8000) {
                ((S_80173408_0 *)jump)->unk_9B.n = 4;
                sprite->flags |= 0x6000;
                resolve_attack_damage_and_effects(actor, sprite, ((S_80173408_2 *)actor)->unk_2A, 1);
                return;
            }
        }

        motion->velocity_x -=
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
        motion->velocity_y -=
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 14;
        ((S_80173408_0 *)jump)->unk_A0.at00.v += 0x60000;
        if (((S_80173408_0 *)jump)->unk_A0.at02.v >= 0x31) {
            ((S_80173408_0 *)jump)->unk_A0.at02.v = 0x30;
        }
        if (!(sprite->flags & 0x6000)) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (((S_80173408_0 *)jump)->unk_A0.at02.v < 0x30) {
            return;
        }
        sprite->frameTable = D_80175C48;
        select_sprite_entry(sprite,
            D_80175C48[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173408_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        func_801753DC((u8 *)jump - 0x20, (u8 *)actor + 0x2A);
        state = ((S_80173408_0 *)jump)->unk_9B.v;
        ((S_80173408_0 *)jump)->unk_96.s = 0;
        ((S_80173408_0 *)jump)->unk_9B.n = state + 1;
        return;

    case 1:
        {
            s16 *x_table;
            s16 *y_table;
            s16 *x_entry;
            s16 *y_entry;
            s32 arc;
            s16 timer;

            x_table = (s16 *)((s8 *)dir_step_x);
            y_entry = (s16 *)(((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE);
            x_entry = (s16 *)((s32)y_entry + (u8 *)x_table);
            y_table = (s16 *)((s8 *)dir_step_y);
            y_entry = (s16 *)((s32)y_entry + (u8 *)y_table);
            arc = *x_entry;
            y_entry = (s16 *)(*y_entry);
            step_x = arc << 16;
            step_y = (s32)y_entry << 16;
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -rsin(((S_80173408_0 *)jump)->unk_96.s * 170);
            ((S_80173408_0 *)jump)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
            timer = ((S_80173408_0 *)jump)->unk_96.u + 1;
            ((S_80173408_0 *)jump)->unk_96.u = timer;
            if (timer < 9) {
                return;
            }
        }
        sprite->frameTable = D_80175C50;
        select_sprite_entry(sprite,
            D_80175C50[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173408_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        play_sound_if_enabled(0x808);
        state = ((S_80173408_0 *)jump)->unk_9B.n;
        ((S_80173408_0 *)jump)->unk_9B.n = state + 1;
        return;

    case 2:
        {
            s16 *x_table;
            s16 *y_table;
            s16 *x_entry;
            s16 *y_entry;
            s32 arc;
            s32 direction_x;
            s32 dir_offset;
            s16 timer;
            s32 velocity_x;
            s32 velocity_y;

            if ((*(s16 *)((u8 *)jump + 0x96)) == 10) {
                resolve_attack_damage_and_effects(actor, sprite, ((S_80173408_4 *)actor)->unk_2A.s, 1);
            }
            x_table = (s16 *)((s8 *)dir_step_x);
            dir_offset = ((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE;
            x_entry = (s16 *)(dir_offset + (u8 *)x_table);
            y_table = (s16 *)((s8 *)dir_step_y);
            y_entry = (s16 *)(dir_offset + (u8 *)y_table);
            direction_x = *x_entry;
            arc = *y_entry;
            step_x = direction_x << 16;
            step_y = arc << 16;
            motion->velocity_x += step_x;
            motion->velocity_y += step_y;
            arc = -rsin(((S_80173408_0 *)jump)->unk_96.s * 170);
            ((S_80173408_0 *)jump)->unk_A0.at00.v = ((arc * 5) << 8) + 0x300000;
            timer = ((S_80173408_0 *)jump)->unk_96.u + 1;
            ((S_80173408_0 *)jump)->unk_96.u = timer;
            if (timer < 13) {
                return;
            }
            sprite->frameTable = D_80175C58;
            select_sprite_entry(sprite,
                D_80175C58[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80173408_4 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                0);

            velocity_x = -*(s16 *)((u8 *)x_table +
                (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
            velocity_x += velocity_x >> 2;
            motion->velocity_x = velocity_x;

            velocity_y = -*(s16 *)((u8 *)y_table +
                (((u16)((S_80173408_4 *)actor)->unk_2A.u >> 8) & 0xE)) << 18;
            velocity_y += velocity_y >> 2;
            motion->velocity_y = velocity_y;
            ((S_80173408_0 *)jump)->unk_A8 = motion->velocity_x / 24;
            ((S_80173408_0 *)jump)->unk_AC = motion->velocity_y / 24;
        }
        ((S_80173408_0 *)jump)->unk_96.s = 12;
        ((S_80173408_0 *)jump)->unk_9B.n++;
        return;

    case 3:
        motion->velocity_x -= ((S_80173408_0 *)jump)->unk_A8;
        motion->velocity_y -= ((S_80173408_0 *)jump)->unk_AC;
        if (((S_80173408_0 *)jump)->unk_A0.at02.v > 0) {
            ((S_80173408_0 *)jump)->unk_A0.at02u.v -= 0x10;
        } else {
            ((S_80173408_0 *)jump)->unk_A0.at02.v = 0;
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
        ((S_80173408_0 *)jump)->unk_8C = &kewne_uncached_action_resume_address;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        ((S_80173408_4 *)actor)->unk_46 &= 0x7FFF;
    }
}
