#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/weadog.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

typedef struct S_801670E0_0 {
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
} S_801670E0_0;   /* arg0 in advance_timed_hop_and_recover */

typedef struct S_801670E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801670E0_1;   /* arg3 in advance_timed_hop_and_recover */


extern s32 rsin(s32);

extern s32 D_80165CE8;
extern u8 D_80168EB8[];
extern u8 D_80168ED0[];
extern u8 D_80168ED8[];

/* Updates a timed hop toward the target tile and handles actor recovery when the timer expires. */
void advance_timed_hop_and_recover(void *motion_state, void *motion, SpriteFrameState *sprite, void *actor)
{
    u16 direction_aux;
    s32 state;
    s32 hop_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 position_x;
    s32 position_y;
    s16 phase_ticks;
    u16 action_ticks;
    u8 *anim_table;

    state = ((S_801670E0_0 *)motion_state)->unk_9B;
    switch (state) {
    case 0:
        phase_ticks = ((S_801670E0_0 *)motion_state)->unk_9E.s - 1;
        ((S_801670E0_0 *)motion_state)->unk_9E.s = phase_ticks;
        if ((phase_ticks << 16) != 0) {
            break;
        }

        sprite->frameTable = D_80168ED0;
        select_sprite_entry(
            sprite,
            D_80168ED0[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801670E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801670E0_0 *)motion_state)->unk_98 |= 8;
        ((S_801670E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801670E0_0 *)motion_state)->unk_9E.u = 5;
        ((S_801670E0_0 *)motion_state)->unk_A0 = 0;
        ((S_801670E0_0 *)motion_state)->unk_9B++;

    case 1:
        hop_ticks = ((S_801670E0_0 *)motion_state)->unk_9E.u;
        ((S_801670E0_0 *)motion_state)->unk_90 -= ((S_801670E0_0 *)motion_state)->unk_A0;
        if (hop_ticks != 0) {
            target_x = sprite->tile_x;
            position_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            position_x -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - position_x) << 16) / hop_ticks;

            position_y = ((EntityRec *)motion)->y.w.i;
            position_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((sprite->tile_y << 6) - position_y) << 16) /
                ((S_801670E0_0 *)motion_state)->unk_9E.u;
            ((S_801670E0_0 *)motion_state)->unk_A0 =
                (-rsin(((S_801670E0_0 *)motion_state)->unk_9E.u * 0x199)) << 10;
        }

        ((S_801670E0_0 *)motion_state)->unk_90 += ((S_801670E0_0 *)motion_state)->unk_A0;
        phase_ticks = ((S_801670E0_0 *)motion_state)->unk_9E.s - 1;
        ((S_801670E0_0 *)motion_state)->unk_9E.s = phase_ticks;
        if (phase_ticks < 0) {
            ((S_801670E0_0 *)motion_state)->unk_90 = 0;
            ((S_801670E0_0 *)motion_state)->unk_98 &= 0xFFF7;
            ((S_801670E0_1 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801670E0_0 *)motion_state)->unk_9B++;
        }

    case 2:
        if (((S_801670E0_1 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801670E0_0 *)motion_state)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

            sprite->frameTable = D_80168ED8;
            select_sprite_entry(
                sprite,
                D_80168ED8[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801670E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801670E0_0 *)motion_state)->unk_9B++;
        }
        break;

    case 3:
        anim_table = D_80168EB8;
        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801670E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_ticks = ((S_801670E0_0 *)motion_state)->unk_96 - 1;
    ((S_801670E0_0 *)motion_state)->unk_96 = action_ticks;
    if ((s16)action_ticks > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
        g_dungeon_status.activity_counts.parts.pending_movement_count--;
    }

    actor_flags = ((S_801670E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_801670E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_801670E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_801670E0_1 *)actor)->unk_2A = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_801670E0_0 *)motion_state)->unk_8C = &D_80165CE8;
        on_actor_status_updated(actor);
    }
}
