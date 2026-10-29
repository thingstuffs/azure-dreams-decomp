#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/baloon.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

typedef struct S_801733B4_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
    u8 pad_A8[0x2];
    union { u16 s; s16 u; } unk_AA;   /* accessed as both */
} S_801733B4_0;   /* arg0 in advance_actor_hop_animation */

typedef struct S_801733B4_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801733B4_1;   /* arg3 in advance_actor_hop_animation */


extern s32 rsin(s32);

extern u8 baloon_default_frames[];
extern u8 baloon_hop_frames[];
extern u8 D_800E2370[];

/* Advances the actor's hop animation and finishes the action when its timer expires. */
void advance_actor_hop_animation(void *motion, ObjectPosition *position, SpriteFrameState *sprite, void *actor)
{
    u16 facing_aux;
    s32 y_offset;
    u16 timer_value;
    s32 phase;

    phase = ((S_801733B4_0 *)motion)->unk_9B;
    switch (phase) {
    case 0:
        timer_value = ((S_801733B4_0 *)motion)->unk_AA.s + 1;
        ((S_801733B4_0 *)motion)->unk_AA.s = timer_value;
        if ((s16)timer_value < 2) {
            break;
        }
        sprite->frameTable = baloon_hop_frames;
        select_sprite_entry(sprite,
            baloon_hop_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801733B4_0 *)motion)->unk_98 |= 8;
        ((S_801733B4_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801733B4_0 *)motion)->unk_AA.s = 5;
        ((S_801733B4_0 *)motion)->unk_A4 = 0;
        ((S_801733B4_0 *)motion)->unk_9B++;
                        /* fallthrough */
    case 1:
        ((S_801733B4_0 *)motion)->unk_90.at00.v -= ((S_801733B4_0 *)motion)->unk_A4;
        if (((S_801733B4_0 *)motion)->unk_AA.u != 0) {
            position->velocity_x =
                (((sprite->tile_x << 6) -
                  ({ position->x.w.i - 0x20; })) << 16) /
                ((S_801733B4_0 *)motion)->unk_AA.u;
            y_offset = position->y.w.i - 0x20;
            position->velocity_y =
                (((sprite->tile_y << 6) - y_offset) << 16) /
                ((S_801733B4_0 *)motion)->unk_AA.u;
            ((S_801733B4_0 *)motion)->unk_A4 =
                (-rsin(((S_801733B4_0 *)motion)->unk_AA.u * 0x199)) << 10;
        }
        ((S_801733B4_0 *)motion)->unk_90.at00.v += ((S_801733B4_0 *)motion)->unk_A4;
        timer_value = ((S_801733B4_0 *)motion)->unk_AA.s - 1;
        ((S_801733B4_0 *)motion)->unk_AA.s = timer_value;
        if ((s16)timer_value < 0) {
            ((S_801733B4_0 *)motion)->unk_90.at02.v = -0x10;
            ((S_801733B4_0 *)motion)->unk_98 &= 0xFFF7;
            ((S_801733B4_1 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801733B4_0 *)motion)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((S_801733B4_1 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801733B4_0 *)motion)->unk_98 &= 0xFFF7;
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_800E2370;
            select_sprite_entry(sprite,
                D_800E2370[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801733B4_0 *)motion)->unk_9B++;
        }
        break;
        break;
    case 3:
        if (*(u8 * *)&sprite->frameTable != baloon_default_frames) {
            sprite->frameTable = baloon_default_frames;
            select_sprite_entry(sprite,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801733B4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801733B4_0 *)motion)->unk_9E = 0;
        }
        break;
    }

    timer_value = ((S_801733B4_0 *)motion)->unk_96 - 1;
    ((S_801733B4_0 *)motion)->unk_96 = timer_value;
    if (((s32)timer_value << 16) <= 0) {
        s32 actor_flags;

        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count--;
        }
        actor_flags = ((S_801733B4_1 *)actor)->unk_1C.u;
        if (actor_flags & 0x2000) {
            if (((S_801733B4_1 *)actor)->unk_46 & 0x8000) {
                ((S_801733B4_1 *)actor)->unk_46 &= 0x7FFF;
            }
        } else {
            if (!(actor_flags & 0x410)) {
                if (actor_flags & 0x20000) {
                    ((S_801733B4_1 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
                }
            }
        }

        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((S_801733B4_0 *)motion)->unk_8C = update_actor_turn_behavior;
            on_actor_status_updated(actor);
        }
    }
}
