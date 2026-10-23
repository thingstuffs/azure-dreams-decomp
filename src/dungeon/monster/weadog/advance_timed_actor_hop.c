#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/weadog.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801550E0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801550E0_0;   /* arg0 in advance_timed_actor_hop */

typedef struct S_801550E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801550E0_1;   /* arg3 in advance_timed_actor_hop */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


extern s32 D_80153CE8;
extern u8 D_80156EB8[];
extern u8 D_80156ED0[];
extern u8 D_80156ED8[];

/* Updates a timed hop to the actor's tile and handles action completion. */
void advance_timed_actor_hop(void *action, void *motion, SpriteFrameState *sprite, void *actor)
{
    s32 facing_aux;
    s32 state;
    s32 hop_frames;
    s32 actor_flags;
    s32 target_x;
    s32 x_offset;
    s32 y_offset;
    s16 next_frame;
    u16 action_timer;
    u8 *anim_table;

    state = ((S_801550E0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        next_frame = ((S_801550E0_0 *)action)->unk_9E.s - 1;
        ((S_801550E0_0 *)action)->unk_9E.s = next_frame;
        if ((next_frame << 16) != 0) {
            break;
        }

        sprite->frameTable = D_80156ED0;
        select_sprite_entry(
            sprite,
            D_80156ED0[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801550E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801550E0_0 *)action)->unk_98 |= 8;
        ((S_801550E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801550E0_0 *)action)->unk_9E.u = 5;
        ((S_801550E0_0 *)action)->unk_A0 = 0;
        ((S_801550E0_0 *)action)->unk_9B++;

    case 1:
        hop_frames = ((S_801550E0_0 *)action)->unk_9E.u;
        ((S_801550E0_0 *)action)->unk_90 -= ((S_801550E0_0 *)action)->unk_A0;
        if (hop_frames != 0) {
            target_x = sprite->unk_24;
            x_offset = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            x_offset -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - x_offset) << 16) / hop_frames;

            y_offset = ((EntityRec *)motion)->y.w.i;
            y_offset -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((sprite->unk_25 << 6) - y_offset) << 16) /
                ((S_801550E0_0 *)action)->unk_9E.u;
            ((S_801550E0_0 *)action)->unk_A0 =
                (-func_800644B8(((S_801550E0_0 *)action)->unk_9E.u * 0x199)) << 10;
        }

        ((S_801550E0_0 *)action)->unk_90 += ((S_801550E0_0 *)action)->unk_A0;
        next_frame = ((S_801550E0_0 *)action)->unk_9E.s - 1;
        ((S_801550E0_0 *)action)->unk_9E.s = next_frame;
        if (next_frame < 0) {
            ((S_801550E0_0 *)action)->unk_90 = 0;
            ((S_801550E0_0 *)action)->unk_98 &= 0xFFF7;
            ((S_801550E0_1 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801550E0_0 *)action)->unk_9B++;
        }

    case 2:
        if (((S_801550E0_1 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801550E0_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);

            sprite->frameTable = D_80156ED8;
            select_sprite_entry(
                sprite,
                D_80156ED8[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801550E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801550E0_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        anim_table = D_80156EB8;
        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801550E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_timer = ((S_801550E0_0 *)action)->unk_96 - 1;
    ((S_801550E0_0 *)action)->unk_96 = action_timer;
    if ((s16)action_timer > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
        g_dungeon_status.activity_counts.parts.pending_movement_count--;
    }

    actor_flags = ((S_801550E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_801550E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_801550E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_801550E0_1 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
                sprite->unk_24, sprite->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_801550E0_0 *)action)->unk_8C = &D_80153CE8;
        on_actor_status_updated(actor);
    }
}
