#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/nyuel.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"

typedef struct S_80172158_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
} S_80172158_0;   /* arg0 in move_actor_with_vertical_arc */

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);


extern u8 nyuel_action_resume_address[];
extern u8 nyuel_frame_set_2[];

/* Moves the actor to its tile with a vertical arc and completes the timed action. */
void move_actor_with_vertical_arc(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 facing_aux;
    s32 move_ticks;
    s32 x_delta;
    s32 axis_pos;
    s32 position;
    s16 next_move_ticks;
    s32 actor_flags;
    u16 action_ticks;
    s32 phase;
    DungeonGlobalStatus *counter_base;

    phase = action->action_phase;
    switch (phase) {
    case 0:
        if (!((sprite->unk_04 == 1 &&
               (sprite->flags & 0x1000)) ||
              (sprite->flags & 0xE000))) {
            break;
        }
        action->action_state_flags |= 8;
        (*(u32 *)&actor->flags1C) &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80172158_0 *)action)->unk_9E = 6;
        ((S_80172158_0 *)action)->unk_A0 = 0;
        action->action_phase++;
                        /* fall through */
    case 1:
        move_ticks = ((S_80172158_0 *)action)->unk_9E;
        ((S_80172158_0 *)action)->unk_90 =
            ((S_80172158_0 *)action)->unk_90 - ((S_80172158_0 *)action)->unk_A0;
        if (move_ticks != 0) {
            x_delta = sprite->tile_x;
            axis_pos = motion->x.w.i;
            x_delta <<= 6;
            axis_pos -= 0x20;
            x_delta -= axis_pos;
            x_delta <<= 16;
            motion->velocity_x = x_delta / move_ticks;
            axis_pos = motion->y.w.i - 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - axis_pos) << 16) /
                (s16)((S_80172158_0 *)action)->unk_9E;
            ((S_80172158_0 *)action)->unk_A0 =
                (-rsin(((S_80172158_0 *)action)->unk_9E * 0x155)) << 9;
        }
        ((S_80172158_0 *)action)->unk_90 += ((S_80172158_0 *)action)->unk_A0;
        next_move_ticks = --((S_80172158_0 *)action)->unk_9E;
        if (next_move_ticks < 0) {
            ((S_80172158_0 *)action)->unk_90 = 0;
            action->action_state_flags &= 0xFFF7;
            (*(u32 *)&actor->flags1C) |= ACTOR_GROUNDED;
            action->action_phase++;
        }

                        /* fall through */
    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = nyuel_frame_set_2;
            select_sprite_entry(
                sprite,
                nyuel_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase++;
        }

        break;
    default:
        break;
    }
    action_ticks = ((S_80172158_0 *)action)->unk_96 - 1;
    ((S_80172158_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 3);
        advance_status_timers(actor);

        counter_base = &g_dungeon_status;
        if (counter_base->activity_counts.parts.pending_movement_count != 0) {
            (*(u16 *)&counter_base->activity_counts.parts.pending_movement_count)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
            }
        }
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((S_80172158_0 *)action)->unk_8C = nyuel_action_resume_address;
            on_actor_status_updated(actor);
        }
    }
}
