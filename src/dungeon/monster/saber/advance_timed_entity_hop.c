#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80166BAC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80166BAC_0;   /* arg0 in advance_timed_entity_hop */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void reduce_actor_food_meter(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern s32 D_80165728;
extern u8 D_80168DEC[];
extern u8 D_80168E0C[];
extern u8 D_80168E14[];

/* Updates a timed hop to the entity tile and handles its completion. */
void advance_timed_entity_hop(void *action, EntityRec *motion, void *map_entity, EntityRec *actor)
{
    s32 state;
    s32 hop_frames;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 hop_timer;
    s32 action_timer;
    s32 actor_flags;
    s32 direction_aux;
    DungeonGlobalStatus *action_counts;

    state = ((S_80166BAC_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)map_entity)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)map_entity)->frameTable = D_80168E0C;
        select_sprite_entry(
            map_entity,
            D_80168E0C[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80166BAC_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_80166BAC_0 *)action)->unk_9E.s = 5;
        ((S_80166BAC_0 *)action)->unk_A4 = 0;
        ((S_80166BAC_0 *)action)->unk_9B++;
                        /* fall through */

    case 1:
        hop_frames = ((S_80166BAC_0 *)action)->unk_9E.s;
        ((S_80166BAC_0 *)action)->unk_90 -= ((S_80166BAC_0 *)action)->unk_A4;
        if (hop_frames != 0) {
            target_x = ((SpriteFrameState *)map_entity)->unk_24;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->unk_0C = ((target_x - pos_x) << 16) / hop_frames;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->unk_10 =
                (((((SpriteFrameState *)map_entity)->unk_25 << 6) - pos_y) << 16) /
                ((S_80166BAC_0 *)action)->unk_9E.s;

            ((S_80166BAC_0 *)action)->unk_A4 =
                (-func_800644B8(((S_80166BAC_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((S_80166BAC_0 *)action)->unk_90;
        arc_offset = ((S_80166BAC_0 *)action)->unk_A4;
        hop_timer = ((S_80166BAC_0 *)action)->unk_9E.u;
        height_offset += arc_offset;
        hop_timer -= 1;
        ((S_80166BAC_0 *)action)->unk_9E.u = hop_timer;
        ((S_80166BAC_0 *)action)->unk_90 = height_offset;
        if ((hop_timer << 16) < 0) {
            ((S_80166BAC_0 *)action)->unk_90 = 0;
            ((S_80166BAC_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_80166BAC_0 *)action)->unk_9B++;
        }
                        /* fall through */

    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_80166BAC_0 *)action)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25);
            ((SpriteFrameState *)map_entity)->frameTable = D_80168E14;
            select_sprite_entry(
                map_entity,
                D_80168E14[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80166BAC_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        if (*(u8 * *)&((SpriteFrameState *)map_entity)->frameTable != D_80168DEC) {
            ((SpriteFrameState *)map_entity)->frameTable = D_80168DEC;
            select_sprite_entry(
                map_entity,
                D_80168DEC[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    action_timer = ((S_80166BAC_0 *)action)->unk_96 - 1;
    ((S_80166BAC_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25);
    reduce_actor_food_meter(actor, 4);
    advance_status_timers(actor);

    action_counts = &g_dungeon_status;
    if (action_counts->unk_08 != 0) {
        (*(u16 *)&action_counts->unk_08)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)map_entity)->unk_24,
                ((SpriteFrameState *)map_entity)->unk_25,
                D_80082E80.tileX,
                D_80082E80.tileY,
                &direction_aux);
        }
    }

    if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
        ((S_80166BAC_0 *)action)->unk_8C = &D_80165728;
        on_actor_status_updated(actor);
    }
}
