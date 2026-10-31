#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "dungeon/item.h"

extern s32 rsin(s32);

extern void golem_action_continuation_address();

/* Advance the actor's hop to its tile and finish the motion when its timer expires. */
void advance_actor_hop_to_tile(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 coord_result;
    s32 phase;
    u32 actor_flags;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        body->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->unk_A4.halves.low.s = 7;
        body->unk_A0.value = 0;
        body->action_phase.u++;

    case 1:
        body->unk_90.value -= body->unk_A0.value;
        if (body->unk_A4.halves.low.s != 0) {
            {
                s32 target_x = sprite->tile_x << 6;
                s32 current_x = position->x.w.i - 32;

                position->velocity_x =
                    ((target_x - current_x) << 16) / body->unk_A4.halves.low.s;
            }
            {
                s32 target_y = sprite->tile_y << 6;
                s32 current_y = position->y.w.i - 32;

                position->velocity_y =
                    ((target_y - current_y) << 16) / body->unk_A4.halves.low.s;
            }
            body->unk_A0.value =
                (-rsin(body->unk_A4.halves.low.s * 292)) << 9;
        }

        body->unk_90.value += body->unk_A0.value;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->unk_A4.halves.low.s--;
        if (body->unk_A4.halves.low.s < 0) {
            body->unk_90.value = 0;
            body->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            body->action_phase.u++;
        }

    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            body->action_state_flags &= 0xFFF7;
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
            body->action_phase.u++;
        }

    default:
        break;
    }

    body->action_timer.s--;
    if (body->action_timer.s > 0) {
        return;
    }

    position->velocity_z = 0;
    position->velocity_y = 0;
    position->velocity_x = 0;
    set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 5);
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
    } else {
        if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &coord_result);
            }
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        body->unk_8C.handler = &golem_action_continuation_address;
        on_actor_status_updated(actor);
    }
}
