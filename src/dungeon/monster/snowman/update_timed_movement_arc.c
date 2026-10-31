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

extern s32 D_801537F4;
extern u8 snowman_frame_set_5[];
extern u8 D_801579A8[];
extern u8 D_801579B8[];

/* Updates a timed movement arc, its animations, and the actor's completion state. */
void update_timed_movement_arc(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_frames;
    s32 action_timer;
    s32 actor_flags;
    u16 direction_aux;
    DungeonGlobalStatus *global_state;

    state = body->action_phase.u;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_801579A8;
        select_sprite_entry(
            sprite,
            D_801579A8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        body->unk_9E.s = 5;
        body->unk_A4.value = 0;
        body->action_phase.u++;
                        /* fallthrough */
    case 1:
        move_frames = body->unk_9E.s;
        body->unk_90.value -= body->unk_A4.value;
        if (move_frames != 0) {
            target_x = sprite->tile_x;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->velocity_x = ((target_x - pos_x) << 16) / move_frames;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - pos_y) << 16) /
                body->unk_9E.s;

            body->unk_A4.value =
                (-rsin(body->unk_9E.s * 0x199)) << 10;
        }

        height_offset = body->unk_90.value;
        arc_offset = body->unk_A4.value;
        next_frames = body->unk_9E.u;
        height_offset += arc_offset;
        next_frames -= 1;
        body->unk_9E.u = next_frames;
        body->unk_90.value = height_offset;
        if ((next_frames << 16) < 0) {
            body->unk_90.value = 0;
            body->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            body->action_phase.u++;
        }
                        /* fallthrough */
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            body->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_801579B8;
            select_sprite_entry(
                sprite,
                D_801579B8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
        }
        break;
    case 3:
        if (*(u8 * *)&sprite->frameTable != snowman_frame_set_5) {
            sprite->frameTable = snowman_frame_set_5;
            select_sprite_entry(
                sprite,
                snowman_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    action_timer = body->action_timer.u - 1;
    body->action_timer.u = action_timer;
    if ((action_timer << 16) > 0) {
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
    } else {
        if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x,
                    sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
            }
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        body->unk_8C.address = &D_801537F4;
        on_actor_status_updated(actor);
    }
}
