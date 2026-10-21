#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8014EBAC_0 {
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
} S_8014EBAC_0;   /* arg0 in advance_actor_hop_and_complete */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern s32 D_8014D728;
extern u8 D_80150DEC[];
extern u8 D_80150E0C[];
extern u8 D_80150E14[];

/* Updates the actor's hop toward its tile and completes the timed action. */
void advance_actor_hop_and_complete(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    s32 state;
    s32 hop_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 hop_offset;
    s32 pos_y;
    s32 next_hop_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *global_base;

    state = ((S_8014EBAC_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_80150E0C;
        select_sprite_entry(
            sprite,
            D_80150E0C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_8014EBAC_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_8014EBAC_0 *)action)->unk_9E.s = 5;
        ((S_8014EBAC_0 *)action)->unk_A4 = 0;
        ((S_8014EBAC_0 *)action)->unk_9B++;

    case 1:
        hop_ticks = ((S_8014EBAC_0 *)action)->unk_9E.s;
        ((S_8014EBAC_0 *)action)->unk_90 -= ((S_8014EBAC_0 *)action)->unk_A4;
        if (hop_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->velocity_x = ((target_x - pos_x) << 16) / hop_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((S_8014EBAC_0 *)action)->unk_9E.s;

            ((S_8014EBAC_0 *)action)->unk_A4 =
                (-func_800644B8(((S_8014EBAC_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height = ((S_8014EBAC_0 *)action)->unk_90;
        hop_offset = ((S_8014EBAC_0 *)action)->unk_A4;
        next_hop_ticks = ((S_8014EBAC_0 *)action)->unk_9E.u;
        height += hop_offset;
        next_hop_ticks -= 1;
        ((S_8014EBAC_0 *)action)->unk_9E.u = next_hop_ticks;
        ((S_8014EBAC_0 *)action)->unk_90 = height;
        if ((next_hop_ticks << 16) < 0) {
            ((S_8014EBAC_0 *)action)->unk_90 = 0;
            ((S_8014EBAC_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_8014EBAC_0 *)action)->unk_9B++;
        }

    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_8014EBAC_0 *)action)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->frameTable = D_80150E14;
            select_sprite_entry(
                sprite,
                D_80150E14[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_8014EBAC_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable == D_80150DEC) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_80150DEC;
        select_sprite_entry(
            sprite,
            D_80150DEC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    default:
        break;
    }

    action_ticks = ((S_8014EBAC_0 *)action)->unk_96 - 1;
    ((S_8014EBAC_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & 0x8000) {
            actor->action_flags &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->unk_24,
                ((SpriteFrameState *)sprite)->unk_25,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_8014EBAC_0 *)action)->unk_8C = &D_8014D728;
        on_actor_status_updated(actor);
    }
}
