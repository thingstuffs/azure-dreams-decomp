#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801722BC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801722BC_0;   /* arg0 in complete_airborne_actor_recovery */

extern void select_sprite_entry(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_80170EE4[];
extern u8 D_801765F0[];
extern u8 D_801765F8[];

/* Advance movement toward the target tile and finish the action when its timer expires. */
void complete_airborne_actor_recovery(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    s32 target_distance;
    s16 move_ticks;
    u16 timer_next;
    u8 phase;
    s32 actor_flags;
    s32 tile_delta;
    s32 axis_pos;
    DungeonGlobalStatus *action_counter;

    phase = ((S_801722BC_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        timer_next = ((S_801722BC_0 *)action)->unk_9E.s - 1;
        ((S_801722BC_0 *)action)->unk_9E.s = timer_next;
        if ((s16)timer_next > 0) {
            break;
        }

        ((SpriteFrameState *)sprite)->frameTable = D_801765F0;
        select_sprite_entry(
            sprite,
            D_801765F0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_801722BC_0 *)action)->unk_9E.s = 5;
        ((S_801722BC_0 *)action)->unk_A0 = 0;
        ((S_801722BC_0 *)action)->unk_9B++;
                        /* fallthrough */

    case 1:
        ((S_801722BC_0 *)action)->unk_90 -= ((S_801722BC_0 *)action)->unk_A0;
        move_ticks = ((S_801722BC_0 *)action)->unk_9E.u;
        if (move_ticks != 0) {
            tile_delta = ((SpriteFrameState *)sprite)->unk_24 << 6;
            axis_pos = motion->x.w.i;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_x = (tile_delta << 16) / move_ticks;

            axis_pos = motion->y.w.i;
            tile_delta = ((SpriteFrameState *)sprite)->unk_25 << 6;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_y =
                (tile_delta << 16) / ((S_801722BC_0 *)action)->unk_9E.u;
            ((S_801722BC_0 *)action)->unk_A0 =
                (-func_800644B8(((S_801722BC_0 *)action)->unk_9E.u * 0x199)) << 9;
        }

        ((S_801722BC_0 *)action)->unk_90 += ((S_801722BC_0 *)action)->unk_A0;
        timer_next = ((S_801722BC_0 *)action)->unk_9E.s - 1;
        ((S_801722BC_0 *)action)->unk_9E.s = timer_next;
        if ((s16)timer_next < 0) {
            ((S_801722BC_0 *)action)->unk_90 = 0;
            ((S_801722BC_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_801722BC_0 *)action)->unk_9B++;
        }
                        /* fallthrough */

    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_801722BC_0 *)action)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24,
                          ((SpriteFrameState *)sprite)->unk_25);

            ((SpriteFrameState *)sprite)->frameTable = D_801765F8;
            select_sprite_entry(
                sprite,
                D_801765F8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_801722BC_0 *)action)->unk_9B++;
        }
        break;
    }

    timer_next = ((S_801722BC_0 *)action)->unk_96 - 1;
    ((S_801722BC_0 *)action)->unk_96 = timer_next;
    if ((s16)timer_next <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24,
                      ((SpriteFrameState *)sprite)->unk_25);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);

        action_counter = &g_dungeon_status;
        if (action_counter->activity_counts.parts.pending_movement_count != 0) {
            (*(u16 *)&action_counter->activity_counts.parts.pending_movement_count)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing =
                    get_rounded_facing_and_rounding_flag(((SpriteFrameState *)sprite)->unk_24,
                                  ((SpriteFrameState *)sprite)->unk_25,
                                  reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance);
            }
        }

        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((S_801722BC_0 *)action)->unk_8C = D_80170EE4;
            on_actor_status_updated(actor);
        }
    }
}
