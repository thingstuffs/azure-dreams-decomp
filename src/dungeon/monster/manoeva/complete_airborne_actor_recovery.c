#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
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



extern s32 rsin(s32);

extern u8 manoeva_action_resume_address[];
extern u8 D_801765F0[];
extern u8 D_801765F8[];

/* Advance movement toward the target tile and finish the action when its timer expires. */
void complete_airborne_actor_recovery(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor)
{
    u16 target_distance;
    s16 move_ticks;
    u16 timer_next;
    u8 phase;
    s32 actor_flags;
    s32 tile_delta;
    s32 axis_pos;
    DungeonGlobalStatus *action_counter;

    phase = ((ActorRecord *)action)->action_phase.u;
    switch (phase) {
    case 0:
        timer_next = ((ActorRecord *)action)->unk_9E.u - 1;
        ((ActorRecord *)action)->unk_9E.u = timer_next;
        if ((s16)timer_next > 0) {
            break;
        }

        ((SpriteFrameState *)sprite)->frameTable = D_801765F0;
        select_sprite_entry(
            sprite,
            D_801765F0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((ActorRecord *)action)->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((ActorRecord *)action)->unk_9E.u = 5;
        ((ActorRecord *)action)->unk_A0.value = 0;
        ((ActorRecord *)action)->action_phase.u++;
                        /* fallthrough */

    case 1:
        ((ActorRecord *)action)->unk_90.value -= ((ActorRecord *)action)->unk_A0.value;
        move_ticks = ((ActorRecord *)action)->unk_9E.s;
        if (move_ticks != 0) {
            tile_delta = ((SpriteFrameState *)sprite)->tile_x << 6;
            axis_pos = motion->x.w.i;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_x = (tile_delta << 16) / move_ticks;

            axis_pos = motion->y.w.i;
            tile_delta = ((SpriteFrameState *)sprite)->tile_y << 6;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_y =
                (tile_delta << 16) / ((ActorRecord *)action)->unk_9E.s;
            ((ActorRecord *)action)->unk_A0.value =
                (-rsin(((ActorRecord *)action)->unk_9E.s * 0x199)) << 9;
        }

        ((ActorRecord *)action)->unk_90.value += ((ActorRecord *)action)->unk_A0.value;
        timer_next = ((ActorRecord *)action)->unk_9E.u - 1;
        ((ActorRecord *)action)->unk_9E.u = timer_next;
        if ((s16)timer_next < 0) {
            ((ActorRecord *)action)->unk_90.value = 0;
            ((ActorRecord *)action)->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            ((ActorRecord *)action)->action_phase.u++;
        }
                        /* fallthrough */

    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            ((ActorRecord *)action)->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x,
                          ((SpriteFrameState *)sprite)->tile_y);

            ((SpriteFrameState *)sprite)->frameTable = D_801765F8;
            select_sprite_entry(
                sprite,
                D_801765F8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((ActorRecord *)action)->action_phase.u++;
        }
        break;
    }

    timer_next = ((ActorRecord *)action)->action_timer.u - 1;
    ((ActorRecord *)action)->action_timer.u = timer_next;
    if ((s16)timer_next <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x,
                      ((SpriteFrameState *)sprite)->tile_y);
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
                    get_rounded_facing_and_rounding_flag(((SpriteFrameState *)sprite)->tile_x,
                                  ((SpriteFrameState *)sprite)->tile_y,
                                  reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance);
            }
        }

        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((ActorRecord *)action)->unk_8C.byte_ptr = manoeva_action_resume_address;
            on_actor_status_updated(actor);
        }
    }
}
