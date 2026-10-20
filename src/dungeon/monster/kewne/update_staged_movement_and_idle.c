#include "common.h"
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
extern void reduce_actor_food_meter(void *, s32);
extern void create_parent_position_effect(EntityRec *parent, s32 effect_param, u8 *effect_data);

extern u8 D_801710EC[9];
extern u8 D_80175E78[8];
extern u8 D_80175E80[8];

typedef struct S_80172DDC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_A0;   /* overlapping accesses */
    u8 pad_A4[0x4];
    s32 unk_A8;
    s32 unk_AC;
} S_80172DDC_0;   /* arg0 in update_staged_movement_and_idle */

/* Updates the actor's staged movement, animation, and return to idle. */
void update_staged_movement_and_idle(void *action, EntityRec *movement, void *sprite, void *actor)
{
    u8 state;

    state = ((S_80172DDC_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x8000)) {
            play_sound_if_enabled(0x80E);
        }
        ((S_80172DDC_0 *)action)->unk_9B++;

    case 1:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((S_80172DDC_0 *)action)->unk_96.u = 0x100;
            ((S_80172DDC_0 *)action)->unk_9B = 5;
            resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
            return;
        }

        ((SpriteFrameState *)sprite)->unk_05 -= 2;
        {
            u32 direction_offset = ((u16)((EntityRec *)actor)->facing >> 8) & 0xE;
            movement->unk_0C -=
                (s32)*(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset) << 16;
            movement->unk_10 -=
                (s32)*(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset) << 16;
        }
        if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            ((SpriteFrameState *)sprite)->frameTable = D_80175E78;
            select_sprite_entry(
                sprite,
                D_80175E78[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172DDC_0 *)action)->unk_9B++;
        }

    case 2:
    {
        u16 height = ((S_80172DDC_0 *)action)->unk_A0.at02.v + 0x10;

        ((S_80172DDC_0 *)action)->unk_A0.at02.v = height;
        if ((s16)height >= 0x31) {
            ((S_80172DDC_0 *)action)->unk_A0.at02.v = 0x30;
            movement->unk_10 = 0;
            movement->unk_0C = 0;
        }
    }
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            return;
        }
        movement->flags14 = 0;
        movement->unk_10 = 0;
        movement->unk_0C = 0;
        if (((S_80172DDC_0 *)action)->unk_A0.at02u.v < 0x30) {
            return;
        }
        {
            s32 current_state = ((S_80172DDC_0 *)action)->unk_9B;

            ((S_80172DDC_0 *)action)->unk_96.u = 0;
            if (current_state == 0) {
                return;
            }
        }
        play_sound_if_enabled(0x808);
        ((S_80172DDC_0 *)action)->unk_9B++;
        create_parent_position_effect((u8 *)action - 0x20, (u8 *)actor + 0x2A,
                      (u8 *)action + 0x9B);
        return;

    case 3:
    {
        u8 *direction_x = (u8 *)((s8 *)dir_step_x);
        u8 *direction_y = (u8 *)((s8 *)dir_step_y);
        u16 timer;

        movement->unk_0C +=
            (s32)*(s16 *)(direction_x +
                (((u16)((EntityRec *)actor)->facing >> 8) & 0xE)) << 17;

        movement->unk_10 +=
            (s32)*(s16 *)(direction_y +
                (((u16)((EntityRec *)actor)->facing >> 8) & 0xE)) << 17;

        ((S_80172DDC_0 *)action)->unk_A0.at00.v -= (s32)((S_80172DDC_0 *)action)->unk_96.s << 17;
        timer = ((S_80172DDC_0 *)action)->unk_96.u + 1;
        ((S_80172DDC_0 *)action)->unk_96.u = timer;
        if ((s16)timer < 9) {
            return;
        }

        resolve_attack_damage_and_effects(actor, sprite, ((EntityRec *)actor)->facing, 1);
        ((SpriteFrameState *)sprite)->frameTable = D_80175E80;
        select_sprite_entry(
            sprite,
            D_80175E80[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);

        movement->unk_0C =
            -*(s16 *)(direction_x +
                (((u16)((EntityRec *)actor)->facing >> 8) & 0xE)) << 20;

        movement->unk_10 =
            -*(s16 *)(direction_y +
                (((u16)((EntityRec *)actor)->facing >> 8) & 0xE)) << 20;
        ((S_80172DDC_0 *)action)->unk_A8 = movement->unk_0C / 6;
        ((S_80172DDC_0 *)action)->unk_AC = movement->unk_10 / 6;
        ((S_80172DDC_0 *)action)->unk_96.u = 0;
        ((S_80172DDC_0 *)action)->unk_9B++;
        return;
    }

    case 4:
        movement->unk_0C -= ((S_80172DDC_0 *)action)->unk_A8;
        movement->unk_10 -= ((S_80172DDC_0 *)action)->unk_AC;
        ((S_80172DDC_0 *)action)->unk_A0.at00.v =
            func_800644B8(((S_80172DDC_0 *)action)->unk_96.s * 146) * 160 + 0x100000;

    case 5:
    {
        u16 timer = ((S_80172DDC_0 *)action)->unk_96.u + 1;

        ((S_80172DDC_0 *)action)->unk_96.u = timer;
        if ((s16)timer < 7 && !(((SpriteFrameState *)sprite)->flags & 0x8000)) {
            return;
        }
    }
        movement->flags14 = 0;
        movement->unk_10 = 0;
        movement->unk_0C = 0;
        set_record_integer_tile_center(movement, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        reduce_actor_food_meter(actor, 0x100);
        ((S_80172DDC_0 *)action)->unk_8C = D_801710EC;
        g_dungeon_status.unk_0C = 0;
        (*(u16 *)((u8 *)actor + (0x46))) &= 0x7FFF;
        ((S_80172DDC_0 *)action)->unk_98 &= 0xFFF7;
        advance_status_timers(actor);
    }
}
