#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
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


extern s32 rsin(s32);

extern s32 D_801597F4;
extern u8 snowman_frame_set_6[];
extern u8 D_8015D9A8[];
extern u8 D_8015D9B8[];

/* Updates an actor's hop toward its tile and completes the timed action. */
void finish_snowman_tile_hop(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
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
    u16 direction_aux;
    DungeonGlobalStatus *global_state;

    state = body->action_phase.u;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_8015D9A8;
        select_sprite_entry(
            sprite,
            D_8015D9A8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->unk_9E.s = 5;
        body->unk_A4.value = 0;
        body->action_phase.u++;

    case 1:
        move_ticks = body->unk_9E.s;
        body->unk_90.value -= body->unk_A4.value;
        if (move_ticks != 0) {
            target_x = sprite->tile_x;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->velocity_x = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - pos_y) << 16) /
                body->unk_9E.s;

            body->unk_A4.value =
                (-rsin(body->unk_9E.s * 0x199)) << 10;
        }

        height = body->unk_90.value;
        arc_offset = body->unk_A4.value;
        next_move_ticks = body->unk_9E.u;
        height += arc_offset;
        next_move_ticks -= 1;
        body->unk_9E.u = next_move_ticks;
        body->unk_90.value = height;
        if ((next_move_ticks << 16) < 0) {
            body->unk_90.value = 0;
            body->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            body->action_phase.u++;
        }
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            body->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_8015D9B8;
            select_sprite_entry(
                sprite,
                D_8015D9B8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
        }
        break;

    case 3:
        if (*(u8 * *)&sprite->frameTable == snowman_frame_set_6) {
            break;
        }
        sprite->frameTable = snowman_frame_set_6;
        select_sprite_entry(
            sprite,
            snowman_frame_set_6[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }

    action_ticks = body->action_timer.u - 1;
    body->action_timer.u = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
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
                sprite->tile_x,
                sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        body->unk_8C.address = &D_801597F4;
        on_actor_status_updated(actor);
    }
}
