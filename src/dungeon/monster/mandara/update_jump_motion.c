#include "shared/actor_status_flags.h"
#include "dungeon/monster/mandara.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/status.h"

typedef struct S_80047784 S_80047784;

typedef struct S_80172834_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172834_0;   /* arg0 in update_jump_motion_2 */

struct SpriteFrameState;
extern void select_sprite_entry(struct SpriteFrameState *, s16, s16);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void on_actor_status_updated(void *actor);
void spend_actor_mp();

extern u8 D_80175278[];
extern u8 D_80175280[];

/* Updates jump motion and animation, then completes the landing. */
void update_jump_motion_2(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *unit, ActorRecord *actor) {
    u16 distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        if (!(unit->flags & 0x6000)) {
            break;
        }
        (unit->frameTable) = D_80175278;
        select_sprite_entry(
            unit,
            D_80175278[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_state_flags |= 8;
        motion->velocity_z = 0xFFEE0000;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_A0.value = 0;
        action->action_phase.u++;

    case 1:
        frames_left = action->action_timer.s;
        action->unk_90.value -= action->unk_A0.value;
        if (frames_left != 0) {
            {
                s32 target_x = unit->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = unit->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16) /
                    action->action_timer.s;
            }
            action->unk_A0.value += motion->velocity_z;
            motion->velocity_z += 0x40000;
        }
        action->unk_90.value += action->unk_A0.value;
        if (action->action_timer.s < 2) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            action->action_phase.u++;
        }

    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, unit->tile_x, unit->tile_y);
            (unit->frameTable) = D_80175280;
            select_sprite_entry(
                unit,
                D_80175280[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u++;
        }
    default:
        break;
    }

    next_timer = action->action_timer.u - 1;
    action->action_timer.s = next_timer;
    if ((next_timer << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, unit->tile_x, unit->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {

            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count--;
            }
        }

        actor_flags = ((u32)actor->flags1C);
        if (actor_flags & 0x2000) {
            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                actor->facing = get_rounded_facing_and_rounding_flag(
                    unit->tile_x, unit->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            }
        }

        if ((check_actor_floor_trap(unit, actor) << 16) > 0) {
            action->unk_8C.handler = update_long_actor_action;
            on_actor_status_updated(actor);
        }
    }
}
