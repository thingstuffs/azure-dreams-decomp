#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80B09454_0 {
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
} S_80B09454_0;   /* arg0 in func_80B09454 */

extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern s32 D_801597F4;
extern u8 D_8015D988[];
extern u8 D_8015D9A8[];
extern u8 D_8015D9B8[];

/* Updates an actor's hop toward its tile and completes the timed action. */
void func_80B09454(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 direction_aux;
    DungeonGlobalStatus *global_state;

    state = ((S_80B09454_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_8015D9A8;
        select_sprite_entry(
            sprite,
            D_8015D9A8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80B09454_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_80B09454_0 *)action)->unk_9E.s = 5;
        ((S_80B09454_0 *)action)->unk_A4 = 0;
        ((S_80B09454_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((S_80B09454_0 *)action)->unk_9E.s;
        ((S_80B09454_0 *)action)->unk_90 -= ((S_80B09454_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->velocity_x = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((S_80B09454_0 *)action)->unk_9E.s;

            ((S_80B09454_0 *)action)->unk_A4 =
                (-func_800644B8(((S_80B09454_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height = ((S_80B09454_0 *)action)->unk_90;
        arc_offset = ((S_80B09454_0 *)action)->unk_A4;
        next_move_ticks = ((S_80B09454_0 *)action)->unk_9E.u;
        height += arc_offset;
        next_move_ticks -= 1;
        ((S_80B09454_0 *)action)->unk_9E.u = next_move_ticks;
        ((S_80B09454_0 *)action)->unk_90 = height;
        if ((next_move_ticks << 16) < 0) {
            ((S_80B09454_0 *)action)->unk_90 = 0;
            ((S_80B09454_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_80B09454_0 *)action)->unk_9B++;
        }
    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_80B09454_0 *)action)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->frameTable = D_8015D9B8;
            select_sprite_entry(
                sprite,
                D_8015D9B8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80B09454_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable == D_8015D988) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = D_8015D988;
        select_sprite_entry(
            sprite,
            D_8015D988[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }

    action_ticks = ((S_80B09454_0 *)action)->unk_96 - 1;
    ((S_80B09454_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_state = &g_dungeon_status;
    if (global_state->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_state->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                ((SpriteFrameState *)sprite)->unk_24,
                ((SpriteFrameState *)sprite)->unk_25,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((S_80B09454_0 *)action)->unk_8C = &D_801597F4;
        on_actor_status_updated(actor);
    }
}
